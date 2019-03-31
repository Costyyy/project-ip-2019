#include <iostream>
#include "header.h"
#include <graphics.h>
#include <conio.h>
#include "menu.h"
#include "settings.h"
#include <fstream>
using namespace std;

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

bool startMenu()
{
    bool ckexit = true;
    while(show == 0)
    {
        PlaySound("Game-Menu_Looping.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
        menu();
        if (show == 1)
        {
            options();
        }
        else if (show == 2)
        {
            settings();
            initSquare();
            ckexit = check();

        }
        else if (show == 3)
        {
            return false;
        }
        else if (show == 4)
        {
            tut();
        }
    }
    if(ckexit == false)
        return false;
    else
        return true;
}

int main()
{

    //HideConsole();
    ifstream res("settings.txt");
    //initwindow(1200,720);
    unsigned int resolution, tableSize, P1C, P2C, BKC, tableType;
    res >> tableSize;
    res >> resolution;
    res >> P1C;
    res >> P2C;
    res >> BKC;
    res >> tableType;
    //closegraph();
    switch(resolution)
    {
    case 0:
        int screenwidth,screenheight;
        screenwidth=GetSystemMetrics(SM_CXSCREEN);
        screenheight=GetSystemMetrics(SM_CYSCREEN);
        initwindow(screenwidth,screenheight,"",-3,-3);
        break;
    case 1:
        initwindow(1280,720," ");
        break;
    case 2:
        initwindow(1024,720," ");
        break;
    case 3:
        initwindow(800,480," ");
        break;
    }
    initColors(P1C,P2C,BKC);
    setTableSize(tableSize);
    initRes(resolution);
    initCenterM();
    initTableType(tableType);
    //initAssets();

    bool exit = true;
    //PlaySound("Game-Menu_Looping.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
    while(exit)
    {
        exit = startMenu();
    }
}
