/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// thread.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include <threads.h>

#define	MAX_THREADS	24

using namespace std;

/*-------------------------------------------------------------*/

static once_flag_t	inited;	/* флаг инициализации потоков */

#if defined	MULTITSSVAR
typedef struct _THREAD_SLOT {
	thrd_t	m_id;	/* идентификатор потока */
	bool	m_busy;	/* показатель использования слота */
	int m_counter;	/* данные потока */
} THREAD_SLOT;

#define	counter	var->m_counter
static tss_t	thr_var = 0;	/* идентификатор ключа хранения переменных в потоках */

THREAD_SLOT* thread_var() {
	THREAD_SLOT* vars;
	if (thr_var && (vars = (THREAD_SLOT*)tss_get(thr_var)))
		return vars;
	return NULL;
};

#else
// Глобальные переменные
# if defined	MULTIMUTEX	/* использовать мютекс на глобальных данных потоков */
static	int	counter = 0;	/* глобальные данные потока */
# else`
__declspec(thread)	int	counter = 0;	/* локальные данные потока (TLS) */
# endif
#endif

bool	init ()
{
#if !defined seh_help
	setlocale(LC_ALL, "rus_rus.1251");
	locale loc;
	locale::global(loc);
	ios_base::sync_with_stdio(false);
#endif
	return true;
};

void	hello ()
{
	cout << _T("Учебная программа № N\t: ");
};

bool	see (int argc, char_t* argv[])
{
	cout << argv[0] << endl;
	cout << _T("Группа № N, учащийся\t: Фамилия Имя") << endl;
	return true;
};

static mtx_t	mutex;	/* условная переменная потоков */

void	thread_done() {
	mtx_destroy(&mutex);
};

void	thread_init () {
	mtx_init(&mutex, mtx_plain);
	atexit(thread_done);
};

unsigned int _stdcall	thread_counter (void* data)
{
#if defined	MULTITSSVAR
	THREAD_SLOT	var_param = { 0 };	/* параметры счётчика программного кода */;
	if (thr_var || tss_create(&thr_var, NULL) == thrd_success)
		tss_set(thr_var, &var_param);
	else
		return false;
	THREAD_SLOT* var = &var_param;
#endif
	static once_flag_t	inited;
	thrd_init();    /* установка локальных для задачи глобальных переменных библиотеки */
	call_once(&inited, thread_init);	/* инициализация глобальных переменных обслуживающих задачу */
# if defined	MULTIMUTEX	/* использовать мютекс на глобальных данных задач */
	mtx_lock(&mutex);
#endif
	// Обработка данных
	stdio_lock();
	counter++;
# if defined	MULTIMUTEX	/*  использовать мютекс на глобальных данных задач */
	mtx_unlock(&mutex);
#endif
//	stdio_lock();
	cout << _T("Счётчик : ") << counter << endl;
	stdio_unlock();
	// Результат работы задачи
	*(int*)data = counter;
	// Код завершение задачи
	return thrd_exit(thrd_success);
}
bool	run ()
{
	int i;
	thrd_t	thread_ids[MAX_THREADS];
	int	thread_ret[MAX_THREADS];
	int	thread_res[MAX_THREADS];
	cout << _T("Результат работы\t: ") << endl;
	for (i = 0; i < MAX_THREADS; i++)
		thrd_create(&thread_ids[i], thread_counter, &thread_res[i]);
	for (i = 0; i < MAX_THREADS; i++)
		thrd_join(thread_ids[i], &thread_ret[i]);
#if !defined	MULTIMUTEX	/* использовать мютекс на глобальных данных задач */
	int	sum = 0;
	for (i = 0; i < MAX_THREADS; i++)
		sum += thread_res[i];
#endif
	stdio_lock();
#if defined	MULTIMUTEX	/* использовать мютекс на глобальных данных задач */
	cout << _T("Количество : ") << counter << endl;
#else
	cout << _T("Количество : ") << sum << endl;
#endif
	stdio_unlock();
	return true;
};

extern "C"
int _cdecl	main (int argc, char_t* argv[])
{
	stdio_lock();	/* запрещаем вывод в стандартные потоки ввода-вывода для функций-потоков */
	if ( ! init()) return EXIT_FAILURE;	/* инициализация программы */
	hello();	/* вывод информационного заголовка программы */
	if ( ! see(argc, argv)) return EXIT_FAILURE;	/* определение параметров запуска программы */
	stdio_unlock();	/* разрешаем вывод в стандартные потоки ввода-вывода для функций-потоков */
	if ( ! run()) return EXIT_FAILURE;	/* выполнение алгоритма программы */
		return EXIT_SUCCESS;	/* завершение программы */
};
