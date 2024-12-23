/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// thread.c : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "threads.h"

#define	MAX_THREADS	24
#define	SIG_THREADS	10

bool	init ()
{
	setlocale(LC_ALL, "rus_rus.1251");
# if 0	//(defined CONSOLE) || (defined _CONSOLE)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
# endif
	stdio_lock();
	return true;
};

void	hello ()
{
	printf(_T("Учебная программа № N\t: "));
};

bool	see (int argc, char_t* argv[])
{
	puts(argv[0]);
	puts(_T("Группа № N, учащийся\t: Фамилия Имя"));
	return true;
};

static once_flag_t	inited;	/* флаг инициализации потоков */
static mtx_t	mutex;	/* мьютекс данных потоков */
static cnd_t	condition;	/* условная переменная потоков */

void	thread_done (void) {
	mtx_destroy(&mutex);
	cnd_destroy(&condition);
};

void	thread_init () {
	mtx_init(&mutex, mtx_plain);
	cnd_init(&condition);
	atexit(thread_done);
};

unsigned int _stdcall	thread_decade (void* data) {
	int* counter = (int*)data;
	thrd_init();    /* установка локальных для задачи глобальных переменных библиотеки */
	call_once(&inited, thread_init);	/* инициализация глобальных переменных обслуживающих задачу */
	mtx_lock(&mutex);
	cnd_wait(&condition, &mutex);
	stdio_lock();
	printf(_T("Сигнал\t: %u\n"), *counter);
	stdio_unlock();
	mtx_unlock(&mutex);
	return thrd_exit(thrd_success);
}

unsigned int _stdcall	thread_counter (void* data)
{
	int* counter = (int*)data;
	thrd_init();    /* установка локальных для задачи глобальных переменных библиотеки */
	call_once(&inited, thread_init);	/* инициализация глобальных переменных обслуживающих задачу */
	stdio_lock();
	printf(_T("Счётчик\t: %u\n"), *counter);
	stdio_unlock();
	(*counter)++;
	if (*counter == SIG_THREADS)
		cnd_signal(&condition);
	return thrd_exit(thrd_success);
};

bool	run ()
{
	int i;
	static	int	counter = 0;
	thrd_t	thread_ids[MAX_THREADS];
	int	thread_ret[MAX_THREADS];
	printf(_T("Результат работы алгоритма :\n"));
	thrd_create(&thread_ids[0], thread_decade, &counter);
	stdio_unlock();
	for (i = 1; i < MAX_THREADS; i++)
		thrd_create(&thread_ids[i], thread_counter, &counter);
	for (i = 0; i < MAX_THREADS; i++)
		thrd_join(thread_ids[i], &thread_ret[i]);
	stdio_lock();
	printf(_T("Количество : %u\n"), counter);
	stdio_unlock();
	return true;
};

int _cdecl	main (int argc, char_t* argv[])
{
	if ( ! init()) return EXIT_FAILURE;	/* инициализация программы */
	hello();	/* вывод информационного заголовка программы */
	if ( ! see(argc, argv)) return EXIT_FAILURE;	/* определение параметров запуска программы */
	if ( ! run()) return EXIT_FAILURE;	/* выполнение алгоритма программы */
		return EXIT_SUCCESS;	/* завершение программы */
};
