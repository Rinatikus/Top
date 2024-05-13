/*(C) ������������� � (Copyright �) 2024 ���\
** � ��������� (Pseudonym)                  |
** � ��� ����� ��������(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

// deque.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "stdafx.h"
#include <deque>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

/*
**  ����������� �������� ������ ����� � string
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
	cout << _T("������� ��������� � 1\t: ");
};

bool	see (int argc, char_t* argv[])
{
	cout << argv[0] << endl;
	cout << _T("������ � 1, ��������\t: ������ ������") << endl;
	return true;
};

bool	run ()
{

    deque<string> user_strings;

    cout << _T("������� �����. ������� ������ ������ ��� �����������.\n");

    string input;

    /*
    ** ������ ����, ���� �� ������� ������ ������ ��� EOF,
    ** � ���������� ��������� ������ � ���������, �������
    ** ���������� �� �� ����� � ��������� ��� �������.
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
    ** ������� ���������� ����������, ��������� ����������� �������� copy � ostream_iterator, ��
    ** ����������� �����
    */
    copy(user_strings.begin(), user_strings.end(), ostream_iterator<string, char_t>(cout, _T("\n")));
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
