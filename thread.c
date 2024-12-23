/*(C) ������������� � (Copyright �) 2024 ���\
** � ��������� (Pseudonym)                  |
** � ��� ����� ��������(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// thread.c : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
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
	printf(_T("������� ��������� � N\t: "));
};

bool	see (int argc, char_t* argv[])
{
	puts(argv[0]);
	puts(_T("������ � N, ��������\t: ������� ���"));
	return true;
};

static once_flag_t	inited;	/* ���� ������������� ������� */
static mtx_t	mutex;	/* ������� ������ ������� */
static cnd_t	condition;	/* �������� ���������� ������� */

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
	thrd_init();    /* ��������� ��������� ��� ������ ���������� ���������� ���������� */
	call_once(&inited, thread_init);	/* ������������� ���������� ���������� ������������� ������ */
	mtx_lock(&mutex);
	cnd_wait(&condition, &mutex);
	stdio_lock();
	printf(_T("������\t: %u\n"), *counter);
	stdio_unlock();
	mtx_unlock(&mutex);
	return thrd_exit(thrd_success);
}

unsigned int _stdcall	thread_counter (void* data)
{
	int* counter = (int*)data;
	thrd_init();    /* ��������� ��������� ��� ������ ���������� ���������� ���������� */
	call_once(&inited, thread_init);	/* ������������� ���������� ���������� ������������� ������ */
	stdio_lock();
	printf(_T("�������\t: %u\n"), *counter);
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
	printf(_T("��������� ������ ��������� :\n"));
	thrd_create(&thread_ids[0], thread_decade, &counter);
	stdio_unlock();
	for (i = 1; i < MAX_THREADS; i++)
		thrd_create(&thread_ids[i], thread_counter, &counter);
	for (i = 0; i < MAX_THREADS; i++)
		thrd_join(thread_ids[i], &thread_ret[i]);
	stdio_lock();
	printf(_T("���������� : %u\n"), counter);
	stdio_unlock();
	return true;
};

int _cdecl	main (int argc, char_t* argv[])
{
	if ( ! init()) return EXIT_FAILURE;	/* ������������� ��������� */
	hello();	/* ����� ��������������� ��������� ��������� */
	if ( ! see(argc, argv)) return EXIT_FAILURE;	/* ����������� ���������� ������� ��������� */
	if ( ! run()) return EXIT_FAILURE;	/* ���������� ��������� ��������� */
		return EXIT_SUCCESS;	/* ���������� ��������� */
};
