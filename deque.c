/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// deque.c : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
//#include <deque.h>

#define	perror	p_error	/* используем локализоваанный аналог функции вывода сообщения об ошибке */

#ifndef DEQUE_H

typedef	size_t	dai_t;

struct deque_node_t
{
	void* data;
	struct deque_node_t	*forward, *backward;
};

typedef struct deque_
{
	struct deque_node_t	*hdr, *fin;
	dai_t	count;
	size_t	typs;
} deque_t;


bool	deque_init (deque_t* d, short typesize)
{
	if ((d->hdr = malloc(sizeof(struct deque_node_t))) == NULL)
		return false;

	d->hdr->data = NULL;
	d->fin = d->hdr;
	d->count = 0;
	d->typs = typesize;
	return true;
};

void*	deque_back (deque_t* d) { return d->fin->data; };
bool	deque_empty (deque_t* d) { return d->count == 0; /* || d->hdr == NULL || d->fin == NULL; */ };

void* deque_push_front (deque_t* d, const void* data)
{
	struct deque_node_t* x;
	/* создание нового элемента очереди */
	x = malloc(sizeof(struct deque_node_t));
	if ( ! x) return NULL;
	/* создание нового элемента данных */
	x->data = malloc(d->typs);
	if ( ! x->data) return NULL;
	/* копирование данных */
	memcpy(x->data, data, d->typs);
	/* вставка нового элемента в очередь */
	x->backward = NULL;
	if (d->count == 0) {	/* очередь пуста */
		x->forward = NULL;
		d->hdr = x;
		d->fin = x;
	}
	else {	/* добавляем элемент в конец очереди */
		d->hdr->backward = x;
		x->forward = d->hdr;
		d->hdr = x;
	};
	/* увеличиваем количество элементов */
	d->count++;
	return x->data;
};

bool	deque_pop_back (deque_t* d)
{
	struct deque_node_t* x;
	if (deque_empty(d)) return false;
	x = d->fin;
	free(x->data);
	d->fin = (d->fin)->backward;
	if (d->fin)
		d->fin->forward = NULL;
	free(x);
	d->count--;
	return true;
};
#endif


bool	init ()
{
	setlocale(LC_ALL, "rus_rus.1251");
	//localeconv()->console_sync = false;
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
	size_t	len;
	char_t input[40], buffer[40], substr[40];
	deque_t	user_strings;
	if ( ! deque_init(&user_strings, 0))
		perror(_T("Создание очереди :"));
	printf(_T("Вводите текст. Введите пустую строку для прекращения.\n"));

	/*
	** Читаем ввод, пока не получим пустую строку или EOF,
	** и запихиваем прочтённые строки в контейнер, попутно
	** приписывая им их длину и последние два символа.
	*/
	do
	{
		printf(_T("> "));
		gets_s(input, STRSIZE(input));
		len = strlen(input);
		if ( ! len) break;
		if (len > 2) {
			substr[0] = input[len - 2];
			substr[1] = input[len - 1];
			substr[2] = _T('\0');
		}
		else
			substr[0] = _T('\0');
		sprintf_s(buffer, STRSIZE(buffer), _T("%u: %s (%s)"), strlen(input), input, substr);
		user_strings.typs = (strlen(buffer) + 1) * sizeof(char_t);
		if ( ! deque_push_front(&user_strings, buffer))
			perror(_T("Добавление элемента в очередь :"));
	} while (1);

	while ( ! deque_empty(&user_strings)) {
		puts(deque_back(&user_strings));
		deque_pop_back(&user_strings);
	};

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
