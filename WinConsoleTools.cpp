#include"WinConsoleTools.h"
#include<windows.h> 
void MoveCursor(const int cor_x, const int cor_y) // Move the cursor to a specific coordinate
{
    HANDLE cursor;
    cursor = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordinate = { cor_x, cor_y };
    SetConsoleCursorPosition(cursor, coordinate); 
}

void HideCursor() // Hide the cursor.
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false; 
	SetConsoleCursorInfo(handle, &CursorInfo);
}

void ShowCursor() // Show the cursor.
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = true; 
    SetConsoleCursorInfo(handle, &CursorInfo);
}

void Pause(unsigned long milliseconds) // Pause the system for some milliseconds
{
	Sleep(milliseconds);
}


void MoveWindow(int posx, int posy) // Move the Window to a specific position on the screen
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void MoveCenter() // Move the Window to the center of the screen 
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    int posx, posy;
    posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2,
        posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2,

        MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}