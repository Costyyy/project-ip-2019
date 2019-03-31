#include <graphics.h>
#include "menu.h"
#include "settings.h"
#include "header.h"
#include <iostream>
#include <cstring>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <string.h>
using namespace std;
//X,Y pozitia mouse; cX, cY pozitie click;
int xCenter = 1366/2, yCenter = 768/2, lat = 49, ln = 190, X, Y, cX,cY;
float fontSize = 4.5, letterSize = 4;
unsigned int show = 0;
bool isP1PC = false;
bool isP2PC = false;

unsigned int pastGames();

void checkClick();

struct buttons
{
    int x,y;
};
buttons play;
buttons Settings;
buttons exitB;
buttons tutorial;
// Salveaza coordonatele centrului fiecarui buton
//Malina
void initCenterM()
{
    xCenter = initX;
    yCenter = initY;
}
void initButtons()
{
    exitB.x = xCenter;
    exitB.y = yCenter+200;
    Settings.x = xCenter;
    Settings.y = yCenter;
    play.x = xCenter;
    play.y = yCenter-100;
    tutorial.x = xCenter;
    tutorial.y = yCenter+100;
}



void openWindow(int resolution)
{
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
}

//Deseneaza un buton la coordonatele x,y si cu textul din text[]
//Malina
void drawButton(int x,int y, char text[])
{
    setlinestyle(SOLID_LINE,0,3);
    rectangle(x-ln/2,y-lat/2,x+ln/2,y+lat/2);
    settextstyle(BOLD_FONT, HORIZ_DIR, letterSize);
    outtextxy(x-textwidth(text)/2,y-textheight(text)/2,text);
}
//Malina
void displayMenu()
{


    /*drawButton(play.x, play.y,"Play");
    drawButton(Settings.x, Settings.y,"Settings");
    drawButton(exitB.x, exitB.y,"Exit");
    drawButton(tutorial.x,tutorial.y,"Tutorial");
    */

    //hoverButton();
    checkClick();

}

void drawColoredSquare(int x, int y, int lat, int color, int edgeColor)
{
    int points[] = {x-lat/2,y-lat/2,x+lat/2,y-lat/2,x+lat/2,y+lat/2,x-lat/2,y+lat/2,x-lat/2,y-lat/2};
    setcolor(edgeColor);
    setfillstyle(SOLID_FILL,color);
    fillpoly(5, points);
}

void drawRectangle(int x, int y, int lat, int color, int edgeColor)
{
    int points[] = {x-lat/2,y-lat/2,x+lat/2,y-lat/2,x+lat/2,y+lat/2,x-lat/2,y+lat/2,x-lat/2,y-lat/2};
    setcolor(edgeColor);
    setfillstyle(SOLID_FILL,color);
    fillpoly(5, points);
}

int op1Update = 0, op2Update = 0;

void displayOptions(int set1, int set2, int set3, int set4, int set5, int set6)
{
    int x = 50;
    int y = 100;
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    setlinestyle(SOLID_LINE,0,3);
    char op1_0[30], op1_1[30], op1_2[30], op1_3[30], op1_4[30], op1_5[30];
    char tableType1[10], tableType2[10], tableType3[10], resolution1[20], resolution2[20], resolution3[20];
    int lang = 1;
    setcolor(WHITE);
    if(lang == 0)
    {
        strcpy(op1_0,"Marimea Tablei:");
        strcpy(op1_1,"Dimensiunea Ferestrei:");
        strcpy(op1_2,"Culoarea Jucatorului 1:");
        strcpy(op1_3,"Culoarea Jucatorului 2:");
        strcpy(op1_4,"Culoarea de fundal:");
        strcpy(op1_5,"Dimensiunea tablei:");
        strcpy(tableType1, "Patrat");
        strcpy(tableType2, "Romb");
        strcpy(tableType3, "Plus");
        strcpy(resolution1, "Ecran Complet");
        strcpy(resolution2, "1280x720");
        strcpy(resolution3, "1024x720");
    }
    else if (lang == 1)
    {
        strcpy(op1_0,"Table Size:");
        strcpy(op1_1,"Window Resolution:");
        strcpy(op1_2,"Player1 Color:");
        strcpy(op1_3,"Player2 Color:");
        strcpy(op1_4,"BackGround Color:");
        strcpy(op1_5,"Table Type:");
        strcpy(tableType1, "Square");
        strcpy(tableType2, "Rhombus");
        strcpy(tableType3, "Plus");
        strcpy(resolution1, "Fullscreen");
        strcpy(resolution2, "1280x720");
        strcpy(resolution3, "1024x720");
    }

    //Table size
    setcolor(COLOR(255, 255, 255));

    outtextxy(x,y-textheight(op1_0)/2,op1_0);




    // int xTab1 = 550+textwidth("4x4")/2, yTab1 = 100;
    // int xTab2 = 650+textwidth("4x4")/2, yTab2 = 100;
    // int xTab3 = 750+textwidth("4x4")/2, yTab3 = 100;
    // int xTab4 = 850+textwidth("4x4")/2, yTab4 = 100;
    int dif = (textwidth("10x10") - textwidth("4x4"))/2;
    int fillX = x+500;
    int fillY = y-textheight("10x10")/2;
    int coverPoints[] = {fillX, fillY, fillX + textwidth("10x10"), fillY, fillX + textwidth("10x10"), fillY + textheight("10x10"), fillX, fillY + textheight("10x10"), fillX, fillY};
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    if(op1Update != set1)
        if(set1 == 0)
        {
            fillpoly(5,coverPoints);
            setcolor(WHITE);
            outtextxy(x+500+dif,y-textheight("4x4")/2,"4x4");
            op1Update = set1;
        }
        else if(set1 == 1)
        {
            fillpoly(5,coverPoints);
            setcolor(WHITE);
            outtextxy(x+500+dif,y-textheight("6x6")/2,"6x6");
            op1Update = set1;
        }
        else if(set1 == 2)
        {
            fillpoly(5,coverPoints);
            setcolor(WHITE);
            outtextxy(x+500+dif,y-textheight("8x8")/2,"8x8");
            op1Update = set1;
        }
        else if(set1 == 3)
        {
            fillpoly(5,coverPoints);
            setcolor(WHITE);
            outtextxy(x+500,y-textheight("10x10")/2,"10x10");
            op1Update = set1;
        }
    setcolor(WHITE);

    rectangle(x+500-5,y-textheight("10x10")/2-5, x+500+textwidth("10x10")+5,y+textheight("10x10")/2+5);

    int points1[] = {x+500+textwidth("10x10")+10,y-textheight("10x10")/2-5, x+500+textwidth("10x10")+10,y+textheight("10x10")/2+5,x+500+textwidth("10x10")+10+textheight("10x10"),y,x+500+textwidth("10x10")+10,y-textheight("10x10")/2-5};

    int points2[] = {x+500-10, y - textheight("10x10")/2-5, x+500-10, y + textheight("10x10")/2+5, x+500-10 - textheight("10x10"),y, x+500-10, y - textheight("10x10")/2-5};

    drawpoly(4,points1);
    drawpoly(4,points2);

    //Table Type

    outtextxy(x, y+100-textheight(op1_5)/2,op1_5);

    fillX = x+500;
    fillY = y-textheight("10x10")/2+100;
    int coverPoints2[] = {fillX, fillY, fillX + textwidth("Rhombus"), fillY, fillX + textwidth("Rhombus"), fillY + textheight("10x10"), fillX, fillY + textheight("10x10"), fillX, fillY};
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);

    int dif0 = (textwidth("Rhombus") - textwidth("Square"))/2;
    int dif1 = (textwidth("Rhombus") - textwidth(tableType2))/2;
    int dif2 = (textwidth("Rhombus") - textwidth(tableType3))/2;

    if(op2Update != set6)
        if(set6 == 0)
        {
            fillpoly(5,coverPoints2);
            setcolor(WHITE);
            outtextxy(x+500+dif0, y+100-textheight("height")/2, tableType1);
            op2Update = set6;
        }
        else if(set6 == 1)
        {
            fillpoly(5,coverPoints2);
            setcolor(WHITE);
            outtextxy(x+500+dif1, y+100-textheight("height")/2, tableType2);
            op2Update = set6;
        }
        else if(set6 == 2)
        {
            fillpoly(5,coverPoints2);
            setcolor(WHITE);
            outtextxy(x+500+dif2, y+100-textheight("height")/2, tableType3);
            op2Update = set6;
        }
    setcolor(WHITE);
    rectangle(x+500-5,y-textheight("10x10")/2-5+100, x+500+textwidth("Rhombus")+5,y+textheight("10x10")/2+5+100);
    int points5[] = {x+500+textwidth("Rhombus")+10,y-textheight("10x10")/2-5+100, x+500+textwidth("Rhombus")+10,y+textheight("10x10")/2+5+100,x+500+textwidth("Rhombus")+10+textheight("10x10"),y+100,x+500+textwidth("Rhombus")+10,y-textheight("10x10")/2-5+100};

    int points6[] = {x+500-10, y - textheight("10x10")/2-5+100, x+500-10, y + textheight("10x10")/2+5+100, x+500-10 - textheight("10x10"), y+100, x+500-10, y - textheight("10x10")/2-5+100};

    drawpoly(4,points5);
    drawpoly(4,points6);
    //Resolution
    setcolor(COLOR(255, 255, 255));

    outtextxy(x,y+200-textheight(op1_1)/2, op1_1);
    dif0 = (textwidth(resolution1) - textwidth(resolution2))/2;
    dif1 = (textwidth(resolution1) - textwidth(resolution3))/2;
    if(set2 == 0)
    {
        outtextxy(x+500,y+200-textheight(resolution1)/2,resolution1);
    }
    else if(set2 == 1)
    {
        outtextxy(x+500+dif0,y+200-textheight(resolution1)/2,resolution2);
    }
    else if(set2 == 2)
    {
        outtextxy(x+500+dif1,y+200-textheight(resolution1)/2,resolution3);
    }
    rectangle(x+500-5,y-textheight(resolution1)/2-5+200, x+500+textwidth(resolution1)+5,y+textheight(resolution1)/2+5+200);

    int points3[] = {x+500+textwidth(resolution1)+10, y-textheight(resolution1)/2-5+200, x+500+textwidth(resolution1)+10,y+textheight(resolution1)/2+5+200,x+500+textwidth(resolution1)+10+textheight(resolution1),y+200,x+500+textwidth(resolution1)+10,y-textheight(resolution1)/2-5+200};

    int points4[] = {x+500-10, y - textheight(resolution1)/2-5+200, x+500-10, y + textheight(resolution1)/2+5+200, x+500-10 - textheight(resolution1),y+200, x+500-10, y - textheight(resolution1)/2-5+200};

    drawpoly(4,points3);
    drawpoly(4,points4);
    //Player1 color
    setcolor(COLOR(255, 255, 255));
    outtextxy(x,y+300-textheight(op1_2),op1_2);
    if(set3 == 0)
    {
        drawColoredSquare(x+500,y+300-textheight(op1_2),50, COLOR(242, 242, 14),COLOR(0, 255, 0));
    }
    else
    {
        drawColoredSquare(x+500,y+300-textheight(op1_2),50, COLOR(242, 242, 14),COLOR(255, 255, 255));
    }
    if(set3 == 1)
    {
        drawColoredSquare(x+600,y+300-textheight(op1_2),50, COLOR(33, 251, 255), COLOR(0, 255, 0));
    }
    else
    {
        drawColoredSquare(x+600,y+300-textheight(op1_2),50, COLOR(33, 251, 255), COLOR(255, 255, 255));
    }
    if(set3 == 2)
    {
        drawColoredSquare(x+700,y+300-textheight(op1_2),50, COLOR(244, 65, 71), COLOR(0, 255, 0));
    }
    else
    {
        drawColoredSquare(x+700,y+300-textheight(op1_2),50, COLOR(244, 65, 71), COLOR(255, 255, 255));
    }


    //Player2 color
    setcolor(COLOR(255, 255, 255));
    outtextxy(x,y+400-textheight(op1_3),op1_3);
    if(set4 == 0)
    {
        drawColoredSquare(x+500,y+400-textheight(op1_3),50, COLOR(110, 38, 255), COLOR(0, 255, 0));
    }
    else
    {
        drawColoredSquare(x+500,y+400-textheight(op1_3),50, COLOR(110, 38, 255), COLOR(255, 255, 255));
    }

    if(set4 == 1)
    {
        drawColoredSquare(x+600,y+400-textheight(op1_3),50, COLOR(255, 171, 38), COLOR(0, 255, 0));
    }
    else
    {
        drawColoredSquare(x+600,y+400-textheight(op1_3),50, COLOR(255, 171, 38), COLOR(255, 255, 255));
    }

    if(set4 == 2)
    {
        drawColoredSquare(x+700,y+400-textheight(op1_3),50, COLOR(66, 140, 244), COLOR(0, 255, 0));
    }
    else
    {
        drawColoredSquare(x+700,y+400-textheight(op1_3),50, COLOR(66, 140, 244), COLOR(255, 255, 255));
    }
    //.

    //Background color
    setcolor(COLOR(255, 255, 255));
    outtextxy(x,y+500-textheight(op1_4),op1_4);
    if(set5 == 0)
    {
        drawColoredSquare(x+500,y+500-textheight(op1_4),50, COLOR(39, 111, 122), COLOR(0, 255, 0));
    }
    else
    {
        drawColoredSquare(x+500,y+500-textheight(op1_4),50, COLOR(39, 111, 122), COLOR(255, 255, 255));
    }
    if(set5 == 1)
    {
        drawColoredSquare(x+600,y+500-textheight(op1_4),50, COLOR(36, 37, 89), COLOR(0, 255, 0));
    }
    else
    {
        drawColoredSquare(x+600,y+500-textheight(op1_4),50, COLOR(36, 37, 89), COLOR(255, 255, 255));
    }
    if(set5 == 2)
    {
        drawColoredSquare(x+700,y+500-textheight(op1_4),50, COLOR(48, 89, 36), COLOR(0, 255, 0));
    }
    else
    {
        drawColoredSquare(x+700,y+500-textheight(op1_4),50, COLOR(48, 89, 36), COLOR(255, 255, 255));
    }

    setcolor(COLOR(255, 255, 255));
    //drawButton(getmaxx()/5,getmaxy() - 50, "BACK");


}
void options()
{
    void* menuButton = new char[imagesize(0, 0, 105, 49)];
    void* menuButton_pressed = new char[imagesize(0, 0, 105, 45)];

    readimagefile("assets/menubutton.gif",0,0,105,49);
    getimage(0,0,105,49,menuButton);
    cleardevice();
    readimagefile("assets/menubutton_pressed.gif",0,0,105,45);
    getimage(0,0,105,45,menuButton_pressed);
    cleardevice();
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    putimage(getmaxx()/6 - 105/2, getmaxy()-50 - 49/2, menuButton, 0);
    ifstream settsr("settings.txt");
    int x,y;
    int xRes1 = 500+textwidth("4x4")/2, yRes = 300;
    int xRes2 = xRes1+textwidth("FullScreen")+15+textheight("FullScreen")/2+textwidth("10x10")/4;
    int xTab1 = 500+textwidth("4x4")/2, yTab = 100;
    int xTab2 = xTab1+textwidth("10x10")+15+textheight("10x10");
    int xTyp1 = 500+textwidth("4x4")/2, yTyp = 200;
    int xTyp2 = xTyp1+textwidth("Rhombus")+15+textheight("FullScreen")/2+textwidth("4x4")/4;
    //int xRes3 = 50+700+textwidth("1280x720")+textwidth("FullScreen") + textwidth("1024x720")/2, yRes3 =100+100;
    setcolor(WHITE);
    int key;
    int counter1 = 0;
    int counter2 = 0;
    int counter6 = 0;
    unsigned int counter3 = 0;
    unsigned int counter4 = 0;
    unsigned int counter5 = 0;
    settsr >> counter1;
    settsr >> counter2;
    settsr >> counter3;
    settsr >> counter4;
    settsr >> counter5;
    settsr >> counter6;
    ofstream settsw("settings.txt");
    unsigned int memory = counter2;
    bool refresh = false, pressed = false;
    op1Update = -1;
    op2Update = -1;
    while(key != 72)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(checkMouse(getmaxx()/6,getmaxy()-50,49,105,x,y))
            {
                buttonCover(getmaxx()/6, getmaxy()-50,105,49,BLACK);
                putimage(getmaxx()/6 - 105/2, getmaxy()-50 - 45/2+4, menuButton_pressed, 0);
                pressed = true;
            }

            clearmouseclick(WM_LBUTTONUP);

            while(pressed)
            {
                if(ismouseclick(WM_LBUTTONUP))
                {
                    clearmouseclick(WM_LBUTTONUP);
                    buttonCover(getmaxx()/6, getmaxy()-50,105,49,BLACK);
                    putimage(getmaxx()/6 - 105/2, getmaxy()-50 - 49/2, menuButton, 0);
                    key = 72;
                    pressed = false;
                }
            }

            //Check Table

            if(checkMouse(xTab1,yTab,textheight("10x10")+10,textheight("10x10")+10,x,y))
            {
                counter1--;
                if(counter1 < 0)
                {
                    counter1 = 3;
                }
            }
            else if(checkMouse(xTab2,yTab,textheight("10x10")+10,textheight("10x10")+10,x,y))
            {
                counter1++;
                if(counter1 > 3)
                {
                    counter1 = 0;
                }
            }

            //Table Type

            if(checkMouse(xTyp1, yTyp, textheight("10x10")+10,textheight("10x10")+10, x, y))
            {
                counter6--;
                if(counter6 < 0)
                {
                    counter6 = 1;
                }
            }
            else if(checkMouse(xTyp2, yTyp, textheight("10x10")+10,textheight("10x10")+10, x, y))
            {
                counter6++;
                if(counter6 > 2)
                {
                    counter6 = 0;
                }
            }

            //Check Resolution
            if(checkMouse(xRes1,yRes,textheight("10x10")+5,textwidth("10x10")+5,x,y))
            {
                counter2--;
                if(counter2 < 0)
                {
                    counter2 = 2;
                }
            }
            else if(checkMouse(xRes2,yRes,textheight("10x10")+5,textwidth("10x10")+5,x,y))
            {
                counter2++;
                if(counter2 > 2)
                {
                    counter2 = 0;
                }
            }
            /*if(checkMouse(xRes3,yRes3,textwidth("1024x720"),textheight("1024x720"),x,y))
            {
                counter2 = 2;
            }*/

            // Colors
            if(checkMouse(50+500,400-textheight("height"),50,50,x,y))
            {
                counter3 = 0;
            }
            else if(checkMouse(50+600,400-textheight("height"),50,50,x,y))
            {
                counter3 = 1;
            }
            else if(checkMouse(50+700,400-textheight("height"),50,50,x,y))
            {
                counter3 = 2;
            }


            if(checkMouse(50+500,500-textheight("height"),50,50,x,y))
            {
                counter4 = 0;
            }
            else if(checkMouse(50+600,500-textheight("height"),50,50,x,y))
            {
                counter4 = 1;
            }
            else if(checkMouse(50+700,500-textheight("height"),50,50,x,y))
            {
                counter4 = 2;
            }

            if(checkMouse(50+500,600-textheight("height"),50,50,x,y))
            {
                counter5 = 0;
            }
            else if(checkMouse(50+600,600-textheight("height"),50,50,x,y))
            {
                counter5 = 1;
            }
            else if(checkMouse(50+700,600-textheight("height"),50,50,x,y))
            {
                counter5 = 2;
            }

        }
        setTableSize(counter1);
        initRes(counter2);
        initColors(counter3,counter4,counter5);
        initTableType(counter6);
        initSquare();
        if(refresh == true)
        {
            cleardevice();
            op1Update = -1;
            op2Update = -1;
            refresh = false;
            putimage(getmaxx()/6 - 105/2, getmaxy()-50 - 49/2, menuButton, 0);
        }
        if(memory != counter2)
        {
            closegraph();
            op1Update = -1;
            op2Update = -1;
            openWindow(counter2);
            initRes(counter2);
            initCenterM();
            memory = counter2;
            refresh = true;
        }

        displayOptions(counter1,counter2,counter3,counter4,counter5, counter6);

    }
    settsw << counter1;
    settsw << "\n";
    settsw << counter2;
    settsw << "\n";
    settsw << counter3;
    settsw << "\n";
    settsw << counter4;
    settsw << "\n";
    settsw << counter5;
    settsw << "\n";
    settsw << counter6;
    settsw.close();
    key = 0;
    show = 0;
    delete menuButton;
    delete menuButton_pressed;
}

void buttonCover(int x, int y, int ln, int lat, int color)
{
    int points[] = {x - ln/2, y - lat/2, x + ln/2, y - lat/2, x + ln/2, y + lat/2, x - ln/2, y + lat/2, x - ln/2, y - lat/2};
    setfillstyle(SOLID_FILL, color);
    setcolor(color);
    fillpoly(5, points);
}

struct gameIndex
{
    unsigned int tSize;
    unsigned int tType;
    unsigned int time;
    unsigned int winner;
    int x,y;
};
gameIndex gameList[50];

void drawCheck(int cnt)
{
    int x = getmaxx() - getmaxx()/3 - 20;
    int y;
    for(int i = 0; i < cnt; i++)
    {
        y = gameList[i].y;
        if(replay == i+1)
        {
            setcolor(WHITE);
        }
        else
        {
            setcolor(BLACK);
        }

        line(x-8, y + 13, x + 8, y - 3);
        line(x-8, y - 3, x + 8, y + 13);
    }
}

//Malina
void checkClick()
{
    /*
    putimage(play.x - 190/2, play.y - 49/2, button, 0);
    putimage(Settings.x - 190/2, Settings.y - 49/2, button, 0);
    putimage(exitB.x - 190/2, exitB.y - 49/2, button, 0);
    putimage(tutorial.x - 190/2, tutorial.y - 49/2, button, 0);
    */
    void* playButton = new char[imagesize(0, 0, 190, 49)];
    void* playButton_pressed = new char[imagesize(0, 0, 190, 45)];
    void* settingsButton = new char[imagesize(0, 0, 190, 49)];
    void* settingsButton_pressed = new char[imagesize(0, 0, 190, 45)];
    void* exitButton = new char[imagesize(0, 0, 190, 49)];
    void* exitButton_pressed = new char[imagesize(0, 0, 190, 45)];
    void* tutorialButton = new char[imagesize(0, 0, 190, 49)];
    void* tutorialButton_pressed = new char[imagesize(0, 0, 190, 45)];

    readimagefile("assets/playbutton.gif",0,0,190,49);
    getimage(0,0,190,49,playButton);
    cleardevice();
    readimagefile("assets/playbutton_pressed.gif",0,0,190,45);
    getimage(0,0,190,45,playButton_pressed);
    cleardevice();
    readimagefile("assets/settingsbutton.gif",0,0,190,49);
    getimage(0,0,190,49,settingsButton);
    cleardevice();
    readimagefile("assets/settingsbutton_pressed.gif",0,0,190,45);
    getimage(0,0,190,45,settingsButton_pressed);
    cleardevice();
    readimagefile("assets/exitbutton.gif",0,0,190,49);
    getimage(0,0,190,49,exitButton);
    cleardevice();
    readimagefile("assets/exitbutton_pressed.gif",0,0,190,45);
    getimage(0,0,190,45,exitButton_pressed);
    cleardevice();
    readimagefile("assets/tutorialbutton.gif",0,0,190,49);
    getimage(0,0,190,49,tutorialButton);
    cleardevice();
    readimagefile("assets/tutorialbutton_pressed.gif",0,0,190,45);
    getimage(0,0,190,45,tutorialButton_pressed);
    cleardevice();

    initButtons();
    setcolor(WHITE);
    char title[] = "Dots and Lines";
    settextstyle(BOLD_FONT, HORIZ_DIR, 8);
    outtextxy(xCenter-textwidth(title)/2+25, yCenter-textheight(title)/2-200, title);

    putimage(play.x - 190/2, play.y - 49/2, playButton, 0);
    putimage(Settings.x - 190/2, Settings.y - 49/2, settingsButton, 0);
    putimage(exitB.x - 190/2, exitB.y - 49/2, exitButton, 0);
    putimage(tutorial.x - 190/2, tutorial.y - 49/2, tutorialButton, 0);
    unsigned int counter = pastGames();
    int x = getmaxx() - getmaxx()/3 - 20;
    int y = getmaxy()/3 - 100;
    for(int i = 0; i < counter; i++)
    {
        setlinestyle(SOLID_LINE, 0, 2);
        rectangle(x - 10, gameList[i].y - 10 + 5, x + 10, gameList[i].y+10 + 5);
    }
    drawButton(getmaxx() - getmaxx()/2 + 100, getmaxy()-55, "Replay");
    while(show == 0)
    {
        bool pressed = false;
        int but = -1;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,cX,cY);
            for(int i = 0; i < counter; i++)
            {
                if(checkMouse(x, gameList[i].y, 20, 20, cX, cY))
                {
                    replay = i+1;
                    initTableType(gameList[i].tType);
                    setTableSize(gameList[i].tSize);
                }
            }
            drawCheck(counter);
            //Play
            if(checkMouse(play.x,play.y,lat,ln,cX,cY))
            {
                buttonCover(play.x,play.y, ln, lat, BLACK);
                putimage(play.x - 190/2, play.y - 45/2+4, playButton_pressed, 0);
                //R: 47 G: 181 B: 239
                //setbkcolor(COLOR(47,181,239));
                //setcolor(WHITE);
                //outtextxy(play.x - 190/2, play.y - 45/2+4, "PLAY");
                //show = 2;
                pressed = true;
                but = 0;
            }
            //Settings
            if(checkMouse(Settings.x,Settings.y,lat,ln, cX, cY))
            {
                buttonCover(Settings.x, Settings.y, ln, lat, BLACK);
                putimage(Settings.x - 190/2, Settings.y - 45/2+4, settingsButton_pressed, 0);
                //show = 1;
                pressed = true;
                but = 1;
            }
            //Exit
            if(checkMouse(exitB.x,exitB.y,lat,ln, cX, cY))
            {
                buttonCover(exitB.x, exitB.y, ln, lat, BLACK);
                putimage(exitB.x - 190/2, exitB.y - 45/2+4, exitButton_pressed, 0);
                //show = 3;
                pressed = true;
                but = 2;

            }
            //Tutorial
            if(checkMouse(tutorial.x,tutorial.y,lat,ln, cX, cY))
            {
                buttonCover(tutorial.x, tutorial.y, ln, lat, BLACK);
                putimage(tutorial.x - 190/2, tutorial.y - 45/2+4, tutorialButton_pressed, 0);
                pressed = true;
                but = 3;
            }
            //Replay
            if(checkMouse(getmaxx() - getmaxx()/2 + 100, getmaxy()-55,lat,ln,cX,cY))
            {
                pressed = true;
                but = 4;
            }
            clearmouseclick(WM_LBUTTONUP);
            while(pressed)
            {
                if(ismouseclick(WM_LBUTTONUP))
                {
                    clearmouseclick(WM_LBUTTONUP);
                    buttonCover(play.x, play.y + 4, ln, lat, BLACK);
                    putimage(play.x - 190/2, play.y - 49/2, playButton, 0);
                    //outtextxy(play.x - 190/2, play.y - 49/2, "PLAY");
                    buttonCover(Settings.x, Settings.y + 4, ln, lat, BLACK);
                    putimage(Settings.x - 190/2, Settings.y - 49/2, settingsButton, 0);

                    buttonCover(exitB.x, exitB.y + 4, ln, lat, BLACK);
                    putimage(exitB.x - 190/2, exitB.y - 49/2, exitButton, 0);

                    buttonCover(tutorial.x, tutorial.y + 4, ln, lat, BLACK);
                    putimage(tutorial.x - 190/2, tutorial.y - 49/2, tutorialButton, 0);
                    pressed = false;
                    switch(but)
                    {
                    case 0:
                        show = 2;
                        break;
                    case 1:
                        show = 1;
                        break;
                    case 2:
                        show = 3;
                        break;
                    case 3:
                        show = 4;
                        break;
                    case 4:
                        replayTable();
                        return;
                        break;
                    }
                }
            }
        }
    }
    clearmouseclick(WM_LBUTTONUP);
    delete playButton;
    delete playButton_pressed;
    delete settingsButton;
    delete settingsButton_pressed;
    delete tutorialButton;
    delete tutorialButton_pressed;
    delete exitButton;
    delete exitButton_pressed;
}

//Malina
void hoverButton()
{
    while(show == 0)
    {
        //Daca mouse-ul a fost miscat
        if(ismouseclick(WM_MOUSEMOVE))
        {
            //atunci se salveaza coordonatele cursorului in X si Y
            getmouseclick(WM_MOUSEMOVE,X,Y);
            if(checkMouse(play.x,play.y,lat,ln,X,Y))
            {
                setcolor(GREEN);
                drawButton(xCenter, yCenter-100,"Play");
            }
            else
            {
                setcolor(WHITE);
                drawButton(xCenter, yCenter-100,"Play");
            }
            if(checkMouse(Settings.x,Settings.y,lat,ln, X, Y))
            {
                setcolor(GREEN);
                drawButton(Settings.x,Settings.y,"Settings");
            }
            else
            {
                setcolor(WHITE);
                drawButton(Settings.x,Settings.y,"Settings");
            }
            if(checkMouse(exitB.x,exitB.y,lat,ln, X, Y))
            {
                setcolor(GREEN);
                drawButton(exitB.x,exitB.y,"Exit");
            }
            else
            {
                setcolor(WHITE);
                drawButton(exitB.x,exitB.y,"Exit");
            }
            if(checkMouse(tutorial.x,tutorial.y,lat,ln, X, Y))
            {
                setcolor(GREEN);
                drawButton(tutorial.x,tutorial.y,"Tutorial");
            }
            else
            {
                setcolor(WHITE);
                drawButton(tutorial.x,tutorial.y,"Tutorial");
            }
        }
        checkClick();
    }

}


unsigned int pastGames()
{

    int x,y;
    ifstream data;
    data.open("games.txt", ios::in);
    char div;
    unsigned int counter = 0;
    int temp, time = 0;
    while(data >> div)
    {
        if(div == 'D')
        {
            while(data >> temp)
            {
                time = time * 10 + temp;
                div = data.peek();
                if(div == 'S')
                {
                    break;
                }
            }
            gameList[counter].time = time;
            data >> div;
            data >> gameList[counter].tSize;
            data >> div;
            data >> gameList[counter].tType;
            data >> div;
            data >> gameList[counter].winner;
            counter++;
        }
    }
    x = getmaxx() - getmaxx()/3;
    y = getmaxy()/3;
    setcolor(WHITE);
    setlinestyle(SOLID_LINE,0,2);
    rectangle(x,y,x+400,y+450);
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    char inx[10];
    char op1[20], op2[20], op3[10];
    for(int i = 0; i < counter; i++)
    {
        itoa(i+1,inx,10);
        switch(gameList[i].tType)
        {
        case 0:
            strcpy(op1, "T:Square");
            break;
        case 1:
            strcpy(op1, "T:Rhombus");
            break;
        case 2:
            strcpy(op1, "T:Plus");
            break;
        }
        switch(gameList[i].tSize)
        {
        case 0:
            strcpy(op2, "S:4x4");
            break;
        case 1:
            strcpy(op2, "S:6x6");
            break;
        case 2:
            strcpy(op2, "S:8x8");
            break;
        case 3:
            strcpy(op2, "S:10x10");
            break;
        }
        switch(gameList[i].winner)
        {
        case 0:
            strcpy(op3, "W:P1");
            break;
        case 1:
            strcpy(op3, "W:P2");
            break;
        case 2:
            strcpy(op3, "W:D");
            break;
        }
        cout<<gameList[i].tSize<<" "<<gameList[i].tType;
        outtextxy(x+10, y + 20 + i*30 - textheight(inx)/2, inx);
        outtextxy(x+50, y + 20 + i*30 - textheight("O")/2, op1);
        outtextxy(x+ 180, y + 20 + i*30 - textheight("O")/2, op2);
        outtextxy(x+ 300, y + 20 + i*30 - textheight("O")/2, op3);
        gameList[i].x = x + 200;
        gameList[i].y = y + 20 + i*30 - textheight("O")/2;
    }
    return counter;
}

void menu()
{

    cleardevice();
    int x = getmaxx();
    int y = getmaxy();
    int points[] = {0,0,x,0,x,y,0,y,0,0};
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    setbkcolor(BLACK);
    fillpoly(5,points);

    show = 0;
    checkClick();
}
//---------------------------------------------------------->
buttons P1vsP2;
buttons P1vsPC;
buttons PCvsPC;

void initSettingsButtons()
{
    P1vsPC.x = xCenter;
    P1vsPC.y = yCenter;
    P1vsP2.x = xCenter;
    P1vsP2.y = yCenter-100;
    PCvsPC.x = xCenter;
    PCvsPC.y = yCenter+100;
}
//Malina
void displaySettings()
{
    initSettingsButtons();
    char title[] = "Select game mode";
    settextstyle(BOLD_FONT, HORIZ_DIR, 8);
    outtextxy(xCenter-textwidth(title)/2, yCenter-textheight(title)/2-200, title);
    drawButton(P1vsP2.x, P1vsP2.y,"P1vsP2");
    drawButton(P1vsPC.x, P1vsPC.y,"P1vsPC");
    drawButton(PCvsPC.x,PCvsPC.y,"PCvsPC");
    hoverSettingsButton();
}
//Malina
void checkSettingsClick()
{
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN,cX,cY);

        if(checkMouse(P1vsP2.x,P1vsP2.y,lat,ln,cX,cY))
        {
            isP1PC = false;
            isP2PC = false;
            show = 0;
        }

        if(checkMouse(P1vsPC.x,P1vsPC.y,lat,ln, cX, cY))
        {
            isP1PC = false;
            isP2PC = true;
            show = 0;
        }

        if(checkMouse(PCvsPC.x,PCvsPC.y,lat,ln, cX, cY))
        {
            isP1PC = true;
            isP2PC = true;
            show = 0;
        }

    }
}
//Malina
void hoverSettingsButton()
{
    while(show == 2)
    {
        //Daca mouse-ul a fost miscat
        if(ismouseclick(WM_MOUSEMOVE))
        {
            //atunci se salveaza coordonatele cursorului in X si Y
            getmouseclick(WM_MOUSEMOVE,X,Y);
            if(checkMouse(P1vsP2.x,P1vsP2.y,lat,ln,X,Y))
            {
                setcolor(GREEN);
                drawButton(P1vsP2.x, P1vsP2.y,"P1vsP2");
            }
            else
            {
                setcolor(WHITE);
                drawButton(P1vsP2.x, P1vsP2.y,"P1vsP2");
            }
            if(checkMouse(P1vsPC.x,P1vsPC.y,lat,ln, X, Y))
            {
                setcolor(GREEN);
                drawButton(P1vsPC.x,P1vsPC.y,"P1vsPC");
            }
            else
            {
                setcolor(WHITE);
                drawButton(P1vsPC.x,P1vsPC.y,"P1vsPC");
            }
            if(checkMouse(PCvsPC.x,PCvsPC.y,lat,ln, X, Y))
            {
                setcolor(GREEN);
                drawButton(PCvsPC.x,PCvsPC.y,"PCvsPC");
            }
            else
            {
                setcolor(WHITE);
                drawButton(PCvsPC.x,PCvsPC.y,"PCvsPC");
            }
        }
        checkSettingsClick();
    }

}

void settings()
{
    cleardevice();
    show = 2;
    displaySettings();
}

void displayTutorial(int tutnum)
{
    cleardevice();
    char tut1text1[100],tut1text2[100],tut2text1[100],tut2text2[100],tut3text1[100],tut3text2[100];
    void* tut1 = new char[imagesize(0, 0, 427, 300)];
    readimagefile("assets/tut1.gif",0,0,427,300);
    getimage(0,0,427,300,tut1);
    cleardevice();
    strcpy(tut1text1,"2 players take turns to draw") ;
    strcpy(tut1text2, "lines between two dots");
    void* tut2 = new char[imagesize(0, 0, 427, 300)];
    readimagefile("assets/tut2.gif",0,0,427,300);
    getimage(0,0,427,300,tut2);
    cleardevice();
    strcpy(tut2text1, "the player that draws a line to");
    strcpy(tut2text2, "create a square gets a point");
    void* tut3 = new char[imagesize(0, 0, 427, 300)];
    readimagefile("assets/tut3.gif",0,0,427,300);
    getimage(0,0,427,300,tut3);
    cleardevice();
    strcpy(tut3text1, "the game is finished when all the lines are");
    strcpy(tut3text2, "drawn and the player with the most points wins");
    void* menuButton = new char[imagesize(0, 0, 105, 49)];
    void* menuButton_pressed = new char[imagesize(0, 0, 105, 45)];

    readimagefile("assets/menubutton.gif",0,0,105,49);
    getimage(0,0,105,49,menuButton);
    cleardevice();
    readimagefile("assets/menubutton_pressed.gif",0,0,105,45);
    getimage(0,0,105,45,menuButton_pressed);
    cleardevice();
    putimage(getmaxx()/6 - 105/2, getmaxy()-50 - 49/2, menuButton, 0);
    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    setcolor(COLOR(255, 255, 255));

    if (tutnum == 1)
    {
        putimage(xCenter - 200, yCenter - 300, tut1, 0);
        outtextxy(xCenter-textwidth(tut1text1)/2+25, yCenter-textheight(tut1text1)/2+150, tut1text1);
        outtextxy(xCenter-textwidth(tut1text2)/2+25, yCenter-textheight(tut1text2)/2+200, tut1text2);
        drawButton(xCenter+10, yCenter+260,">");
    }
    else if (tutnum == 2)
    {
        putimage(xCenter - 200, yCenter - 300, tut2, 0);
        outtextxy(xCenter-textwidth(tut2text1)/2+25, yCenter-textheight(tut2text1)/2+150, tut2text1);
        outtextxy(xCenter-textwidth(tut2text2)/2+25, yCenter-textheight(tut2text2)/2+200, tut2text2);
        drawButton(xCenter+10, yCenter+260,">");
    }
    else if (tutnum >= 3)
    {
        putimage(xCenter - 200, yCenter - 300, tut3, 0);
        settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        outtextxy(xCenter-textwidth(tut3text1)/2+25, yCenter-textheight(tut3text1)/2+150, tut3text1);
        outtextxy(xCenter-textwidth(tut3text2)/2+25, yCenter-textheight(tut3text2)/2+200, tut3text2);
    }
    bool done = true;
    while (done) {
        while(!ismouseclick(WM_LBUTTONDOWN));
        clearmouseclick(WM_LBUTTONDOWN);
        getmouseclick(WM_MOUSEMOVE,X,Y);
        if(checkMouse(xCenter+10,yCenter+260,lat,ln,X,Y))
         {  clearmouseclick(WM_LBUTTONUP);
            while(!ismouseclick(WM_LBUTTONUP));
            done = false;
            displayTutorial(tutnum + 1);
        } else if(checkMouse(getmaxx()/6,getmaxy()-50,49,105,X,Y))
            {
                buttonCover(getmaxx()/6, getmaxy()-50,105,49,BLACK);
                putimage(getmaxx()/6 - 105/2, getmaxy()-50 - 45/2+4, menuButton_pressed, 0);
                show = 0;
                return;
            }
    }
}

void tut()
{
    cleardevice();
    show = 4;
    displayTutorial(1);
}
