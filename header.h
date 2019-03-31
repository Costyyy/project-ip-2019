#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

struct square
{
    bool up = false;
    bool whoUP; // retine care dintre jucatori a desenat o linie
    bool down = false;
    bool whoDOWN;
    bool left = false;
    bool whoLEFT;
    bool right = false;
    bool whoRIGHT;
    bool complete = false;
    bool active = false;
    unsigned int cnt = 0;
    int x,y;
    char who; // retine care dintre jucatori a completat patratul
};

struct nod
{
    int i, j;
    int direction;
    nod *next;
    nod *prev;
};

struct lista
{
    nod *first;
    nod *last;
};

extern square table[15][15];

extern bool player;

extern unsigned int show;

extern bool rhTable;
extern bool plusTable;

/*
menu = 0;
options = 1;
settings = 2;
exit = 3;


*/

extern bool isP1PC;

extern bool isP2PC;

extern int matSize;

extern int initX, initY;

extern int replay;

void initCenterM();

void initSquare();

void tut();

void initAssets();

void buttonCover(int x, int y, int ln, int lat, int color);

void afisare(int i, int j);

bool check();

void replayTable();

bool complete(int i, int j);

void menu();

bool checkMouse(int x, int y, int lat, int ln, int X, int Y);

void gameOver();

void initRes(int res);

void updateScore();

void cover(int x, int y);

void drawPoints(int i,int j);

void actionEasy(lista &L);

void actionMedium(lista &L);

void turn();

void score();

bool startMenu();

void setTableSize(unsigned int lat);

void initTableType(int type);

void resetSquares();

void initColors(int P1C, int P2C, int BKC);

void addMove(int i, int j, int dir, lista &L);
#endif // HEADER_H_INCLUDED
