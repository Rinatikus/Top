/*(C) ������������� � (Copyright �) 2024 ���\
** � ��������� (Pseudonym)                  |
** � ��� ����� ��������(All rights reserved)|
\* * * * * * * * * * * * * * * * * * * * * */

#include "stdafx.h"

#if (defined WINDOWS) || (defined _WINDOWS)
//#  if _MFC_VER > 0x700
# define INTC3D	/* �������� ���������� � ��������� ����� */
//#  endif
#endif

#ifdef _MSC_VER
# pragma comment (user,"(KSV) author Adamanteus.")
# if defined INTC3D	/* �������� ���������� � ��������� ����� */
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
/*-- ��������� ������������ ���������������� ������� ������ ---*/
/*-------------------------------------------------------------*/

/*#define INTNDD	/* ��� ����������� ���������� ��������� */
/*#define LIBSAL	/* ������������� ���� ����� ��������� ������� */
/*#define FPUINI	/* ������������� ��������������� ������������ */
/*#define FPUFIN	/* ������������� ������ ��������� ���������� ������������ */
#define SETLOC	/* ������������� ������ ���������� */
#if U_PLATFORM_IS_LINUX_BASED
# define SETLOC_LOCALE	"RU_RU.CP1251"	/* ������� ������ ������������� ���������� */
#else
# define SETLOC_LOCALE	"rus_rus.1251"	/* ������� ������ ������������� ���������� */
#endif
/*#define FNTSIZ	18	/* ��������� ������� ������ ����������� ���������� */
/*#define FNTSIZ_FACENAME	L"Lucida Console"	/* ��������� ������� ������ ����������� ���������� */
/*#define SEHINT	/* ������������� ������ ��������� ���������� */
/*#define SAMSIG	/* ������������� ������ ��������� ����������� �������� */
/*#define SAMKIL	/* ������������� ������ ��������� ������� ��������������� ���������� ��������� */
/*#define SAMQIT	/* ������������� ������ ������������� ������� ���������� ��������� */

#if (defined _DEBUG) && ! ((defined SAMSIG) || (defined LIBSAM))
# define SAMSIG	/* ������������� ������ ��������� ����������� �������� */
#endif

/*-------------------------------------------------------------*/
/*-- ��������� ������������ ���������� ������������ �������� --*/
/*-------------------------------------------------------------*/

/*#define	STRVAR	/* ������ ����������� �� ���������� ���������� */
/*#define	STRRES	/* ������ ����������� � ��������� ������ ����� ������ */
/*#define	STRMES	/* ������ ����������� � ��������� ������ ��������� ������ */

/*#define	ICOVAR	/* ����������� ����������� �� ���������� ���������� */
/*#define	ICORES	/* ����������� ����������� � ��������� ������ ������ */


#if (defined _WIN32) || (defined _WIN64)
# include <windows.h>
#endif

#if (defined main) || (defined WinMain)	// ���� ��������� ������ �������

// �������� ���������������� �������
# undef	puts
# undef	main
# undef	WinMain

#if (defined UNICODE) || (defined _UNICODE)
# define	main	wmain
#endif

// ���������� ������� ������� ��������� �� ����� ��
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

#if defined	FNTSIZ	/* ��������� ������� ������ ����������� ���������� */
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

#if defined SETLOC	/* ������������� ������ ���������� */

static void	setProgLoca () {
# if defined SETLOC_LOCALE
	setlocale(LC_ALL, SETLOC_LOCALE);
# endif
	// �������������� ������ ������ ���������� ��-���������
	locale loc;
	// ��-���������, ���� �� ������� �����, ������������ ��������� (C Locale)
	// ��������� ����� ������������ � � ������� ���������� ������
	locale::global(loc);
	// ��-��������� ����������� ������ C++ (cin, cout, cerr)
	// �������� ��� �������� ������ stdin, stdout � stderr, � �� ����������
	// ������ ��� �������������� ���������. ����� ������������� ������,
	// ���������� ��������� ������������� �� ������������ �������� �����-������.
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
// �������  : main (int argc, char_t *argv[])
//
// ��������� :
//	argc	- ���������� ���������� ��������� ������
//	argv	- ��������� ��������� ��������� ������
//
//	���
//
// ������� : WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//
// ��������� :
//	hInstance	- ���������� ����� ���������
//	hPrevInstance	    - ���������� ���������� ����� ���������
//	lpCmdLine	- ������� ��������� ��������� ������
//	nCmdShow	- ������� ����������� ���� ���������
//
// ������� :
// ������ ������� ������� ��������� ��� ���������
// ���������� � �������� ������������ ����������
//
// ���������� :
//	��� �������� �� ��������� �� ����� ��
//
// �������� ������� :
// ������������� ��� ����������� ��++ ����������
// � ��������� ���������� ������������ �������
//
// ������������� :
// �������� ������ � ��������� � ����������
// ���������������� ��� � ������� �������
//	/Dseh_help
//	���
//	/Dmain=cmain
//	���
//	/DWinMain=cWinMain

//---------------------------------------------------------------

#if (defined WINDOWS) || (defined _WINDOWS)
extern "C" int _stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

#else
extern "C" int _cdecl	main (int argc, char_t *argv[]) {

#if defined SETLOC	/* ������������� ������ ���������� */
 setProgLoca();
#endif
# if defined SEHINT	// ������������� ������ ��������� ����������
 setintmod();	// ���������� ����������� ��������������� ��������� ����������
# endif
# if defined FPUINI	// ������������� ��������������� ������������
#  if defined FPUFIN	// ������������� ������ ��������� ���������� ������������
 feninit();	// ������������ ���������� ��� ����������� ������������
#  else
 feinit();	// ������������ �������������� ����������� ��� ����������
#  endif
# endif
#if defined	FNTSIZ	/* ��������� ������� ������ ����������� ���������� */
 setFontSize(FNTSIZ);
# endif
#endif

#if defined SEHINT	// ����� ��������� ����������
 try    // ������� ���� ����������� ��������
 {
#endif
#if defined INTC3D	// �������� ���������� � ��������� �����
	InitCommonControls();
#endif
#if (defined WINDOWS) || (defined _WINDOWS)
	return cWinMain (hInstance, hPrevInstance, lpCmdLine, nCmdShow);	// ����� ������� ������� ��������� �� ����� ��
#else
	return cmain (argc, argv);	// ����� ������� ������� ��������� �� ����� ��
#endif
#if defined SEHINT	// ����� ��������� ����������
 }
 catch (exception &e) { // ����������� �������� ����������
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

/*:::::::: ����������� � ���������� :::::::::::::::::::::::::::::
-----------------------------------------------------------------
**
**
**
*/
