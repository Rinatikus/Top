/***********************************************************
** Модуль = Threads = 
**
** Автор :	Adamanteus
** Компилятор	Microsoft Visual C++ v.19.0	Дата 17.03.2024
** Назначение : описание стд. функций управления процессами
************************************************************
*/

#if !defined THREADS_H
#define THREADS_H

#include <time.h>
#if _MSC_VER >= 1800
# include <xthreads.h>
#endif

#if defined __cplusplus
extern "C" {
#endif

/*::::::::::::: Типы из словаря предметной области ::::::::::::::::*/

typedef void* hand_t;
typedef	int	tss_t;

#if _MSC_VER >= 1800

typedef	_Thrd_t	thrd_t;
typedef	_Mtx_t	mtx_t;
typedef	_Cnd_t	cnd_t;

#else

typedef		unsigned int	_Thrd_id_t;

typedef	struct _Thrd_tag {
	hand_t	_Hnd;
	_Thrd_id_t	_Id;
} thrd_t;

typedef struct _cnd {
	void* condvar;
} cnd_t;

typedef struct _mtx {
	hand_t	cs[7];
} mtx_t;

typedef struct timespec
{
	time_t	tv_sec;
	long	tv_nsec;
} timespec_t;

#endif

typedef	void	(_stdcall* tss_dtor_t)(void*);
typedef	unsigned int	(_stdcall* thrd_start_t)(void*);

typedef	enum mtx_type {
	mtx_plain     = 0,
	mtx_try       = 1,
	mtx_timed     = 2,
	mtx_recursive = 4
} mtx_type_t;

typedef	enum thrd_creator {
	thrd_success = 0,
	thrd_nomem,
	thrd_timedout,
	thrd_busy,
	thrd_error
} thrd_creator_t;

typedef struct _once_flag {
	volatile long status;
} once_flag, once_flag_t;

/*:::::: константы ::::::::::::::::::::::::::::::::::::::::::::::::*/

#define	TSS_DTOR_ITERATIONS	1
#define	ONCE_FLAG_INIT	{0}


/*:::::: макросы ::::::::::::::::::::::::::::::::::::::::::::::::::*/

#if _MSC_VER >= 1800
#define	cnd_init(cond)	_Cnd_init(cond)
#define	cnd_broadcast(cond)	_Cnd_broadcast(*cond)
#define	cnd_signal(cond)	_Cnd_signal(*cond)
#define	cnd_wait(cond, mtx)	_Cnd_wait(*cond, *mtx)
#define	cnd_timedwait(cond, mtx, ts)	_Cnd_timedwait(cond, mtx, ts)
#define	cnd_destroy(cond)	_Cnd_destroy(*cond)

#define	mtx_init(mtx, type)	_Mtx_init(mtx, type)
#define	mtx_lock(mtx)	_Mtx_lock(*mtx)
#define	mtx_trylock(mtx)	_Mtx_trylock(*mtx)
#define	mtx_timedlock(mtx, ts)	_Mtx_timedlock(*mtx, ts)
#define	mtx_unlock(mtx)	_Mtx_unlock(*mtx)
#define	mtx_destroy(mtx)	_Mtx_destroy(*mtx)

#define	thrd_current	_Thrd_id
#define	thrd_detach(thr)	_Thrd_detach(thr)
#define	thrd_join(thr, res)	_Thrd_join(thr, res)
#define	thrd_yield	_Thrd_yield
#endif

/*:::::: функции ::::::::::::::::::::::::::::::::::::::::::::::::::*/

#if _MSC_VER < 1800
thrd_creator_t	cnd_init (cnd_t* cond);
thrd_creator_t	cnd_broadcast (cnd_t* cond);
thrd_creator_t	cnd_signal (cnd_t* cond);
thrd_creator_t	cnd_wait (cnd_t* cond, mtx_t* mtx);
thrd_creator_t	cnd_timedwait (cnd_t* cond, mtx_t* mtx, const struct timespec* ts);
void	cnd_destroy (cnd_t* cond);

thrd_creator_t	mtx_init (mtx_t* mtx, int type);
thrd_creator_t	mtx_lock (mtx_t* mtx);
thrd_creator_t	mtx_trylock (mtx_t* mtx);
thrd_creator_t	mtx_timedlock (mtx_t* mtx, const struct timespec* ts);
thrd_creator_t	mtx_unlock (mtx_t* mtx);
void	mtx_destroy (mtx_t* mtx);

thrd_t	thrd_current ();
thrd_creator_t	thrd_detach (thrd_t thr);
thrd_creator_t	thrd_join (thrd_t thr, int* res);
void	thrd_yield ();
#endif

void	call_once (once_flag* flag, void (* func)());

thrd_creator_t	tss_create (tss_t* key, tss_dtor_t dtor);
thrd_creator_t	tss_memory (tss_t* key);
thrd_creator_t	tss_set (tss_t key, void* val);
void* tss_get (tss_t key);
void	tss_delete (tss_t key);

thrd_creator_t	thrd_init ();
thrd_creator_t	thrd_create (thrd_t* thr, thrd_start_t func, void* arg);
bool	thrd_equal (thrd_t thr1, thrd_t thr2);
int	thrd_sleep (const struct timespec* duration, struct timespec* remaining);
int	thrd_exit (int res);
bool	thrd_return (thrd_t thr, int* res);

void	stdio_lock ();
void	stdio_unlock ();

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

#if defined __cplusplus
};	/* extern "C" */
#endif

#endif  /* THREADS_H */