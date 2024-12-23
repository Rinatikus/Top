/*(C) Собственность © (Copyright ©) 2024 год\
** © Псевдоним (Pseudonym)                  |
** © Все права защищены(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

#include "stdafx.h"

#if (defined WINDOWS) || (defined _WINDOWS)
//#  if _MFC_VER > 0x700
# define INTC3D	/* элементы управления в трёхмерном стиле */
//#  endif
#endif

#ifdef _MSC_VER
# pragma comment (user,"(KSV) author Adamanteus.")
# if defined INTC3D	/* элементы управления в трёхмерном стиле */
#  include <commctrl.h>
#  pragma comment(lib, "comctl32.lib")
#  if defined _M_IX86
#   pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#  elif defined _M_IA64
#   pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#  elif defined _M_X64
#   pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#  else
#   pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#  endif
# endif
#endif

#if defined seh_help

#include <exception>
#include <stdexcept>
#include <setjmp.h>

/*-------------------------------------------------------------*/
/*-- настройки определяющие функциональность данного модуля ---*/
/*-------------------------------------------------------------*/

/*#define INTNDD	/* без отображения диалоговых элементов */
/*#define LIBSAL	/* инициализация всех строк библиотек целиком */
/*#define FPUINI	/* инициализация математического сопроцессора */
/*#define FPUFIN	/* инициализация режима обработки исключений сопроцессора */
#define SETLOC	/* инициализация локали приложения */
#if U_PLATFORM_IS_LINUX_BASED
# define SETLOC_LOCALE	"RU_RU.CP1251"	/* задание локали инициализации приложения */
#else
# define SETLOC_LOCALE	"rus_rus.1251"	/* задание локали инициализации приложения */
#endif
/*#define FNTSIZ	18	/* установка размера шрифта консольного приложения */
/*#define FNTSIZ_FACENAME	L"Lucida Console"	/* установка размера шрифта консольного приложения */
/*#define SEHINT	/* инициализация режима обработки прерываний */
/*#define SAMSIG	/* инициализация режима обработки программных сигналов */
/*#define SAMKIL	/* инициализация режима обработки сигнала принудительного завершения программы */
/*#define SAMQIT	/* инициализация режима игнорирования сигнала завершения программы */

#if (defined _DEBUG) && ! ((defined SAMSIG) || (defined LIBSAM))
# define SAMSIG	/* инициализация режима обработки программных сигналов */
#endif

/*-------------------------------------------------------------*/
/*-- настройки определяющие размещение библиотечных ресурсов --*/
/*-------------------------------------------------------------*/

/*#define	STRVAR	/* строки размещаются во внутренних переменных */
/*#define	STRRES	/* строки размещаются в ресурсной секции строк модуля */
/*#define	STRMES	/* строки размещаются в ресурсной секции сообщений модуля */

/*#define	ICOVAR	/* пиктограммы размещаются во внутренних переменных */
/*#define	ICORES	/* пиктограммы размещаются в ресурсной секции модуля */


#if (defined _WIN32) || (defined _WIN64)
# include <windows.h>
#endif

#if (defined main) || (defined WinMain)	// если финальная версия проекта

// удаление макроопределения проекта
# undef	puts
# undef	main
# undef	WinMain

#if (defined UNICODE) || (defined _UNICODE)
# define	main	wmain
#endif

// объявление главной функции программы на языке Си
#if (defined WINDOWS) || (defined _WINDOWS)
extern "C" int _stdcall cWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#else
extern "C" int _cdecl	cmain (int argc, char_t *argv[]);
#endif

extern "C" {
#if (!defined U_PLATFORM) || U_PLATFORM_HAS_WIN32_API

char_t* str_error (errno_t errnum)
{
	static	char_t	buf[BUFSIZ];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		errnum,	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)buf,	BUFSIZ - 1, NULL);
	return buf;
};

# undef	strerror
# define	strerror	str_error

#else

# define	str_error	strerror

#endif

#if (defined CONSOLE) || (defined _CONSOLE)

# define	get_errno	*_errno

void	p_error (const char_t* format, ...)
{
#if 0
 printf(_T("\n%s -> %s\n"), format, strerror(errno));
#else
 va_list args;
 va_start(args, format);
 vprintf(format, args);
 printf(_T(" -> %s\n"), strerror(get_errno()));
 va_end(args);
#endif
//	exit(EXIT_FAILURE);
};
#endif

};
using namespace std;

#if defined	FNTSIZ	/* установка размера шрифта консольного приложения */
# if (defined CONSOLE) || (defined _CONSOLE)

static void	setFontSize (int FontSize) {
    CONSOLE_FONT_INFOEX info = {0};
    info.cbSize       = sizeof(info);
    info.dwFontSize.Y = FontSize; // leave X as zero
    info.FontWeight   = FW_NORMAL;
#  if defined FNTSIZ_FACENAME
    wcscpy_s(info.FaceName, _countof(info.FaceName) -1, FNTSIZ_FACENAME);
#  endif
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
};

# endif
#endif

#if defined SETLOC	/* инициализация локали приложения */

static void	setProgLoca () {
# if defined SETLOC_LOCALE
	setlocale(LC_ALL, SETLOC_LOCALE);
# endif
	// Инициализируем объект локали значениями по-умолчанию
	locale loc;
	// По-умолчанию, если не указано иного, используется кодировка (C Locale)
	// Указываем везде использовать её в объекте глобальной локали
	locale::global(loc);
	// По-умолчанию стандартные потоки C++ (cin, cout, cerr)
	// работают как врапперы вокруг stdin, stdout и stderr, и не используют
	// фасеты для преобразования кодировок. Чтобы задействовать фасеты,
	// необходимо отключить синхронизацию со стандартными потоками ввода-вывода.
# if (defined CONSOLE) || (defined _CONSOLE)
	ios_base::sync_with_stdio(false);
#  if (!defined U_PLATFORM) || U_PLATFORM_HAS_WIN32_API
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#  endif
# endif
}
#endif

/////////////////////////////////////////////////////////////////
//
// Функция  : main (int argc, char_t *argv[])
//
// Параметры :
//	argc	- количество аргументов командной строки
//	argv	- отдельные аргументы командной строки
//
//	или
//
// Функция : WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//
// Параметры :
//	hInstance	- дескриптор копии программы
//	hPrevInstance	    - дескриптор предыдущей копии программы
//	lpCmdLine	- полнные аргументы командной строки
//	nCmdShow	- команда отображения окна программы
//
// Заметки :
// замена главной функции программы для обработки
// исключений и проверки лицензионной информации
//
// Возвращает :
//	код возврата из программы на языке Си
//
// Побочные эффекты :
// перехватывает все стандартные Си++ исключения
// и системные исключения операционной системы
//
// Использование :
// добавить модуль в программу и определить
// макроподстановку для её главной функции
//	/Dseh_help
//	или
//	/Dmain=cmain
//	или
//	/DWinMain=cWinMain

//---------------------------------------------------------------

#if (defined WINDOWS) || (defined _WINDOWS)
extern "C" int _stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

#else
extern "C" int _cdecl	main (int argc, char_t *argv[]) {

#if defined SETLOC	/* инициализация локали приложения */
 setProgLoca();
#endif
# if defined SEHINT	// инициализация режима обработки прерываний
 setintmod();	// установить обработчики перехватывающие системные исключения
# endif
# if defined FPUINI	// инициализация математического сопроцессора
#  if defined FPUFIN	// инициализация режима обработки исключений сопроцессора
 feninit();	// использовать исключения при вычислениях сопроцессора
#  else
 feinit();	// использовать математический сопроцессор без исключений
#  endif
# endif
#if defined	FNTSIZ	/* установка размера шрифта консольного приложения */
 setFontSize(FNTSIZ);
# endif
#endif

#if defined SEHINT	// режим обработки прерываний
 try    // участок кода критических операций
 {
#endif
#if defined INTC3D	// элементы управления в трёхмерном стиле
	InitCommonControls();
#endif
#if (defined WINDOWS) || (defined _WINDOWS)
	return cWinMain (hInstance, hPrevInstance, lpCmdLine, nCmdShow);	// вызов главной функции программы на языке Си
#else
	return cmain (argc, argv);	// вызов главной функции программы на языке Си
#endif
#if defined SEHINT	// режим обработки прерываний
 }
 catch (exception &e) { // отображение описания исключения
# if (defined WINDOWS) || (defined _WINDOWS)
	char_t	str[256];
	MessageBox(NULL, e.what(), e.name(), MB_OK | MB_ICONSTOP);
# else
	puts("");
	puts(e.what());
# endif
 };
#endif
 return EXIT_FAILURE;
};

#endif

#endif	// seh_help

/*:::::::: Оптимизация и разработка :::::::::::::::::::::::::::::
-----------------------------------------------------------------
**
**
**
*/
