/*(C) ������������� � (Copyright �) 2024 ���\
** � ��������� (Pseudonym)                  |
** � ��� ����� ��������(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// hello.c : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "stdafx.h"

bool	init () {
#if U_PLATFORM_IS_LINUX_BASED
	setlocale(LC_ALL, "ru_RU.iso88595@rur");
#else
	setlocale(LC_ALL, "rus_rus.1251");
#endif
	return true;
};

void	hello ()
{
	printf(_T("���������� ��������� "));
};

bool	see (int argc, char_t* argv[])
{
	int i;
	puts(argv[0]);
	if (argc > 1) {
		puts(_T("��������� ������� :"));
		for (i = 1; i < argc; i++)
			puts(argv[i]);
	};
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
