/***********************************************************
** Модуль = StdAfx = прикладного приложения
**
** Автор :       Псевдоним
** Компилятор   MSVC ver. 12.0   Дата    13.07.2021
** Назначение :  описание стандартных системных функций
**      и специфичных для всего проекта библиотек
** Примечания :
**      включает часто используемые и неизменные определения
************************************************************
*/

#if (defined _MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if !defined	StdAfx_defined
# define StdAfx_defined

/*:::::: макросы ::::::::::::::::::::::::::::::::::::::::::::::::::*/

/*

#if !defined _SECURE_ATL
# define	_SECURE_ATL	1	// Безопасные шаблонные функции
#endif

#if !defined VC_EXTRALEAN
# define	VC_EXTRALEAN            // Исключите редко используемые компоненты из заголовков Windows
#endif

#define	_CRT_NON_CONFORMING_SWPRINTFS
#define	_ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // некоторые конструкторы CString будут явными

#define	_CRT_SECURE_NO_WARNINGS	// отключает предупреждения функций небезопасного стиля
#define	_SCL_SECURE_NO_WARNINGS	// отключает предупреждения объектов небезопасного стиля

// отключает функцию скрытия некоторых общих и часто пропускаемых предупреждений MFC
#define	_AFX_ALL_WARNINGS
*/


/*::::::::: константы используемых модулей ::::::::::::::::::::::::::*/

#include	"platform.h"
/*
#include	"targetver.h"
#include	"resource.h"
#include	"version.h"
*/

/*:::::: функции стандартных типов данных :::::::::::::::::::::::::::*/

#if (!defined U_PLATFORM) || (U_PLATFORM == U_PF_WINDOWS)
# include	<tchar.h>
#endif
#include	<malloc.h>
#include	<locale.h>
#include	<stdio.h>
#include	<stdlib.h>
#if defined __cplusplus
# include	<locale>
# include	<queue>
# include	<iostream>
# include	<iomanip>
# include	<string>
#endif

/*
#include	<string>
#include	<memory>
#include	<cassert>
#include	<exception>
#include	<stdexcept>
#include	<iostream>
#include	<fstream>
#include	<iomanip>
#include	<iosfwd>
#include	<vector>

#include	<malloc.h>
#include	<memory.h>
#include	<locale.h>
#include	<ctype.h>
#include	<conio.h>
#include	<io.h>
#include	<dirent.h>
#include	<threads.h>
#include	<signal.h>
#include	<setjmp.h>
#include	<stdarg.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>

#include	<crtdbg.h>
*/

/*:::::: функции интерактивного интерфейса ::::::::::::::::::::::::::*/

#if (defined _CONSOLE) || (defined CONSOLE)

#include	<stdio.h>

#elif (defined _WINDOWS) || (defined WINDOWS)

#define WIN32_LEAN_AND_MEAN	/* отключаем редко используемые определения */
#include	<windows.h>
/*
#include	<windowsx.h>
#include	<commctrl.h>
#include	<commdlg.h>
#include	<htmlhelp.h>
#include	<shellapi.h>

#include	<afxwin.h>         // основные и стандартные компоненты MFC
#include	<afxext.h>         // расширения MFC
#include	<afxdisp.h>        // классы автоматизации MFC
#if !defined _AFX_NO_OLE_SUPPORT
# include	<afxdtctl.h>           // поддержка MFC для типовых элементов управления Internet Explorer 4
#endif
#if !defined _AFX_NO_AFXCMN_SUPPORT
# include	<afxcmn.h>                     // поддержка MFC для типовых элементов управления Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // поддержка MFC для типовых элементов панелей инструментов
#include <afxcview.h>     // поддержка MFC для отображения древовидных структур данных
#include <afxhtml.h>     // поддержка MFC для отображения гипертекстовых страниц
#include <afxsock.h>     // поддержка MFC соединений через интранет-порты

*/

#endif

/*:::::: модули прикладных библиотек ::::::::::::::::::::::::::::::::*/

/*

#include	<strsafe.h>

#if defined	_DEBUG
# undef	THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/*::::::::::::: Типы из словаря предметной области ::::::::::::::::*/

# if (!defined __cplusplus) && (!defined __bool_true_false_are_defined)
typedef	char	bool;
# endif
# if defined UNICODE
typedef	wchar_t	char_t;
# else
typedef	char	char_t;
# endif

#if (defined U_PLATFORM) && (U_PLATFORM != U_PF_WINDOWS)
typedef	char_t	TCHAR;
typedef	char_t	_TCHAR;
#endif

/*:::::: функции поддержки обработки исключений :::::::::::::::::::::*/

#if (defined  seh_help) && ((!defined WinMain) && (!defined main))	/* если нужно включить обработку исключений */
# if (defined WINDOWS) || (defined _WINDOWS)
#  define	WinMain	cWinMain
# else
#  define	main	cmain
# endif
#endif

#if defined __cplusplus
extern "C" {
#endif

char_t* str_error (int errnum);
void	p_error (const char_t* string);

#if defined __cplusplus
};	/* extern "C" */
#endif


/*:::::: макросы прикладной программы :::::::::::::::::::::::::::::::*/

#if !defined NO_MT
# define	MULTITHREAD	/* поддержка параллельных вычислительных процессов */
# define	MULTITSSVAR	/* использовать локальные данные потоков */
# define	MULTISTRATAGY	/* использовать стратегию многопоточности */
# define	THREADS	thr_num	/* количество запущенных потоков */
# if !defined MULTITSSVAR	/* использовать локальные данные потоков */
//#  define	MULTIMUTEX	/* использовать мютекс на глобальных данных потоков */
# endif
#else
# define	THREADS	1
#endif

#if !defined INITCONTANERSIZE	/* начальное количество элементов массива */
# define	INITCONTANERSIZE	30
#endif

#if (defined _CONSOLE) || (defined CONSOLE)
# if !defined EXIT_SUCCESS
#  define	EXIT_SUCCESS	0
# endif
# if !defined EXIT_FAILURE
#  define	EXIT_FAILURE	0
# endif
#endif

#if U_PLATFORM == U_PF_LINUX
# define  _cdecl
#endif

# if (!defined __cplusplus) && (!defined __bool_true_false_are_defined)
#  define	false	0
#  define	true	~false
# endif
# if !defined _T
#  if defined UNICODE
#   define	_T(x)	(char_t *)L##x
#  else
#   define	_T(x)	x
#  endif
# endif

#if (defined __WATCOMC__) && ((defined UNICODE) || (defined _UNICODE))
# define ultoa   _ultot
# define ltoa    _ltot
# define atol    _ttol
# define strlen  _tcslen
# define strcpy  _tcscpy
# define strncpy    wcsncpy
# define strcat  _tcscat
# define strchr  _tcschr
# define sprintf  wsprintf
# define stricmp _wcsicmp
# define sscanf  swscanf
#endif

#if (defined __POCC__) && ((defined UNICODE) || (defined _UNICODE))
# define ultoa   _ultot
# undef	 atol
# define atol    _ttol
# define strlen  wcslen
# define strcpy  wcscpy
# define strncpy wcsncpy
# define strcat  wcscat
# define strcmp  wcscmp
# define strchr  wcschr
# define sprintf wsprintf
#endif

#if (!defined UNICODE) && (!defined _UNICODE)
# define     subcmp(buf1, buf2, count)     memcmp (buf1, buf2, count * sizeof(cap_t))
# define     subcpy(dst, src, count)     memcpy (dst, src, count * sizeof(cap_t))
# define     subchr(buf, lenght, sim)     memchr (buf, lenght * sizeof(cap_t), sim)
# define     subrchr(buf, lenght, sim)     memrchr (buf, lenght * sizeof(cap_t), sim)
#else
# undef	 _MBCS
#endif

#define     strbck1(str)     strcpy(str, &str[1])
#define     zapstr(str,n)     strcpy(str, str + n)
#define     lastchar(str)     *(cap_t*)(str + strlen(str) - 1)
#define     strsize(str)     ((strlen(str) + 1) * sizeof(cap_t))

# if !defined STRSIZE
#define	STRSIZE(str)	(_countof(str) - 1)
# endif

#if (defined UNICODE) || (defined _UNICODE)
# define	tcout	wcout
# define	cout	wcout
# define	cin		wcin
# define	string  wstring
# define	stringstream	wstringstream
# define	strcpy_s	wcscpy_s
# define	puts(str)  wprintf(str); wprintf(L"\n")
# define	printf  wprintf
# define	gets_s	_getws_s
# define	sprintf_s	swprintf_s
# define	scanf	wscanf
# define	scanf_s	wscanf_s
# define	strlen	wcslen
# define	strerror	_wcserror
# if (!defined seh_help) && (!defined U_PLATFORM_IS_LINUX_BASED)
#  define	main  wmain
# endif
#else
#  define tcout cout
#endif


#endif	// !defined	StdAfx_defined
