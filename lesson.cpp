/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// lesson.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	cout << _T("Учебная программа № N\t: ");
};

bool	see (int argc, char_t* argv[])
{
	cout << argv[0] << endl;
	cout << _T("Группа № N, учащийся\t: Фамилия Имя") << endl;
	return true;
};

bool	run ()
{
	cout << _T("Результат работы\t: ");
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
