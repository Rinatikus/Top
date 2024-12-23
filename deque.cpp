/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// deque.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include <deque>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

/*
**  Конвертация объектов других типов в string
*/
class sformat
{
protected:
    stringstream ss;

public:
    template <typename T>
    sformat&    operator<< (const T& other) {
        ss << other;
        return *this;
    }

    operator string () {
        return ss.str();
    }
};

bool	init ()
{
	return true;
};

void	hello ()
{
	cout << _T("Учебная программа № 1\t: ");
};

bool	see (int argc, char_t* argv[])
{
	cout << argv[0] << endl;
	cout << _T("Группа № 1, учащийся\t: Киселёв Сергей") << endl;
	return true;
};

bool	run ()
{

    deque<string> user_strings;

    cout << _T("Вводите текст. Введите пустую строку для прекращения.\n");

    string input;

    /*
    ** Читаем ввод, пока не получим пустую строку или EOF,
    ** и запихиваем прочтённые строки в контейнер, попутно
    ** приписывая им их длину и последние два символа.
    */

    while (cout << _T("> "), getline(cin, input), input != _T(""))
    {
        cout << endl;
        user_strings.push_back(sformat()
            << input.length()
            << _T(": ")
            << input
            << _T(" (")
            << ((input.length() > 2) ? (input.substr(input.length() - 2)) : string(_T("")))
            << _T(')'));
    };
    cout << endl;

    /*
    ** Выводим содержимое контейнера, используя стандартный алгоритм copy и ostream_iterator, на
    ** стандартный вывод
    */
    copy(user_strings.begin(), user_strings.end(), ostream_iterator<string, char_t>(cout, _T("\n")));
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
