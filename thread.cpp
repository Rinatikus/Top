/*(C) ������������� � (Copyright �) 2024 ���\
** � ��������� (Pseudonym)                  |
** � ��� ����� ��������(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// thread.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "stdafx.h"
#include <threads.h>

#define	MAX_THREADS	24

using namespace std;

/*-------------------------------------------------------------*/

static once_flag_t	inited;	/* ���� ������������� ������� */

#if defined	MULTITSSVAR
typedef struct _THREAD_SLOT {
	thrd_t	m_id;	/* ������������� ������ */
	bool	m_busy;	/* ���������� ������������� ����� */
	int m_counter;	/* ������ ������ */
} THREAD_SLOT;

#define	counter	var->m_counter
static tss_t	thr_var = 0;	/* ������������� ����� �������� ���������� � ������� */

THREAD_SLOT* thread_var() {
	THREAD_SLOT* vars;
	if (thr_var && (vars = (THREAD_SLOT*)tss_get(thr_var)))
		return vars;
	return NULL;
};

#else
// ���������� ����������
# if defined	MULTIMUTEX	/* ������������ ������ �� ���������� ������ ������� */
static	int	counter = 0;	/* ���������� ������ ������ */
# else`
__declspec(thread)	int	counter = 0;	/* ��������� ������ ������ (TLS) */
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
	cout << _T("������� ��������� � N\t: ");
};

bool	see (int argc, char_t* argv[])
{
	cout << argv[0] << endl;
	cout << _T("������ � N, ��������\t: ������� ���") << endl;
	return true;
};

static mtx_t	mutex;	/* �������� ���������� ������� */

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
	THREAD_SLOT	var_param = { 0 };	/* ��������� �������� ������������ ���� */;
	if (thr_var || tss_create(&thr_var, NULL) == thrd_success)
		tss_set(thr_var, &var_param);
	else
		return false;
	THREAD_SLOT* var = &var_param;
#endif
	static once_flag_t	inited;
	thrd_init();    /* ��������� ��������� ��� ������ ���������� ���������� ���������� */
	call_once(&inited, thread_init);	/* ������������� ���������� ���������� ������������� ������ */
# if defined	MULTIMUTEX	/* ������������ ������ �� ���������� ������ ����� */
	mtx_lock(&mutex);
#endif
	// ��������� ������
	stdio_lock();
	counter++;
# if defined	MULTIMUTEX	/*  ������������ ������ �� ���������� ������ ����� */
	mtx_unlock(&mutex);
#endif
//	stdio_lock();
	cout << _T("������� : ") << counter << endl;
	stdio_unlock();
	// ��������� ������ ������
	*(int*)data = counter;
	// ��� ���������� ������
	return thrd_exit(thrd_success);
}
bool	run ()
{
	int i;
	thrd_t	thread_ids[MAX_THREADS];
	int	thread_ret[MAX_THREADS];
	int	thread_res[MAX_THREADS];
	cout << _T("��������� ������\t: ") << endl;
	for (i = 0; i < MAX_THREADS; i++)
		thrd_create(&thread_ids[i], thread_counter, &thread_res[i]);
	for (i = 0; i < MAX_THREADS; i++)
		thrd_join(thread_ids[i], &thread_ret[i]);
#if !defined	MULTIMUTEX	/* ������������ ������ �� ���������� ������ ����� */
	int	sum = 0;
	for (i = 0; i < MAX_THREADS; i++)
		sum += thread_res[i];
#endif
	stdio_lock();
#if defined	MULTIMUTEX	/* ������������ ������ �� ���������� ������ ����� */
	cout << _T("���������� : ") << counter << endl;
#else
	cout << _T("���������� : ") << sum << endl;
#endif
	stdio_unlock();
	return true;
};

extern "C"
int _cdecl	main (int argc, char_t* argv[])
{
	stdio_lock();	/* ��������� ����� � ����������� ������ �����-������ ��� �������-������� */
	if ( ! init()) return EXIT_FAILURE;	/* ������������� ��������� */
	hello();	/* ����� ��������������� ��������� ��������� */
	if ( ! see(argc, argv)) return EXIT_FAILURE;	/* ����������� ���������� ������� ��������� */
	stdio_unlock();	/* ��������� ����� � ����������� ������ �����-������ ��� �������-������� */
	if ( ! run()) return EXIT_FAILURE;	/* ���������� ��������� ��������� */
		return EXIT_SUCCESS;	/* ���������� ��������� */
};
