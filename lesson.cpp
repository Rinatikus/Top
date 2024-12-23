/*(C) ������������� � (Copyright �) 2024 ���\
** � ��������� (Pseudonym)                  |
** � ��� ����� ��������(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// lesson.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "stdafx.h"

using namespace std;

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

bool	run ()
{
	cout << _T("��������� ������\t: ");
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
