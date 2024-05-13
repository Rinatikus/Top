/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// queue.c : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include <queue.h>

#define	perror	p_error	/* используем локализоваанный аналог функции вывода сообщения об ошибке */

#ifndef QUEUE_H

typedef	size_t	qai_t;

struct queue_node_t
{
	void* data;
	struct queue_node_t* forward;
};


typedef struct queue_
{
	struct queue_node_t	*hdr, *fin;
	qai_t	count;
	size_t	typs;
} queue_t;

bool	queue_init (queue_t* q, short typesize)
{
	if ((q->hdr = malloc(sizeof(struct queue_node_t))) == NULL)
		return false;

	q->hdr->data = NULL;
	q->fin = q->hdr;
	q->count = 0;
	q->typs = typesize;
	return true;
};

void*	queue_front (queue_t* q) { return q->hdr->data; };
bool	queue_empty (queue_t* q) { return q->count == 0; /* || q->hdr == NULL || q->fin == NULL; */ };

void* queue_push_back (queue_t* q, const void* data)
{
	struct queue_node_t* x;
	/* создание нового элемента очереди */
	x = malloc(sizeof(struct queue_node_t));
	if ( ! x) return NULL;
	/* создание нового элемента данных */
	x->data = malloc(q->typs);
	if ( ! x->data) return NULL;
	/* копирование данных */
	memcpy(x->data, data, q->typs);
	/* вставка нового элемента в очередь */
	x->forward = NULL;
	if (q->count == 0) {	/* очередь пуста */
		q->hdr = x;
		q->fin = x;
	}
	else {	/* добавляем элемент в конец очереди */
		q->fin->forward = x;
		q->fin = x;
	};
	/* увеличиваем количество элементов */
	q->count++;
	return x->data;
};

bool	queue_pop_front (queue_t* q)
{
	struct queue_node_t*	x;
	if (queue_empty(q)) return false;
	x = q->hdr;
	free(x->data);
	q->hdr = (q->hdr)->forward;
	free(x);
	q->count--;
	return true;
};
#endif

bool	init ()
{
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
	queue_t	user_strings;
	if ( ! queue_init(&user_strings, 0))
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
		if ( ! queue_push_back(&user_strings, buffer))
			perror(_T("Добавление элемента в очередь :"));
	} while (1);

	while ( ! queue_empty(&user_strings)) {
		puts(queue_front(&user_strings));
		queue_pop_front(&user_strings);
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
