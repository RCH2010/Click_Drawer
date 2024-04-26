#include <bits/stdc++.h>
#include <windows.h>
#include <winuser.h>
#include"MyLibrary.h"
using namespace std;

POINT point2;   
POINT point;
CONSOLE_SCREEN_BUFFER_INFO csbi;
HWND pHwnd = ::GetForegroundWindow();
		
int showLicense(){
	SetColorAndBackground(11,0);
	cout<<"---------------Click Drawer---------------"<<endl;
	cout<<"-By: rch2010 (github: github.com/rch2010) "<<endl;
	cout<<"                                          "<<endl;
	cout<<"-Usage: Left/Right Key: Switch Colors     "<<endl;
	cout<<"-Double-Click F11 Key: Exit Full Screen   "<<endl;
	cout<<"--------------Have a nice day-------------"<<endl;
	system("pause&&cls");
}

int main() {
	int nowx,nowy;
	int color=4;
	full_screen();    
	showLicense();
    while(1) {
    Go:
		if(KEY_DOWN(VK_LEFT)){
			Sleep(60);
			if(color<=0)goto next;
			color--;
			gotoxy(0,0);
			SetColorAndBackground(15,0);
			cout<<"Color: ";
			SetColorAndBackground(15,color);
			cout<<"["<<color<<"]";
		}next:
		if(KEY_DOWN(VK_RIGHT)){
			Sleep(60);
			if(color>=15)goto nextt;
			color++;
			gotoxy(0,0);
			SetColorAndBackground(15,0);
			cout<<"Color: ";
			SetColorAndBackground(15,color);
			cout<<"["<<color<<"]";
		}nextt:
	    GetCursorPos(&point);
	    nowx=point.x;nowy=point.y;
	    gotoxy(nowx/10,nowy/5);
	    SetColorAndBackground(15,0);
	    cout<<"";
    	if(KEY_DOWN(VK_LBUTTON)){
			SetColorAndBackground(15,color);
			cout<<" ";
		}
    }
    return 0;
}

