/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// hello.c : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	printf(_T("Прикладная программа "));
};

bool	see (int argc, char_t* argv[])
{
	int i;
	puts(argv[0]);
	if (argc > 1) {
		puts(_T("Параметры запуска :"));
		for (i = 1; i < argc; i++)
			puts(argv[i]);
	};
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
