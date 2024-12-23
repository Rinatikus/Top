/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// hello.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	cout << _T("Прикладная программа ");
};

bool	see (int argc, char_t* argv[])
{
	cout << argv[0] << endl;
	if (argc > 1) {
		cout << _T("Параметры запуска :") << endl;
		for (int i = 1; i < argc; i++)
			cout << argv[i] << endl;
	};
	return true;
};

bool	run ()
{
	cout << _T("Результат работы алгоритма : ");
	cout << _T("Привет Мир !");
	return true;
};

extern "C"
int _cdecl	main (int argc, char_t* argv[])
{
	if ( ! init()) return EXIT_FAILURE;	/* инициализация программы */
	hello();	/* вывод информационного заголовка программы */
	if ( ! see(argc, argv)) return EXIT_FAILURE;	/* определение параметров запуска программы */
	if ( ! run()) return EXIT_FAILURE;	/* выполнение алгоритма программы */
	return EXIT_SUCCESS;	/* завершение программы */
};
