/*  AUTOR: Ivan Garavito Garcia */
/*  INFO.: Header para manipular la consola. */
/*  FECHA: 13/09/2001 */
/*  EMAIL: Susaji@email.com */

#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

#define ADVANCED


/*#define MAXSCREENHEIGHT 25 */
/*#define MAXSCREENWIDTH  80 */


/***    VIRTUAL KEYS    ***/
#define VKINTRO   0x0D  /* Enter key */
#define VKESC     0x1B  /* Escape key */
#define VKSPACE   0x20  /* Space key */
#define VKLEFT    0x25  /* Arrow left key */
#define VKUP      0x26  /* Arrow up key */
#define VKRIGHT   0x27  /* Arrow right key */
#define VKDOWN    0x28  /* Arrow down key */


/***    COLORS    ***/
/* Foreground colors */
#define FC_BLACK    0x00
#define FC_DBLUE    0x01
#define FC_DGREEN   0x02
#define FC_DCYAN    0x03
#define FC_DRED     0x04
#define FC_DMAGENTA 0x05
#define FC_BROWN    0x06
#define FC_LGRAY    0x07
#define FC_DGRAY    0x08
#define FC_LBLUE    0x09
#define FC_LGREEN   0x0A
#define FC_LCYAN    0x0B
#define FC_LRED     0x0C
#define FC_LMAGENTA 0x0D
#define FC_YELLOW   0x0E
#define FC_WHITE    0x0F

/* Background colors */
#define BC_BLACK    0x00
#define BC_DBLUE    0x10
#define BC_DGREEN   0x20
#define BC_DCYAN    0x30
#define BC_DRED     0x40
#define BC_DMAGENTA 0x50
#define BC_BROWN    0x60
#define BC_LGRAY    0x70
#define BC_DGRAY    0x80
#define BC_LBLUE    0x90
#define BC_LGREEN   0xA0
#define BC_LCYAN    0xB0
#define BC_LRED     0xC0
#define BC_LMAGENTA 0xD0
#define BC_YELLOW   0xE0
#define BC_WHITE    0xF0
/***  END COLORS  ***/


/*** CELL DEFINITION ***/
typedef struct _CellScreen
{
  char ch;
  int attr;
} CellScreen;

/*typedef _CellScreen CellScreen; */
/*** END CELL DEFINITION ***/


void Clear(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE hOutput;
  DWORD nLen;
  char* ch;
  int n;

  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(hOutput, &csbi);
  ch = malloc(sizeof(char)*csbi.dwSize.X+1);

  csbi.dwCursorPosition.X = csbi.dwCursorPosition.Y = 0;
  for(n = 0; n < csbi.dwSize.X; n++)
    ch[n] = ' ';
  ch[n] = '\0';
  FillConsoleOutputAttribute(hOutput, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, csbi.dwCursorPosition, &nLen);
  for (n = 0; n < csbi.dwSize.Y; n++)
  {
    csbi.dwCursorPosition.Y = n;
    WriteConsoleOutputCharacter(hOutput, &ch[0], csbi.dwSize.X, csbi.dwCursorPosition, &nLen);
  }
  csbi.dwCursorPosition.Y = 0;
  SetConsoleCursorPosition(hOutput, csbi.dwCursorPosition);
  free(ch);
}

void ClearEx(int x, int y, int w, int h)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE hOutput;
  DWORD nLen;
  char ch[120];
  int n;
  
  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(hOutput, &csbi);

  csbi.dwCursorPosition.X = x - 1;
  for(n = 0; (n < csbi.dwSize.X - 1) && (n < w); n++)
    ch[n] = ' ';
  ch[n] = '\0';
  for (n = y - 1; (n < csbi.dwSize.Y - 1) && (n < (y + h - 1)); n++)
  {
    csbi.dwCursorPosition.Y = n;
    FillConsoleOutputAttribute(hOutput, csbi.wAttributes, w, csbi.dwCursorPosition, &nLen);
    WriteConsoleOutputCharacter(hOutput, &ch[0], w, csbi.dwCursorPosition, &nLen);
  }
}

void CEOL(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD nLen;
  char ch[120];
  int n;
  
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

  for (n = 0; n < csbi.dwSize.X - 1; n++)
    ch[n] = ' ';
  ch[n] = '\0';
  csbi.dwCursorPosition.X = 0;

  WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &ch[0], n, csbi.dwCursorPosition, &nLen);
}

void CEOLEx(int nLn)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD nLen;
  char ch[120];
  int n;
  
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

  for (n = 0; n < csbi.dwSize.X - 1; n++)
    ch[n] = ' ';
  ch[n] = '\0';
  csbi.dwCursorPosition.X = 0;
  csbi.dwCursorPosition.Y = nLn;

  WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &ch[0], n, csbi.dwCursorPosition, &nLen);
}

void Delay(int iMilliseconds)
{
  Sleep(iMilliseconds);
}

void DrawBar(int ln, int fc, int bc)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE hOutput;
  COORD cXY;
  DWORD dwlen = 0;

  cXY.X = 0;
  cXY.Y = ln - 1;
  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(hOutput, &csbi);

  FillConsoleOutputAttribute(hOutput, (WORD)(fc | bc), csbi.dwSize.X, cXY, &dwlen);
}

void FlushInputBuffer(void)
{
  FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void FullScreen(void)
{
  keybd_event(VK_MENU, 0, 0, 0);
  keybd_event(VK_RETURN, 0, 0, 0);
  keybd_event(VK_MENU, 0, 2, 0);
  keybd_event(VK_RETURN, 0, 2, 0);
  fflush(stdin);
}

int GetCaret(void)
{
  CONSOLE_CURSOR_INFO cci;

  GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
  return cci.bVisible;
}

int GetCaretSize(void)
{
  CONSOLE_CURSOR_INFO cci;
  
  GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
  return cci.dwSize;
}

char GetCharFromPoint(int x, int y)
{
  HANDLE hOutput;
  COORD XY;
  DWORD nLen;
  char chi[2];
  
  XY.X = x - 1;
  XY.Y = y - 1;
  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  ReadConsoleOutputCharacter(hOutput, &chi[0], 1, XY,  &nLen);
  
  return chi[0];
}

int GetColor(int *fc, int *bc)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  if (fc != NULL)
    *fc = csbi.wAttributes & 0x0F;
  if (bc != NULL)
    *bc = csbi.wAttributes & 0xF0;
  return csbi.wAttributes;
}

int GetColorFromPoint(int x, int y)
{
  HANDLE hOutput;
  COORD XY;
  DWORD nLen;
  WORD clr;
  
  XY.X = x - 1;
  XY.Y = y - 1;
  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  ReadConsoleOutputAttribute(hOutput, &clr, 1, XY,  &nLen);
  
  return (int)clr;
}

CellScreen GetCellScreen(int x, int y)
{
  CellScreen cs;
  
  cs.ch = GetCharFromPoint(x, y);
  cs.attr = GetColorFromPoint(x, y);
  return cs;
}

int GetWndHeight(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.dwSize.Y;
}

void GetWndTitle(char *lpTitle, int cch)
{
  GetConsoleTitle((LPTSTR)lpTitle, (DWORD)cch);
}

int GetWndWidth(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.dwSize.X;
}

void Gotoxy(int x, int y)
{
  COORD XY;

  XY.X = x - 1;
  XY.Y = y - 1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

int ReadVK(void)
{
  DWORD dwER;
  HANDLE hInput;
  INPUT_RECORD ir;
  
  hInput = GetStdHandle(STD_INPUT_HANDLE);
  FlushConsoleInputBuffer(hInput);
  do
  {
    ReadConsoleInput(hInput, &ir, 1, &dwER);
  } while (ir.EventType != KEY_EVENT);
  return ir.Event.KeyEvent.wVirtualKeyCode;
}

void SetCaret(int bVisible)
{
  CONSOLE_CURSOR_INFO cci;
  HANDLE hOutput;

  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleCursorInfo(hOutput, &cci);
  cci.bVisible = bVisible;
  SetConsoleCursorInfo(hOutput, &cci);
}

void SetCaretSize(int nSize)
{
  CONSOLE_CURSOR_INFO cci;
  HANDLE hOutput;

  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleCursorInfo(hOutput, &cci);
  cci.dwSize = nSize;
  SetConsoleCursorInfo(hOutput, &cci);
}

int SetCharOnPoint(int x, int y, char ch)
{
  HANDLE hOutput;
  COORD XY;
  DWORD nLen;
  char chi[2];
  
  XY.X = x - 1;
  XY.Y = y - 1;
  chi[0] = ch;
  chi[1] = '\0';

  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  
  return WriteConsoleOutputCharacter(hOutput, &chi[0], 1, XY,  &nLen);
}

void SetColor(int fc, int bc)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(fc | bc));
}

int SetColorOnPoint(int x, int y, int cl)
{
  HANDLE hOutput;
  COORD XY;
  DWORD nLen;
  WORD clr;
  
  XY.X = x - 1;
  XY.Y = y - 1;
  clr = (WORD)cl;
  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  
  return WriteConsoleOutputAttribute(hOutput, &clr, 1, XY,  &nLen);
}

void SetCellScreen(int x, int y, CellScreen cs)
{ 
  SetCharOnPoint(x, y, cs.ch);
  SetColorOnPoint(x, y, cs.attr);
  return;
}

void SetWndTitle(char *lpTitle)
{
  SetConsoleTitle((LPCTSTR)lpTitle);
}

int ThisConsoleWnd(void)
{
  HWND hW;
  char ch[64], cl[8];
  
  GetConsoleTitle((LPTSTR)ch, (DWORD)64);
  strcpy(cl, "tty");
  if ((hW = FindWindow(cl, &ch[0])) == NULL)
    return 0;
  strcpy(cl, "ttyGrab");
  if ((hW = FindWindowEx(hW, NULL, cl, NULL)) == NULL)
    return 0;
  return (int)hW;
}

int ThisWnd(void)
{
  HWND hW;
  char ch[64], cl[8];
  
  GetConsoleTitle((LPTSTR)ch, (DWORD)64);
  strcpy(cl, "tty");
  if ((hW = FindWindow(cl, &ch[0])) == NULL)
    return 0;
  return (int)hW;
}

int WhereX(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.dwCursorPosition.X + 1;
}

int WhereY(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.dwCursorPosition.Y + 1;
}

void UpdateColorScreen(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE hOutput;
  DWORD nLen;
  COORD XY;
  
  XY.X = XY.Y = 0;
  hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(hOutput, &csbi);

  FillConsoleOutputAttribute(hOutput, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, XY, &nLen);
}
