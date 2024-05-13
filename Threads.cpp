/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

#if !defined THREADS_H
# include "threads.h"
#endif

#include <process.h>
#include <vector>
#if _MSC_VER >= 1800
# include <thread>
# define	STDIO_SPINLOCK	/* использовать семафора вместо мьютекса для ввода-вывода */
#endif

#if defined	STDIO_SPINLOCK
# include <atomic>
#endif

#if !defined (__WINDOWS_H) && (defined (_WIN32) || defined (_WIN64))
# include <windows.h>
#endif

#ifdef _MSC_VER
# pragma comment (user,"(KSV) author Adamanteus.")
# pragma warning (disable : 4267)
#endif

/* временные константы */
#define	NSMSC	1000
#define	MSSEC	1000

#define	halt	abort	/* функция аварийного заверщения программы */

using namespace std;

#pragma pack(1)	/* выравнивание структур на один байт */

typedef struct tss_keydtor {
	tss_t key;
	tss_dtor_t dtor;
} tss_keydtor_t;

#pragma pack()	/* выравнивание по умолчанию */


#if defined	STDIO_SPINLOCK
static atomic_flag	_stdio_semaphore = ATOMIC_FLAG_INIT;	/* спинлок системной консоли */
#else
static mtx_t	_stdio_mutex;	/* мьютекс системной консоли */
#endif

static vector<tss_keydtor_t>	_tss_dtors;	/* массив для хранения деструкторов ключей */


/*-------------------------------------------------------------*/

#if _MSC_VER < 1800
thrd_creator_t	cnd_init (cnd_t* cond)
{
	if ( ! cond) return thrd_error;
	InitializeConditionVariable((PCONDITION_VARIABLE)&cond->condvar);
	return thrd_success;
};

thrd_creator_t	cnd_broadcast (cnd_t* cond)
{
	if ( ! cond) return thrd_error;
	WakeAllConditionVariable((PCONDITION_VARIABLE)&cond->condvar);
	return thrd_success;
};

thrd_creator_t	cnd_signal (cnd_t* cond)
{
	if ( ! cond) return thrd_error;
	WakeConditionVariable((PCONDITION_VARIABLE)&cond->condvar);
	return thrd_success;
};

thrd_creator_t	cnd_wait (cnd_t* cond, mtx_t* mtx)
{
	if (( ! cond) || ( ! mtx)) return thrd_error;
	SleepConditionVariableCS((PCONDITION_VARIABLE)&cond->condvar, (PCRITICAL_SECTION)&mtx->cs, INFINITE);
	return thrd_success;
};

thrd_creator_t	cnd_timedwait (cnd_t* cond, mtx_t* mtx, const struct timespec* ts)
{
	if (( ! cond) || ( ! mtx) || ( ! ts)) return thrd_error;
	if (SleepConditionVariableCS((PCONDITION_VARIABLE)&cond->condvar, (PCRITICAL_SECTION)&mtx->cs, (DWORD)(MSSEC * ts->tv_sec + ts->tv_nsec / NSMSC)))
		return thrd_success;
	return (GetLastError() == ERROR_TIMEOUT) ? thrd_busy : thrd_error;
};

void	cnd_destroy (cnd_t* cond) { };

thrd_creator_t	mtx_init (mtx_t* mtx, int type)
{
	if ( ! mtx) return thrd_error;
	if (type != mtx_plain && type != mtx_timed && type != mtx_try
		&& type != (mtx_plain | mtx_recursive)
		&& type != (mtx_timed | mtx_recursive)
		&& type != (mtx_try | mtx_recursive))
		return thrd_error;
	InitializeCriticalSection((LPCRITICAL_SECTION)&mtx->cs);
	return thrd_success;
};

thrd_creator_t	mtx_lock (mtx_t* mtx)
{
	if ( ! mtx) return thrd_error;
	EnterCriticalSection((LPCRITICAL_SECTION)&mtx->cs);
	return thrd_success;
};

thrd_creator_t	mtx_trylock (mtx_t* mtx)
{
	if ( ! mtx) return thrd_error;
	return TryEnterCriticalSection((LPCRITICAL_SECTION)&mtx->cs) ? thrd_success : thrd_busy;
};

thrd_creator_t	mtx_timedlock (mtx_t* mtx, const struct timespec* ts) {
	time_t expire, now;
	if (( ! mtx) || ( ! ts)) return thrd_error;
	expire = time(NULL);
	expire += ts->tv_sec;
	while (mtx_trylock(mtx) != thrd_success) {
		now = time(NULL);
		if (expire < now) return thrd_busy;
		thrd_yield();
	}
	return thrd_success;
};

thrd_creator_t	mtx_unlock (mtx_t* mtx)
{
	if ( ! mtx) return thrd_error;
	LeaveCriticalSection((LPCRITICAL_SECTION)&mtx->cs);
	return thrd_success;
};

void	mtx_destroy (mtx_t* mtx)
{
	DeleteCriticalSection((LPCRITICAL_SECTION)&mtx->cs);
};

thrd_t	thrd_current ()
{
	thrd_t	ct;
	ct._Hnd = (hand_t)__threadhandle();
	return ct;
};

thrd_creator_t	thrd_detach (thrd_t thr)
{
	if ( ! TerminateThread(thr.hd, FALSE)) return thrd_error;
	return thrd_success;
};

thrd_creator_t	thrd_join (thrd_t thr, int* res)
{
	int	code;
	if (WaitForSingleObject(thr._Hnd, INFINITE) != WAIT_OBJECT_0)
		return thrd_error;
	if (res)
	{
		if ( ! thrd_return(thr, &code)) {
			thrd_detach(thr);
			return thrd_error;
		}
		*res = code;
	}
	else return thrd_detach(thr);
	return thrd_success;
};

void	thrd_yield ()
{
	SwitchToThread();
};

#endif


void	call_once (once_flag* flag, void (* func)()) {
	if (InterlockedCompareExchange(&flag->status, 1, 0) == 0) {
		func();
		InterlockedExchange(&flag->status, 2);
	}
	else {
		while (flag->status == 1)	/* во время первого этапа */
			thrd_yield();
	};
};

static bool	tss_dtor_register (tss_t key, tss_dtor_t dtor) {
	size_t	n;
	tss_keydtor_t	elem = { key, dtor };
	for (n = 0; n < _tss_dtors.size(); n++)
		if (_tss_dtors[n].key == key) {
			_tss_dtors[n].dtor = dtor;
			return true;
		}
	_tss_dtors.push_back(elem);
	return true;
};

static void	tss_dtor_invoke () {
	size_t	n;
	void* data;
	for (n = 0; n < _tss_dtors.size(); n++)
		if (_tss_dtors[n].dtor && (data = tss_get(_tss_dtors[n].key)))
			_tss_dtors[n].dtor(data);	/* вызов деструктора с указателем данных ключа данных потока */
};

thrd_creator_t	tss_create (tss_t* key, tss_dtor_t dtor) {
	if ( ! key) return thrd_error;
	*key = TlsAlloc();
	if (dtor) {
		if ( ! tss_dtor_register(*key, dtor)) {
			TlsFree(* key);
			return thrd_error;
		};
	};
	return (*key != TLS_OUT_OF_INDEXES) ? thrd_success : thrd_error;
};

thrd_creator_t	tss_memory (tss_t* key) {
	return tss_create(key, (tss_dtor_t)free);
};

thrd_creator_t	tss_set (tss_t key, void* val) {
	return TlsSetValue(key, val) ? thrd_success : thrd_error;
};

void*	tss_get (tss_t key) {
	return (void*)TlsGetValue(key);
};

void	tss_delete (tss_t key) {
	TlsFree(key);
};

thrd_creator_t	thrd_init () { return thrd_success; };

thrd_creator_t	thrd_create (thrd_t* thr, thrd_start_t func, void* arg) {
#if 1
	if ( ! (thr->_Hnd = (hand_t)_beginthreadex(NULL, 0, func, arg, 0, &thr->_Id)))
#else
	if ( ! (thr->_Hnd = CreateThread(NULL,	0,(LPTHREAD_START_ROUTINE)func, arg, 0, (LPDWORD)&thr->_Id)))
#endif
		return thrd_error;
	return thrd_success;
};

bool	thrd_equal (thrd_t thr1, thrd_t thr2) {
 return thr1._Id == thr2._Id;
};


int	thrd_sleep (const struct timespec* duration, struct timespec* remaining) {
 unsigned long  pause = (unsigned long)(1000 * duration->tv_sec + duration->tv_nsec / 1000);
 Sleep(pause);
 if (remaining) {
	remaining->tv_sec = 0;
	remaining->tv_nsec = 0;
 };
 return 0;
 
}

int	thrd_exit (int res) {
	tss_dtor_invoke();
	ExitThread(res);
	return res;
};

bool	thrd_return(thrd_t thr, int* res)
{
	return GetExitCodeThread(thr._Hnd, (LPDWORD)res) != 0;
};

#if !defined	STDIO_SPINLOCK

static void	__stdio_mutex_destroy_mutex() {
	mtx_destroy(&_stdio_mutex);
};

mtx_t*	__stdio_mutex () {
 static bool	inited = false;	/* показатель инициализации мьютекса */

 if ( ! inited) {	/* инициализация глобального мьютекса вывода сообщений */
	if (mtx_init(&_stdio_mutex, mtx_plain) != thrd_success)
		halt();
	inited = true;
	atexit(__stdio_mutex_destroy_mutex);
 };
 return &_stdio_mutex;
};

#endif

void	stdio_lock () {
#if defined	STDIO_SPINLOCK
 while(atomic_flag_test_and_set(&_stdio_semaphore))
	thrd_yield(); // ждать
#else
 mtx_lock(__stdio_mutex());
#endif
};

void	stdio_unlock () {
#if defined	STDIO_SPINLOCK
 atomic_flag_clear(&_stdio_semaphore);
#else
 mtx_unlock(__stdio_mutex());
#endif
};
