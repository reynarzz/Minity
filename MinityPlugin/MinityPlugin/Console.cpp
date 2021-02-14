#include "pch.h"
#include <windows.h>

#include <stdio.h>

#include <fcntl.h>

#include <io.h>

#include <iostream>

#include <fstream>

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;

#ifdef _DEBUG

void RedirectIOToConsole()

{

    int hConHandle;

    long lStdHandle;

    CONSOLE_SCREEN_BUFFER_INFO coninfo;

    FILE* fp;

    // allocate a console for this app

    AllocConsole();

    // set the screen buffer to be big enough to let us scroll text

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),

        &coninfo);

    coninfo.dwSize.Y = MAX_CONSOLE_LINES;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),

        coninfo.dwSize);

    // redirect unbuffered STDOUT to the console

    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);

    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen(hConHandle, "w");

    *stdout = *fp;

    setvbuf(stdout, NULL, _IONBF, 0);

    // redirect unbuffered STDIN to the console

    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);

    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen(hConHandle, "r");

    *stdin = *fp;

    setvbuf(stdin, NULL, _IONBF, 0);

    // redirect unbuffered STDERR to the console

    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);

    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen(hConHandle, "w");

    *stderr = *fp;

    setvbuf(stderr, NULL, _IONBF, 0);

    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog

    // point to console as well

    std::ios::sync_with_stdio();

}

#endif

void OpenConsole()
{

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    int consoleHandleR, consoleHandleW;
    long stdioHandle;
    FILE* fptr;

    AllocConsole();
    SetConsoleTitle("Minity Console");

    EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);
    DrawMenuBar(GetConsoleWindow());

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);

    stdioHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    consoleHandleR = _open_osfhandle(stdioHandle, _O_TEXT);
    fptr = _fdopen(consoleHandleR, "r");
    *stdin = *fptr;
    setvbuf(stdin, NULL, _IONBF, 0);

    stdioHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    consoleHandleW = _open_osfhandle(stdioHandle, _O_TEXT);
    fptr = _fdopen(consoleHandleW, "w");
    *stdout = *fptr;
    setvbuf(stdout, NULL, _IONBF, 0);
    
    stdioHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    *stderr = *fptr;
    setvbuf(stderr, NULL, _IONBF, 0);
}

void OpenConsole2() 
{
    AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;

    std::wios::sync_with_stdio();
    std::ios::sync_with_stdio();
}