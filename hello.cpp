/*(C) ������������� � (Copyright �) 2024 ���\
** � ��������� (Pseudonym)                  |
** � ��� ����� ��������(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// hello.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "stdafx.h"

using namespace std;

bool	init ()
{
	setlocale(LC_ALL, "rus_rus.1251");
	locale loc;
	locale::global(loc);
	ios_base::sync_with_stdio(false);
# if 0	//(defined CONSOLE) || (defined _CONSOLE)
	SetConsoleCP(1251);
# endif
	return true;
};

void	hello ()
{
	cout << _T("���������� ��������� ");
};

bool	see (int argc, char_t* argv[])
{
	cout << argv[0] << endl;
	if (argc > 1) {
		cout << _T("��������� ������� :") << endl;
		for (int i = 1; i < argc; i++)
			cout << argv[i] << endl;
	};
	return true;
};

bool	run ()
{
	cout << _T("��������� ������ ��������� : ");
	cout << _T("������ ��� !");
	return true;
};

extern "C"
int _cdecl	main (int argc, char_t* argv[])
{
	if ( ! init()) return EXIT_FAILURE;	/* ������������� ��������� */
	hello();	/* ����� ��������������� ��������� ��������� */
	if ( ! see(argc, argv)) return EXIT_FAILURE;	/* ����������� ���������� ������� ��������� */
	if ( ! run()) return EXIT_FAILURE;	/* ���������� ��������� ��������� */
	return EXIT_SUCCESS;	/* ���������� ��������� */
};
