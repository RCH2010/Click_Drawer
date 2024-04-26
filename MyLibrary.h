#include<windows.h>
#include<bits/stdc++.h>
#pragma comment(lib, "winmm.lib")

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 


HCRYPTPROV prov;
HWND hwnd = GetDesktopWindow();
HDC hdc = GetWindowDC(hwnd);
POINT cursor;
int cursor_freq = 0;
int cx = GetSystemMetrics(SM_CXSCREEN);
int cy = GetSystemMetrics(SM_CYSCREEN);


using namespace std;
void full_screen()
{   
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);            
    int cy = GetSystemMetrics(SM_CYSCREEN);           
    LONG l_WinStyle = GetWindowLong(hwnd,GWL_STYLE);   
    SetWindowLong(hwnd,GWL_STYLE,(l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}
void gotoxy(short x,short y) {
    COORD pos={x,y};
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleCursorPosition(hOut,pos); 
}
void SetColorAndBackground(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void Typer(string totype, int sleeptime,bool isendl) {
    int len = totype.length();
    for (int i = 0; i < len; i++) {
        cout << totype[i];
        Sleep(sleeptime);
    }if (isendl)cout << endl;
}
int ClrScr(){
	gotoxy(0,0);
	for(int i=0;i<100;i++){
		for(int i=0;i<100;i++){
			cout<<"  ";
		}cout<<endl;
	}gotoxy(0,0);
}
void ErrorIcon(int looptimes,bool ShowLooptimes){
	int j=0;
	for (int i = 0; i < looptimes; i++)
	{
			cout<<"\rLoop: "<<j+1<<" of "<<looptimes;
			GetCursorPos(&cursor);
			DrawIcon(hdc, cursor.x * 1.75, cursor.y * 1.75, LoadIcon(NULL, IDI_ERROR));
			Sleep(0.5);
			j++;
	}
}
void WarningIcon(int looptimes,bool ShowLooptimes){
	int j=0;
	for (int i = 0; i < looptimes; i++)
	{
			if(ShowLooptimes)cout<<"\rLoop: "<<j+1<<" of "<<looptimes;
			GetCursorPos(&cursor);
			DrawIcon(hdc, cursor.x * 1.75, cursor.y * 1.75, LoadIcon(NULL, IDI_WARNING));
			Sleep(0.5);
			j++;
	}
}
void InfoIcon(int looptimes,bool ShowLooptimes){
	int j=0;
	for (int i = 0; i < looptimes; i++)
	{
			if(ShowLooptimes)cout<<"\rLoop: "<<j+1<<" of "<<looptimes;
			GetCursorPos(&cursor);
			DrawIcon(hdc, cursor.x * 1.75, cursor.y * 1.75, LoadIcon(NULL, IDI_INFORMATION));
			Sleep(0.5);
			j++;
	}
}

int random()
{
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);
	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
	return out & 0x7fffffff;
}
void MouseError(int looptimes,bool ShowLooptimes){
	int j=0;
	for (int i = 0; i < looptimes; i++)
	{
		if(ShowLooptimes)cout<<"\rLoop: "<<j+1<<" of "<<looptimes;
		GetCursorPos(&cursor);
		SetCursorPos(cursor.x + (random() % 3 - 1) * (random() % (cursor_freq / 2200 + 2)), cursor.y + (random() % 3 - 1) * (random() % (cursor_freq / 2200 + 2)));
 		j++;
		Sleep(0.2);
	}
}
int ToTop(){
	HWND hWnd = ::GetForegroundWindow();
	::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 100, 100, SWP_NOMOVE | SWP_NOSIZE);
	return FALSE;
}
void ShakeWindow(int looptimes,int ShakeSize,bool ShowLooptimes){
	RECT rect; 
    HWND hwnd = NULL,oldhwnd = NULL; 
    int j=0,x,y,width,height; 
    for(int i=0;i<looptimes;i++)
    {
    	if(ShowLooptimes)cout<<"\rLoop: "<<j+1<<" of "<<looptimes;
        hwnd = GetForegroundWindow(); 
        if(hwnd!=oldhwnd)
        {
            GetWindowRect(hwnd,&rect); 
            x = rect.left;
            y = rect.top;
            width = rect.right - x;
            height = rect.bottom - y;
            oldhwnd = hwnd; 
        }
        MoveWindow(hwnd,x-ShakeSize,y,width,height,TRUE); 
        Sleep(5); //ÔÝÍ£5ºÁÃë
        MoveWindow(hwnd,x-ShakeSize,y-10,width,height,TRUE);
        Sleep(5);
        MoveWindow(hwnd,x,y-ShakeSize,width,height,TRUE);
        Sleep(5);
        MoveWindow(hwnd,x,y,width,height,TRUE);
        Sleep(5);j++;
    }
}
bool DisableConsoleWindowCloseButton()
{
   HWND consoleWnd = GetConsoleWindow();
    if (NULL == consoleWnd)
    {
        return false;
    }
    HMENU systemMenu = GetSystemMenu(consoleWnd, FALSE);
    if (NULL == systemMenu)
    {
        return false;
    }
    return EnableMenuItem(systemMenu, SC_CLOSE, MF_BYCOMMAND | MF_DISABLED) != FALSE;
}
bool DisableConsoleWindowSize()//Unusable
{
   HWND consoleWnd = GetConsoleWindow();
    if (NULL == consoleWnd)
    {
        return false;
    }
    HMENU systemMenu = GetSystemMenu(consoleWnd, FALSE);
    if (NULL == systemMenu)
    {
        return false;
    }
    return EnableMenuItem(systemMenu, SC_SIZE, MF_BYCOMMAND | MF_GRAYED) != FALSE;
}
bool DisableConsoleWindowMinisizeButton()//Unusable
{
   HWND consoleWnd = GetConsoleWindow();
    if (NULL == consoleWnd)
    {
        return false;
    }
    HMENU systemMenu = GetSystemMenu(consoleWnd, FALSE);
    if (NULL == systemMenu)
    {
        return false;
    }
    return EnableMenuItem(systemMenu, SC_MINIMIZE, MF_BYCOMMAND | MF_GRAYED) != FALSE;
}

/*int screenfuck(){ //Unusable[ERROR]
	for (int i = 0; i < 30; i++)
	{
		StretchBlt(hdc, 50, 50, cx * 1.75 - 100, cy * 1.75 - 100, hdc, 0, 0, cx * 1.75, cy * 1.75, SRCCOPY);
		Sleep(300);
	}
}*/
