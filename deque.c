/*(C) ������������� � (Copyright �) 2024 ���\
** � ��������� (Pseudonym)                  |
** � ��� ����� ��������(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// deque.c : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "stdafx.h"
//#include <deque.h>

#define	perror	p_error	/* ���������� ��������������� ������ ������� ������ ��������� �� ������ */

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
	/* �������� ������ �������� ������� */
	x = malloc(sizeof(struct deque_node_t));
	if ( ! x) return NULL;
	/* �������� ������ �������� ������ */
	x->data = malloc(d->typs);
	if ( ! x->data) return NULL;
	/* ����������� ������ */
	memcpy(x->data, data, d->typs);
	/* ������� ������ �������� � ������� */
	x->backward = NULL;
	if (d->count == 0) {	/* ������� ����� */
		x->forward = NULL;
		d->hdr = x;
		d->fin = x;
	}
	else {	/* ��������� ������� � ����� ������� */
		d->hdr->backward = x;
		x->forward = d->hdr;
		d->hdr = x;
	};
	/* ����������� ���������� ��������� */
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
	size_t	len;
	char_t input[40], buffer[40], substr[40];
	deque_t	user_strings;
	if ( ! deque_init(&user_strings, 0))
		perror(_T("�������� ������� :"));
	printf(_T("������� �����. ������� ������ ������ ��� �����������.\n"));

	/*
	** ������ ����, ���� �� ������� ������ ������ ��� EOF,
	** � ���������� ��������� ������ � ���������, �������
	** ���������� �� �� ����� � ��������� ��� �������.
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
			perror(_T("���������� �������� � ������� :"));
	} while (1);

	while ( ! deque_empty(&user_strings)) {
		puts(deque_back(&user_strings));
		deque_pop_back(&user_strings);
	};

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
