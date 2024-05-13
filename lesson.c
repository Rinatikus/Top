/*(C) ������������� � (Copyright �) 2024 ���\
** � ��������� (Pseudonym)                  |
** � ��� ����� ��������(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// lesson.c : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "stdafx.h"

bool	init ()
{
	setlocale(LC_ALL, "rus_rus.1251");
# if 0	//(defined CONSOLE) || (defined _CONSOLE)
	SetConsoleCP(1251);
# endif
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

bool	run ()
{
	printf(_T("��������� ������ ��������� : "));
	printf(_T("������ ��� !"));
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
