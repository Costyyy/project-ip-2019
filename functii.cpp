#include "header.h"
#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <random>
#include "menu.h"
#include <windows.h>
#include <string>
#include <fstream>
#include <time.h>
using namespace std;
//Marimea tablei de joc
int matSize = 5;
//Coordonatele pentru centrul tablei, distanta dintre cercuri, raza cercurilor
int initX = 600, initY = 300, dist = 100, radius = 7;
bool rhTable = true, plusTable = true;
//latimea zonei de click, pozitia click-ului, counter pentru numarul de casute completate dupa desenarea unei linii
int L = radius, mX, mY,countCells = 0;
//Jucatorul curent
bool player = 0;
//Colors
int P1color = COLOR(244, 65, 71); // Bright Red
int P2color = COLOR(66, 140, 244); // Bright Blue
int P1scoreColorON = COLOR(242, 53, 81); //Bright Red
int P1scoreColorOFF = COLOR(140, 0, 20); // Dark Red
int P2scoreColorON = COLOR(9, 218, 229); // Bright Blue
int P2scoreColorOFF = COLOR(2, 94, 147); // Dark Blue
int BKcolor = COLOR(29, 70, 76); //
int DotColor = COLOR(37, 198, 77);

struct points
{
    int scoreP1 = 0;
    int scoreP2 = 0;
};

void endcond(bool &done);

void initTableType(int type)
{
    switch(type)
    {
    case 0:
        rhTable = false;
        plusTable = false;
        break;
    case 1:
        rhTable = true;
        plusTable = false;
        break;
    case 2:
        plusTable = true;
        rhTable = false;
        break;
    }
}

void initColors(int P1C, int P2C, int BKC)
{

    switch(P1C)
    {
    case 0:
        P1color = COLOR(242, 242, 14);
        P1scoreColorON = COLOR(255, 255, 58);
        P1scoreColorOFF = COLOR(180, 183, 25);
        break;
    case 1:
        P1color = COLOR(33, 251, 255);
        P1scoreColorON = COLOR(64, 246, 249);
        P1scoreColorOFF = COLOR(41, 176, 178);
        break;
    case 2:
        P1color = COLOR(244, 65, 71);
        P1scoreColorON = COLOR(242, 53, 81);
        P1scoreColorOFF = COLOR(140, 0, 20);
        break;
    }
    switch(P2C)
    {
    case 0:
        P2color = COLOR(110, 38, 255);
        P2scoreColorON = COLOR(128, 66, 255);
        P2scoreColorOFF = COLOR(86, 41, 178);
        break;
    case 1:
        P2color = COLOR(255, 171, 38);
        P2scoreColorON = COLOR(255, 176, 50);
        P2scoreColorOFF = COLOR(183, 124, 31);
        break;
    case 2:
        P2color = COLOR(66, 140, 244);
        P2scoreColorON = COLOR(9, 218, 229);
        P2scoreColorOFF = COLOR(2, 94, 147);
        break;
    }
    switch(BKC)
    {
    case 0:
        BKcolor = COLOR(39, 111, 122);
        break;
    case 1:
        BKcolor = COLOR(36, 37, 89);
        break;
    case 2:
        BKcolor = COLOR(48, 89, 36);
        break;
    }

}

void initRes(int res)
{
    switch(res)
    {
    case 0:
        initX = 1366/2;
        initY = 768/2;
        break;
    case 1:
        initX = 1280/2;
        initY = 720/2;
        break;
    case 2:
        initX = 1024/2;
        initY = 720/2;
        break;
    case 3:
        initX = 800/2;
        initY = 480/2;
        break;
    }

}

void resetList(lista &L)
{
    nod *n, *q;
    if(L.first != NULL)
    {
        for(n = L.first; n->next != NULL; n = q)
        {
            q = n->next;
            L.first = q;
            n = NULL;
            delete n;
        }
    }
}

void initLista(lista &L)
{

    {
        L.first = NULL;
    }
}



void setTableSize(unsigned int lat)
{
    switch(lat)
    {
    case 0:
        matSize = 4;
        dist = 120;
        break;
    case 1:
        matSize = 6;
        dist = 100;
        break;
    case 2:
        matSize = 8;
        dist = 70;
        break;
    case 3:
        matSize = 10;
        dist = 60;
        break;
    case 4:
        matSize = 10;
        dist = 60;
        break;
    }
}

void addMove(int i, int j, int dir, lista &L)
{
    if(L.first == NULL)
    {
        L.first = new nod;
        L.first->i = i;
        L.first->j = j;
        L.first->direction = dir;
        L.first->next = NULL;
        L.last = L.first;
        L.first->prev = NULL;
    }
    else
    {
        nod *n = new nod;
        n->next = L.first;
        n->i = i;
        n->j = j;
        n->direction = dir;
        L.first = n;
        n->next->prev = n;
        L.first->prev = NULL;
    }
}

points players;
//Malina
void score()
{
    if(player == 0)
        players.scoreP1+=countCells;
    else
        players.scoreP2+=countCells;
    updateScore();
    countCells = 0;
}

square table[15][15];
// salveaza coordonate centrului fiecarui patrat
//Constantin
void initSquare()
{
    for(int x = initX-(matSize-1)*dist/2, i = 0; i < matSize - 1; x += dist, i++)
        for(int y = initY-(matSize-1)*dist/2, j = 0; j < matSize - 1; y+=dist, j++)
        {
            table[i][j].x = x + dist/2;
            table[i][j].y = y + dist/2;
            if(plusTable == true)
            {

                if(((i < (matSize-1)/2-1)&&(j < (matSize-1)/2-1))||((i > (matSize-1)/2 + 1)&&(j < (matSize-1)/2-1))||((j > (matSize-1)/2 + 1)&&(i < (matSize-1)/2 - 1))||((j > (matSize-1)/2 + 1)&&(i > (matSize-1)/2 + 1)))
                {
                    table[i][j].active = false;
                }
                else
                {
                    table[i][j].active = true;
                }
            }
            if(rhTable == true)
            {
                if((j > (matSize-1)/2 - i - 1)&&(j < (matSize-1)/2 + i + 1)&&(i < (matSize-1)/2 + j + 1)&&(i < (matSize-1)/2 + (matSize-1) - j))
                    table[i][j].active = true;
                else
                    table[i][j].active = false;
            }
            if(plusTable == false && rhTable == false)
            {
                table[i][j].active = true;
            }

        }
}

void resetSquares()
{
    for(int i = 0; i < matSize - 1; i++)
        for(int j = 0; j < matSize - 1; j++)
        {
            table[i][j].complete = false;
            table[i][j].up = false;
            table[i][j].down = false;
            table[i][j].right = false;
            table[i][j].left = false;
            table[i][j].cnt = 0;
            //table[i][j].active = false;

        }
    players.scoreP1 = 0;
    players.scoreP2 = 0;
    player = 0;
}
//Deseneaza o linie orizontala de grosime 3
//Constantin
void drawHline(int x1, int y1,int x2, int y2, unsigned int style)
{
    setlinestyle(style,0,1);
    line(x1,y1-1,x2,y2-1);
    line(x1,y1,x2,y2);
    line(x1,y1+1,x2,y2+1);
}
//Deseneaza o linie verticala de grosime 3
//Constantin
void drawVline(int x1, int y1,int x2, int y2, unsigned int style)
{
    setlinestyle(style,0,1);
    line(x1-1,y1,x2-1,y2);
    line(x1,y1,x2,y2);
    line(x1+1,y1,x2+1,y2);
}
//Deseneaza liniile si literele din interiorul patratelor
//Constantin
void afisare(int i, int j)
{
    int x,y;
    x = table[i][j].x;
    y = table[i][j].y;
    if(table[i][j].complete == 0)
        //cover(x,y);
        setlinestyle(0,0,1);
    if((i<matSize-1)&&(j<matSize-1))
    {
        if(table[i][j].up == true)
        {
            if(table[i][j].whoUP == 0)
                setcolor(P1color);
            else
                setcolor(P2color);
            drawHline(x-dist/2+radius,y-dist/2,x+dist/2-radius,y-dist/2,0);
        }
        if(table[i][j].down == true)
        {
            if(table[i][j].whoDOWN == 0)
                setcolor(P1color);
            else
                setcolor(P2color);
            drawHline(x-dist/2+radius,y+dist/2,x+dist/2-radius,y+dist/2,0);
        }
        if(table[i][j].right == true)
        {
            if(table[i][j].whoRIGHT == 0)
                setcolor(P1color);
            else
                setcolor(P2color);
            drawVline(x+dist/2,y-dist/2+radius,x+dist/2,y+dist/2-radius,0);
        }
        if(table[i][j].left == true)
        {
            if(table[i][j].whoLEFT == 0)
                setcolor(P1color);
            else
                setcolor(P2color);
            drawVline(x-dist/2,y-dist/2+radius,x-dist/2,y+dist/2-radius,0);
        }
        if(table[i][j].complete == true)
        {
            setbkcolor(BLACK);
            char display[2];
            display[0] = table[i][j].who;
            display[1] = '\0';
            settextstyle(BOLD_FONT, HORIZ_DIR, dist/20);
            if(table[i][j].who == 'A')
                setcolor(P1color);
            else
                setcolor(P2color);
            outtextxy(x-textwidth(display)/2, y-textheight(display)/2, display);
        }
    }

    drawPoints(i,j);
}


//Deseneaza punctele
//Constantin
void drawPoints(int i, int j)
{
    int x,y;

    x = table[i][j].x;
    y = table[i][j].y;

    setcolor(DotColor);
    setlinestyle(SOLID_LINE, 0, 1);

    circle(x-dist/2,y-dist/2,radius);
    setfillstyle(SOLID_FILL, DotColor);
    floodfill(x-dist/2,y-dist/2, DotColor);

    circle(x+dist/2,y-dist/2,radius);
    setfillstyle( SOLID_FILL, DotColor);
    floodfill(x+dist/2,y-dist/2, DotColor);

    circle(x-dist/2,y+dist/2,radius);
    setfillstyle( SOLID_FILL, DotColor);
    floodfill(x-dist/2,y+dist/2, DotColor);

    circle(x+dist/2,y+dist/2,radius);
    setfillstyle( SOLID_FILL, DotColor);
    floodfill(x+dist/2,y+dist/2, DotColor);

}
//Deseneaza background-ul
//Constantin
void displayBackground()
{
    // Deseneaza background-ul
    setcolor(BKcolor);
    setfillstyle(SOLID_FILL,BKcolor);
    setlinestyle(SOLID_LINE,0,3);
    int x = getmaxx();
    int y = getmaxy();
    int points[] = {0,0,x,0,x,y,0,y,0,0};
    fillpoly(5,points);
    setcolor(WHITE);
    for(int i = 0; i < matSize - 1; i++)
        for(int j = 0; j < matSize - 1; j++)
        {
            if(rhTable == true || plusTable == true)
            {
                if(table[i][j].active == true)
                {
                    x = table[i][j].x;
                    y = table[i][j].y;
                    int points[] = {x-dist/2 - 18, y-dist/2 - 18, x+dist/2 + 18, y-dist/2 - 18, x+dist/2 + 18, y+dist/2 + 18, x-dist/2 - 18, y+dist/2 + 18, x-dist/2 - 18, y-dist/2 - 18};
                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL, WHITE);
                    fillpoly(5,points);
                }
            }
        }

    for(int i = 0; i < matSize - 1; i++)
        for(int j = 0; j < matSize - 1; j++)
        {
            if(rhTable == true || plusTable == true)
            {
                if(table[i][j].active == true)
                {
                    x = table[i][j].x;
                    y = table[i][j].y;

                    int points1[] = {x-dist/2 - 15, y-dist/2 - 15, x+dist/2 + 15, y-dist/2 - 15, x+dist/2 + 15, y+dist/2 + 15, x-dist/2 - 15, y+dist/2 + 15, x-dist/2 - 15, y-dist/2 - 15};
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    fillpoly(5,points1);
                }
            }
            else
            {

                setcolor(WHITE);
                rectangle(initX-(matSize-1)*dist/2-dist/2, initY-(matSize-1)*dist/2-dist/2, initX+(matSize-1)*dist/2+dist/2, initY+(matSize-1)*dist/2+dist/2);
                setfillstyle(SOLID_FILL, BLACK);
                floodfill(initX,initY, WHITE);

            }

        }


}

// Deseneaza scorul si il coloreaza in functie de al cui e randul
//Malina
void updateScore()
{
    int x1,y1,x2,y2,text;
    x1 = initX-(matSize-1)*dist/2-dist/2-150;
    y1 = getmaxy()/5;
    x2 = initX+(matSize-1)*dist/2+dist/2+150;
    y2 = getmaxy()/5;

    //Convert int to char
    char score1[10], score2[10];


    int score, counter = 0;
    score1[0] = '0';
    score2[0] = '0';
    score = players.scoreP1;
    while(score != 0)
    {
        counter++;
        score /= 10;
    }
    if(counter != 0)
        score1[counter] = '\0';
    else if (counter == 0)
        score1[1] = '\0';
    score = players.scoreP1;
    do
    {
        counter--;
        score1[counter] = score%10 + '0';
        score /= 10;
    }
    while(score != 0);

    score = players.scoreP2;
    counter = 0;
    while(score != 0)
    {
        counter++;
        score /= 10;
    }
    score = players.scoreP2;
    if(counter != 0)
        score2[counter] = '\0';
    else if (counter == 0)
        score2[1] = '\0';
    do
    {
        counter--;
        score2[counter] = score%10 + '0';
        score /= 10;
    }
    while(score != 0);

    settextstyle(BOLD_FONT,HORIZ_DIR,10);

    setbkcolor(BKcolor);
    if(player == 0)
        setcolor(P1scoreColorON);
    else
        setcolor(P1scoreColorOFF);

    text = textwidth(score1);
    outtextxy(x1-text/2, y1, score1);

    setbkcolor(BKcolor);
    if(player == 1)
        setcolor(P2scoreColorON);
    else
        setcolor(P2scoreColorOFF);

    text = textwidth(score2);
    outtextxy(x2-text/2, y2, score2);

}

// Verifica daca patratul [i][j] este complet
//Constantin
bool complete(int i, int j)
{
    bool cmp = false;
    if((table[i][j].up == true)&&(table[i][j].down == true)&&(table[i][j].right == true)&&(table[i][j].left == true)&&(table[i][j].complete != true))
    {
        table[i][j].complete = true;
        countCells++;
        cout<<i<<" "<<j<<" complete\n";
        if(player == 0)
            table[i][j].who = 'A';
        else
            table[i][j].who = 'B';

        cmp = true;
    }
    return cmp;
}
//Trece la urmatorul jucator
//Constantin
void turn()
{
    if (player == 0)
    {
        player = 1;
    }
    else if(player == 1)
    {
        player = 0;
    }
    updateScore();
}
//Acopera zona dintre puncte cu un poligon(not used)
//Constantin
void cover(int x, int y)
{
    int points1[] = {x-dist/2+radius,y-dist/2-2,x+dist/2-radius,y-dist/2-2,x+dist/2-radius,y+dist/2+2,x-dist/2+radius,y+dist/2+2,x-dist/2+radius,y-dist/2-2};
    int points2[] = {x-dist/2-2,y-dist/2+radius,x+dist/2+2,y-dist/2+radius,x+dist/2+2,y+dist/2-radius,x-dist/2-2,y+dist/2-radius,x-dist/2-2,y-dist/2+radius};
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillpoly(5, points1);
    fillpoly(5, points2);
}
//Deseneaza liniile punctate intre puncte
//Constantin
void hover()
{
    int x,y, mXhover, mYhover;
    if(ismouseclick(WM_MOUSEMOVE))
    {
        getmouseclick(WM_MOUSEMOVE,mXhover,mYhover);
        for(int i=0; i < matSize-1; i++)
            for(int j=0; j < matSize-1; j++)
            {
                x = table[i][j].x;
                y = table[i][j].y;
                //Sus-Jos
                if((mXhover<x-dist/2+L)&&(mXhover>x-dist/2-L)&&(mYhover>y-dist/2+L)&&(mYhover<y+dist/2-L)&&(table[i][j].left != true)&&(table[i][j].active == true))
                {
                    setcolor(COLOR(70, 244, 65));
                    drawVline(x-dist/2,y-dist/2+radius+1,x-dist/2,y+dist/2-radius-1,1);
                    drawPoints(i,j);
                }
                else if((mXhover>x+dist/2-L)&&(mXhover<x+dist/2+L)&&(mYhover<y+dist/2-L)&&(mYhover>y-dist/2+L)&&(table[i][j].right != true)&&(table[i][j].active == true))
                {
                    setcolor(COLOR(70, 244, 65));
                    drawVline(x+dist/2,y-dist/2+radius+1,x+dist/2,y+dist/2-radius-1,1);
                    drawPoints(i,j);
                }
                else if((!((mXhover>table[i-1][j].x+dist/2-L)&&(mXhover<table[i-1][j].x+dist/2+L)&&(mYhover<table[i-1][j].y+dist/2-L)&&(mYhover>table[i-1][j].y-dist/2+L)))&&(table[i][j].active == true))
                {
                    setcolor(BLACK);
                    if(table[i][j].left != true)
                        drawVline(x-dist/2,y-dist/2+radius+1,x-dist/2,y+dist/2-radius-1,1);
                    if(table[i][j].right != true)
                    {
                        drawVline(x+dist/2,y-dist/2+radius+1,x+dist/2,y+dist/2-radius-1,1);
                    }
                }
                //Stanga-Dreapta
                if((mYhover<y-dist/2+L)&&(mYhover>y-dist/2-L)&&(mXhover>x-dist/2+L)&&(mXhover<x+dist/2-L)&&(table[i][j].up != true)&&(table[i][j].active == true))
                {
                    setcolor(COLOR(70, 244, 65));
                    drawHline(x-dist/2+radius+1,y-dist/2,x+dist/2-radius-1,y-dist/2,1);
                }
                else if((mYhover<y+dist/2+L)&&(mYhover>y+dist/2-L)&&(mXhover<x+dist/2-L)&&(mXhover>x-dist/2+L)&&(table[i][j].down != true)&&(table[i][j].active == true))
                {
                    setcolor(COLOR(70, 244, 65));
                    drawHline(x-dist/2+radius+1,y+dist/2,x+dist/2-radius-1,y+dist/2,1);
                }
                else if((!((mYhover<table[i][j-1].y+dist/2+L)&&(mYhover>table[i][j-1].y+dist/2-L)&&(mXhover<table[i][j-1].x+dist/2-L)&&(mXhover>table[i][j-1].x-dist/2+L)))&&(table[i][j].active == true))
                {
                    setcolor(BLACK);
                    if(table[i][j].up != true)
                        drawHline(x-dist/2+radius+1,y-dist/2,x+dist/2-radius-1,y-dist/2,1);
                    if(table[i][j].down != true)
                        drawHline(x-dist/2+radius+1,y+dist/2,x+dist/2-radius-1,y+dist/2,1);
                }

            }

    }


}

void replayGame(unsigned int gameIndx)
{
    ifstream gameList;
    gameList.open("games.txt", ios::in);
    char index;
    unsigned int cnt = 0;
    while(gameList >> index)
    {
        if(index == 'D')
        {
            cnt++;
        }
        if(cnt == gameIndx)
        {
            break;
        }
    }
    int time = 0;
    int temp;
    while(gameList >> temp)
    {
        time = time * 10 + temp;
        index = gameList.peek();
        if(index == 'S')
        {
            break;
        }
    }
    gameList >> index;
    static int tType, tSize;
    gameList >> tSize;
    gameList >> index;
    gameList >> tType;
    gameList >> index;
    gameList >> index;
    static int i,j,dir,who;
    static bool comp1, comp2;
    bool done = false;
    while(!done)
    {
        comp1 = false;
        comp2 = false;
        Sleep(300);
        gameList >> i;
        gameList >> j;
        gameList >> dir;
        gameList >> who;
        player = who;
        switch(dir)
        {
        case 0:
            table[i][j].up = true;
            table[i][j].whoUP = who;
            if(j != 0)
            {
                table[i][j-1].down = true;
                table[i][j-1].whoDOWN = who;
            }
            comp1 = complete(i,j);
            if(j != 0)
                comp2 = complete(i,j-1);
            if(comp1 == true)
            {
                switch(who)
                {
                case 0:
                    table[i][j].who = 'A';
                    break;
                case 1:
                    table[i][j].who = 'B';
                    break;
                }
            }
            afisare(i,j);
            if((j != 0)&&(table[i][j-1].active == true))
            {
                if(comp2 == true)
                {
                    switch(who)
                    {
                    case 0:
                        table[i][j-1].who = 'A';
                        break;
                    case 1:
                        table[i][j-1].who = 'B';
                        break;
                    }

                }
                afisare(i,j-1);
            }

            break;
        case 1:
            table[i][j].right = true;
            table[i][j].whoRIGHT = who;
            if(i < matSize - 2)
            {
                table[i+1][j].left = true;
                table[i+1][j].whoLEFT = who;
            }
            comp1 = complete(i,j);
            if(i < matSize-2)
                comp2 = complete(i+1,j);
            if(comp1 == true)
            {
                switch(who)
                {
                case 0:
                    table[i][j].who = 'A';
                    break;
                case 1:
                    table[i][j].who = 'B';
                    break;
                }
            }
            afisare(i,j);
            if((i < matSize-2)&&(table[i+1][j].active == true))
            {
                if(comp2 == true)
                {
                    switch(who)
                    {
                    case 0:
                        table[i+1][j].who = 'A';
                        break;
                    case 1:
                        table[i+1][j].who = 'B';
                        break;
                    }
                }
                afisare(i+1,j);

            }
            break;
        case 2:
            table[i][j].down = true;
            table[i][j].whoDOWN = who;
            if(j < matSize - 2)
            {
                table[i][j+1].up = true;
                table[i][j+1].whoUP = who;
            }
            comp1 = complete(i,j);
            if(j != matSize-1)
                comp2 = complete(i,j+1);
            if(comp1 == true)
            {
                switch(who)
                {
                case 0:
                    table[i][j].who = 'A';
                    break;
                case 1:
                    table[i][j].who = 'B';
                    break;
                }
            }
            afisare(i,j);
            if((j != matSize - 2)&&(table[i][j+1].active == true))
            {
                if(comp2 == true)
                {
                    switch(who)
                    {
                    case 0:
                        table[i][j+1].who = 'A';
                        break;
                    case 1:
                        table[i][j+1].who = 'B';
                        break;
                    }
                }
                afisare(i,j+1);

            }
            break;
        case 3:
            table[i][j].left = true;
            table[i][j].whoLEFT = who;
            if(i > 0)
            {
                table[i-1][j].right = true;
                table[i-1][j].whoRIGHT = who;
            }
            comp1 = complete(i,j);
            if(i != 0)
                comp2 = complete(i-1,j);
            if(comp1 == true)
            {
                switch(who)
                {
                case 0:
                    table[i][j].who = 'A';
                    break;
                case 1:
                    table[i][j].who = 'B';
                    break;
                }
            }
            afisare(i,j);
            if((i != 0)&&(table[i-1][j].active == true))
            {
                if(comp2 == true)
                {
                    switch(who)
                    {
                    case 0:
                        table[i-1][j].who = 'A';
                        break;
                    case 1:
                        table[i-1][j].who = 'B';
                        break;
                    }
                }
                afisare(i-1,j);

            }
            break;
        }
        score();
        endcond(done);
        if(done == true)
        {
            return;
        }
    }
}

void saveGame(lista L, int winner)
{
    nod* n;
    ofstream game;
    game.open("games.txt",std::fstream::out | std::fstream::app);
    ifstream sets;
    sets.open("settings.txt", fstream::in | std::fstream::app);
    n = L.last;
    unsigned int tSize, tType;
    sets >> tSize;
    for(int i = 0; i < 6; i++)
    {
        sets >> tType;
    }
    game <<"D"<< time(NULL);
    game <<"S"<< tSize;
    game <<"T"<< tType;
    game <<"W"<< winner;
    game << "\n";
    while(n != NULL)
    {
        game << n->i << " ";
        game << n->j << " ";
        game << n->direction << " ";
        switch(n->direction)
        {
        case 0:
            game << table[n->i][n->j].whoUP << " ";
            break;
        case 1:
            game << table[n->i][n->j].whoRIGHT << " ";
            break;
        case 2:
            game << table[n->i][n->j].whoDOWN << " ";
            break;
        case 3:
            game << table[n->i][n->j].whoLEFT << " ";
            break;
        }
        game <<"\n";
        n = n->prev;

    }
    game.close();
    sets.close();

}
//Afiseaza jucatorul castigator
//Constantin
void gameOver(lista &L)
{
    int len;
    int win;
    if(players.scoreP1 > players.scoreP2)
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(P1color);
        char winner[] = "PLAYER1 WINS";
        len = textwidth(winner);
        setbkcolor(BKcolor);
        outtextxy(initX-len/2,5,winner);
        outtextxy(initX-len/2,getmaxy()-textheight(winner),winner);
        win = 0;
    }
    else if(players.scoreP1 < players.scoreP2)
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(P2color);
        char winner[] = "PLAYER2 WINS";
        len = textwidth(winner);
        setbkcolor(BKcolor);
        outtextxy(initX-len/2,5,winner);
        outtextxy(initX-len/2,getmaxy()-textheight(winner),winner);
        win = 1;
    }
    else
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(COLOR(16, 239, 53));
        char winner[] = "DRAW";
        len = textwidth(winner);
        setbkcolor(COLOR(61, 153, 112));
        outtextxy(initX-len/2,5,winner);
        outtextxy(initX-len/2,getmaxy()-textheight(winner),winner);
        win = 2;
    }
    saveGame(L, win);
    resetList(L);
    int bX,bY;
    while(true)
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,bX,bY);
            if(checkMouse(100,getmaxy()-200,60,160,bX,bY))
            {
                return;
            }
        }
}
//Malina
void endcond(bool& done)
{
    if(rhTable == true || plusTable == true)
    {
        done = true;
        for(int i = 0; i < matSize - 1; i++)
            for(int j = 0; j < matSize - 1; j++)
            {
                if((table[i][j].complete == false)&&(table[i][j].active == true))
                    done = false;
            }
    }
    else if(players.scoreP1+players.scoreP2 == (matSize-1)*(matSize-1))
    {
        done = true;
    }

}
//Pentru meniu
bool checkMouse(int x, int y, int lat, int ln, int X, int Y)
{
    if((X>x-ln/2)&&(X<x+ln/2)&&(Y<y+lat/2)&&(Y>y-lat/2))
        return true;
    return false;

}

void checkPlayer(int i, int j, int dir)
{
    switch(dir)
    {
    case 0:
        player = table[i][j].whoUP;
        break;
    case 1:
        player = table[i][j].whoRIGHT;
        break;
    case 2:
        player = table[i][j].whoDOWN;
        break;
    case 3:
        player = table[i][j].whoLEFT;
        break;
    }
}

void undoFeature(lista &stiva, bool forced)
{
    if((checkMouse(100,getmaxy()-100,45,49,mX,mY)||forced)&&(stiva.first != NULL))
    {
        mX = 0;
        mY = 0;
        int I = stiva.first->i;
        int J = stiva.first->j;
        int dir = stiva.first->direction;
        nod *n;
        switch(dir)
        {
        case 0:
            table[I][J].up = false;
            table[I][J].cnt--;
            if(J>0)
            {
                table[I][J-1].down = false;
                table[I][J-1].cnt--;
            }

            if(table[I][J].complete == true)
            {
                table[I][J].complete = false;
                switch(table[I][J].who)
                {
                case 'A':
                    players.scoreP1--;
                    break;
                case 'B':
                    players.scoreP2--;
                    break;
                }
            }
            if(table[I][J-1].complete == true)
            {
                table[I][J-1].complete = false;
                switch(table[I][J-1].who)
                {
                case 'A':
                    players.scoreP1--;
                    break;
                case 'B':
                    players.scoreP2--;
                    break;
                }
            }

            cover(table[I][J].x,table[I][J].y);
            afisare(I,J);
            if((J>0)&&(table[I][J-1].active == true))
            {
                cover(table[I][J-1].x,table[I][J-1].y);
                afisare(I,J-1);
            }
            break;
        case 1:
            table[I][J].right = false;
            table[I][J].cnt--;
            if(I<matSize-2)
            {
                table[I+1][J].left = false;
                table[I+1][J].cnt--;
            }

            if(table[I][J].complete == true)
            {
                table[I][J].complete = false;
                switch(table[I][J].who)
                {
                case 'A':
                    players.scoreP1--;
                    break;
                case 'B':
                    players.scoreP2--;
                    break;
                }
            }

            if(table[I+1][J].complete == true)
            {
                table[I+1][J].complete = false;
                switch(table[I+1][J].who)
                {
                case 'A':
                    players.scoreP1--;
                    break;
                case 'B':
                    players.scoreP2--;
                    break;
                }
            }
            cover(table[I][J].x,table[I][J].y);
            afisare(I,J);
            if((I < matSize - 2)&&(table[I+1][J].active == true))
            {
                cover(table[I+1][J].x,table[I+1][J].y);
                afisare(I+1,J);
            }
            break;
        case 2:
            table[I][J].down = false;
            table[I][J].cnt--;
            if(J<matSize-2)
            {
                table[I][J+1].up = false;
                table[I][J+1].cnt--;
            }

            if(table[I][J].complete == true)
            {
                table[I][J].complete = false;
                switch(table[I][J].who)
                {
                case 'A':
                    players.scoreP1--;
                    break;
                case 'B':
                    players.scoreP2--;
                    break;
                }
            }

            if(table[I][J+1].complete == true)
            {
                table[I][J+1].complete = false;
                switch(table[I][J+1].who)
                {
                case 'A':
                    players.scoreP1--;
                    break;
                case 'B':
                    players.scoreP2--;
                    break;
                }
            }
            cover(table[I][J].x,table[I][J].y);
            afisare(I,J);
            if((J < matSize - 2)&&(table[I][J+1].active == true))
            {
                cover(table[I][J+1].x,table[I][J+1].y);
                afisare(I,J+1);
            }
            break;
        case 3:
            table[I][J].left = false;
            table[I][J].cnt--;
            if(I>0)
            {
                table[I-1][J].right = false;
                table[I-1][J].cnt--;
            }

            if(table[I][J].complete == true)
            {
                table[I][J].complete = false;
                switch(table[I][J].who)
                {
                case 'A':
                    players.scoreP1--;
                    break;
                case 'B':
                    players.scoreP2--;
                    break;
                }
            }

            if(table[I-1][J].complete == true)
            {
                table[I-1][J].complete = false;
                switch(table[I-1][J].who)
                {
                case 'A':
                    players.scoreP1--;
                    break;
                case 'B':
                    players.scoreP2--;
                    break;
                }
            }
            cover(table[I][J].x,table[I][J].y);
            afisare(I,J);
            if((I > 0)&&(table[I-1][J].active == true))
            {
                cover(table[I-1][J].x,table[I-1][J].y);
                afisare(I-1,J);
            }
            break;
        }

        checkPlayer(I,J,dir);
        nod *p, *q;
        p = stiva.first;
        q = stiva.first->next;
        delete p;
        stiva.first = q;
        updateScore();
        if(player == 1 && isP2PC)
        {
            undoFeature(stiva, true);
        }

    }
}
// ESC = 27;
bool pause()
{
    int key;
    bool exit = true;
    if(kbhit())
    {
        key = getch();
        if(key == 27)
        {
            exit = startMenu();
        }
    }
    return exit;
}
int replay = 1;

void resetSettings()
{
    fstream settings;
    settings.open("settings.txt", ios::in);
    int temp;
    settings >> temp;
    initTableType(temp);
    settings >> temp;
    settings >> temp;
    settings >> temp;
    settings >> temp;
    settings >> temp;
    initTableType(temp);
}

void replayTable()
{
    PlaySound(NULL,NULL,SND_FILENAME);

    resetSquares();

    initSquare();

    cleardevice();

    displayBackground();

    updateScore();

    for(int j = 0; j < matSize-1; j++)
        for(int i = 0; i < matSize-1; i++)
        {
            if(rhTable == true || plusTable == true)
            {
                if(table[i][j].active == true)
                    drawPoints(i,j);
            }
            else
                drawPoints(i,j);
        }

    bool done = false;
    int x,y;
    while(!done)
    {
        replayGame(replay);
        endcond(done);
    }
    getch();
    show = 0;
    resetSettings();
    cleardevice();
    //startMenu();
}
// UP-0, DOWN-1, RIGHT-2, LEFT-3
//Functia pricipala care verifica daca jucatorul face click intre doua puncte
//Constantin
bool check()
{
    void* undoButton = new char[imagesize(0, 0, 49, 49)];
    void* undoButton_pressed = new char[imagesize(0, 0, 49, 45)];
    void* menuButton = new char[imagesize(0, 0, 105, 49)];
    void* menuButton_pressed = new char[imagesize(0, 0, 105, 45)];
    displayBackground();

    readimagefile("assets/undobutton.gif",0,0,49,49);
    getimage(0,0,49,49,undoButton);


    readimagefile("assets/undobutton_pressed.gif",0,0,49,45);
    getimage(0,0,49,45,undoButton_pressed);


    readimagefile("assets/menubutton.gif",0,0,105,49);
    getimage(0,0,105,49,menuButton);


    readimagefile("assets/menubutton_pressed.gif",0,0,105,45);
    getimage(0,0,105,45,menuButton_pressed);
    cleardevice();

    lista stiva;

    initLista(stiva);

    PlaySound(NULL,NULL,SND_FILENAME);

    resetSquares();

    initSquare();

    cleardevice();

    displayBackground();

    updateScore();

    setcolor(WHITE);
    putimage(100 - 49/2, getmaxy()-100 - 49/2, undoButton, 0);


    //drawButton(100, getmaxy()-100, "UNDO");
    putimage(100 - 105/2, getmaxy()-200 - 49/2, menuButton, 0);
    for(int j = 0; j < matSize-1; j++)
        for(int i = 0; i < matSize-1; i++)
        {
            if(rhTable == true || plusTable == true)
            {
                if(table[i][j].active == true)
                    drawPoints(i,j);
            }
            else
                drawPoints(i,j);

        }
    bool done = false;
    int x,y;

    while(!done)
    {
        bool exit = true, pressed = false;
        hover();
        exit = pause();


        int bX, bY;
        //Exit
        if(isP1PC && isP2PC)
        {
            Sleep(200);
            clearmouseclick(WM_LBUTTONUP);
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN,bX,bY);

                if(checkMouse(100,getmaxy()-200,49,105,bX,bY))
                {
                    buttonCover(100, getmaxy() - 200, 105, 49, BKcolor);
                    putimage(100 - 105/2, getmaxy()-200 - 45/2+4, menuButton_pressed, 0);
                    pressed = true;
                    while(pressed)
                    {
                        if(ismouseclick(WM_LBUTTONUP))
                        {
                            clearmouseclick(WM_LBUTTONUP);
                            buttonCover(100, getmaxy() - 200, 105, 49, BKcolor);
                            putimage(100 - 105/2, getmaxy()-200 - 49/2, menuButton, 0);
                            Sleep(200);
                            exit = false;
                            pressed = false;
                        }
                    }
                }

            }


        }
        if(exit == false)
        {
            return false;
        }
        else if(player == 0 && isP1PC)
        {
            Sleep(300);
            actionEasy(stiva);
        }
        else if(player == 1 && isP2PC)
        {
            Sleep(300);
            actionEasy(stiva);
        }
        else if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,mX,mY);
            if((checkMouse(100,getmaxy()-100,45,49,mX,mY))&&(stiva.first != NULL))
            {
                buttonCover(100, getmaxy()-100, 49, 49, BKcolor);
                putimage(100 - 49/2, getmaxy()-100 - 45/2, undoButton_pressed, 0);
                pressed = true;
            }
            clearmouseclick(WM_LBUTTONUP);
            while(pressed)
            {
                if(ismouseclick(WM_LBUTTONUP))
                {
                    clearmouseclick(WM_LBUTTONUP);
                    buttonCover(100, getmaxy()-100, 49, 49, BKcolor);
                    putimage(100 - 49/2, getmaxy()-100 - 49/2, undoButton, 0);
                    undoFeature(stiva, false);
                    pressed = false;
                }
            }


            for(int j = 0; j < matSize-1; j++)
                for(int i = 0; i < matSize-1; i++)

                {
                    x = table[i][j].x;
                    y = table[i][j].y;
                    //Left side
                    if((mX<x-dist/2+L)&&(mX>x-dist/2-L)&&(mY>y-dist/2+L)&&(mY<y+dist/2-L)&&(table[i][j].left != true)&&(table[i][j].active == true))
                    {
                        table[i][j].left = true;
                        table[i][j].cnt++;
                        table[i][j].whoLEFT = player;
                        addMove(i,j,3,stiva);
                        if(i>0)
                        {
                            table[i-1][j].right = true;
                            table[i-1][j].cnt++;
                            table[i-1][j].whoRIGHT = player;
                        }
                        complete(i,j);
                        if(i != 0)
                            complete(i-1,j);
                        if((table[i][j].complete == false)&&(table[i-1][j].complete == false)&&(i != 0))
                        {
                            turn();
                        }
                        else if((table[i][j].complete == false)&&(i == 0))
                        {
                            turn();
                        }
                        else if((table[i][j].complete == true)||(table[i-1][j].complete == true))
                        {
                            score();
                        }

                        afisare(i,j);
                        if((i != 0)&&(table[i-1][j].active == true))
                            afisare(i-1,j);
                        PlaySound("floop2_x.wav", NULL, SND_FILENAME|SND_ASYNC);

                    }
                    else
                        //Right side
                        if((mX>x+dist/2-L)&&(mX<x+dist/2+L)&&(mY<y+dist/2-L)&&(mY>y-dist/2+L)&&(table[i][j].right != true)&&(table[i][j].active == true))
                        {
                            table[i][j].right = true;
                            table[i][j].cnt++;
                            table[i][j].whoRIGHT = player;
                            addMove(i,j,1,stiva);

                            if(i<matSize-2)
                            {
                                table[i+1][j].left = true;
                                table[i+1][j].cnt++;
                                table[i+1][j].whoLEFT = player;
                            }
                            complete(i,j);
                            if(i < matSize-2)
                                complete(i+1,j);
                            if((table[i][j].complete == false)&&(table[i+1][j].complete == false)&&(i != matSize-2))
                            {
                                turn();
                            }
                            else if((table[i][j].complete == false)&&(i == matSize-2))
                            {
                                turn();
                            }
                            else if((table[i][j].complete == true)||(table[i+1][j].complete == true))
                            {
                                score();
                            }

                            afisare(i,j);
                            if((i < matSize-2)&&(table[i+1][j].active == true))
                                afisare(i+1,j);
                            PlaySound("floop2_x.wav", NULL, SND_FILENAME|SND_ASYNC);
                        }
                        else
                            //Down side
                            if((mY<y+dist/2+L)&&(mY>y+dist/2-L)&&(mX<x+dist/2-L)&&(mX>x-dist/2+L)&&(table[i][j].down != true)&&(table[i][j].active == true))
                            {
                                table[i][j].down = true;
                                table[i][j].cnt++;
                                table[i][j].whoDOWN = player;
                                addMove(i,j,2,stiva);

                                if(j<matSize-2)
                                {
                                    table[i][j+1].up = true;
                                    table[i][j+1].cnt++;
                                    table[i][j+1].whoUP = player;
                                }
                                complete(i,j);
                                if(j != matSize-1)
                                    complete(i,j+1);
                                if((table[i][j].complete == false)&&(table[i][j+1].complete == false)&&(j != matSize-2))
                                {
                                    turn();
                                }
                                else if((table[i][j].complete == false)&&(j == matSize-2))
                                {
                                    turn();
                                }
                                else if((table[i][j].complete == true)||(table[i][j+1].complete == true))
                                {
                                    score();
                                }

                                afisare(i,j);
                                if((j != matSize - 2)&&(table[i][j+1].active == true))
                                    afisare(i,j+1);
                                PlaySound("floop2_x.wav", NULL, SND_FILENAME|SND_ASYNC);
                            }
                            else
                                //Up side
                                if((mY<y-dist/2+L)&&(mY>y-dist/2-L)&&(mX>x-dist/2+L)&&(mX<x+dist/2-L)&&(table[i][j].up != true)&&(table[i][j].active == true))
                                {
                                    table[i][j].up = true;
                                    table[i][j].cnt++;
                                    table[i][j].whoUP = player;
                                    addMove(i,j,0,stiva);
                                    if(j>0)
                                    {
                                        table[i][j-1].down = true;
                                        table[i][j-1].cnt++;
                                        table[i][j-1].whoDOWN = player;
                                    }
                                    complete(i,j);
                                    if(j != 0)
                                        complete(i,j-1);
                                    if((table[i][j].complete == false)&&(table[i][j-1].complete == false)&&(j != 0))
                                    {
                                        turn();
                                    }
                                    else if((table[i][j].complete == false)&&(j == 0))
                                    {
                                        turn();
                                    }
                                    else if((table[i][j].complete == true)||(table[i][j-1].complete == true))
                                    {
                                        score();
                                    }

                                    afisare(i,j);
                                    if((j != 0)&&(table[i][j-1].active == true))
                                        afisare(i,j-1);
                                    PlaySound("floop2_x.wav", NULL, SND_FILENAME|SND_ASYNC);
                                }

                }
            if(checkMouse(100,getmaxy()-200,49,105,mX,mY))
            {
                buttonCover(100, getmaxy() - 200, 115, 50, BKcolor);
                putimage(100 - 105/2, getmaxy()-200 - 45/2+4, menuButton_pressed, 0);
                pressed = true;

            }
            clearmouseclick(WM_LBUTTONUP);
            while(pressed)
            {
                if(ismouseclick(WM_LBUTTONUP))
                {
                    clearmouseclick(WM_LBUTTONUP);
                    buttonCover(100, getmaxy() - 200 + 5, 115, 50, BKcolor);
                    putimage(100 - 105/2, getmaxy()-200 - 49/2, menuButton, 0);
                    Sleep(100);
                    exit = false;
                    pressed = false;
                }
            }
        }

        if(exit == false)
        {
            return false;
        }
        //Daca suma dintre scorurile celor 2 jucatori este egal cu patratul maximului matricii atunci jocul s-a terminat
        endcond(done);
    }
    delete undoButton;
    delete undoButton_pressed;
    gameOver(stiva);
    return true;
}


