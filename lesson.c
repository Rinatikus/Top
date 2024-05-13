/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// lesson.c : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	printf(_T("Учебная программа № N\t: "));
};

bool	see (int argc, char_t* argv[])
{
	puts(argv[0]);
	puts(_T("Группа № N, учащийся\t: Фамилия Имя"));
	return true;
};

bool	run ()
{
	printf(_T("Результат работы алгоритма : "));
	printf(_T("Привет Мир !"));
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
