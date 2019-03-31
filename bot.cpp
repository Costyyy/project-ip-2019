#include "header.h"
#include <random>
#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;
//Constantin
bool template1(int i, int j, lista &L)
{
    bool done = false;
    if(table[i][j].up != true)
    {
        done = true;
        table[i][j].up = true;
        table[i][j].cnt++;
        table[i][j].whoUP = player;
        addMove(i,j,0,L);
        if(j>0)
        {
            table[i][j-1].down = true;
            table[i][j-1].cnt++;
            table[i][j-1].whoDOWN = player;
        }
        complete(i,j);

        if(j != 0)
            complete(i,j-1);

        if((table[i][j].complete == false)&&(table[i][j-1].complete == false))
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
    return done;
}
//Constantin
bool template2(int i, int j, lista &L)
{
    bool done = false;
    if(table[i][j].right != true)
    {
        done = true;
        table[i][j].right = true;
        table[i][j].cnt++;
        table[i][j].whoRIGHT = player;
        addMove(i,j,1,L);
        if(i<matSize-2)
        {
            table[i+1][j].left = true;
            table[i+1][j].cnt++;
            table[i+1][j].whoLEFT = player;
        }
        complete(i,j);

        if(i != matSize-1)
            complete(i+1,j);

        if((table[i][j].complete == false)&&(table[i+1][j].complete == false))
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
    return done;
}
//Constantin
bool template3(int i, int j, lista &L)
{
    bool done = false;
    if(table[i][j].down != true)
    {
        done = true;
        table[i][j].down = true;
        table[i][j].cnt++;
        table[i][j].whoDOWN = player;
        addMove(i,j,2,L);
        if(j<matSize-2)
        {
            table[i][j+1].up = true;
            table[i][j+1].cnt++;
            table[i][j+1].whoUP = player;
        }
        complete(i,j);

        if(j != matSize-1)
            complete(i,j+1);

        if((table[i][j].complete == false)&&(table[i][j+1].complete == false))
        {
            turn();
        }
        else if((table[i][j].complete == false)&&(j == matSize-1))
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
    return done;
}
//Constantin
bool template4(int i, int j, lista &L)
{
    bool done = false;

    if(table[i][j].left != true)
    {
        done = true;
        table[i][j].left = true;
        table[i][j].cnt++;
        table[i][j].whoLEFT = player;
        addMove(i,j,3,L);
        if(i > 0)
        {
            table[i-1][j].right = true;
            table[i-1][j].cnt++;
            table[i-1][j].whoRIGHT = player;
        }
        complete(i,j);

        if(i > 0)
            complete(i-1,j);

        if((table[i][j].complete == false)&&(table[i-1][j].complete == false))
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
    return done;
}
//Constantin
void action(lista &L)
{
    unsigned int side,i,j;
    bool done;
    srand(time(NULL));
    do
    {
        i = rand()%(matSize-1);
        j = rand()%(matSize-1);
    }
    while(table[i][j].complete == true);
    do
    {
        side = rand()%4;
        switch(side)
        {
        case 0:
            done = template1(i,j,L);
            break;
        case 1:
            done = template2(i,j,L);
            break;
        case 2:
            done = template3(i,j,L);
            break;
        case 3:
            done = template4(i,j,L);
            break;
        }
    }
    while(done == false);
}

int checkSides(int i, int j)
{
    bool up = false, down = false, left = false, right = false;
    int side;
    if(table[i][j].cnt == 2)
    {
        return -1;
    }
    if(table[i][j].cnt != 2)
    {
        if((table[i][j].up == false)&&((j == 0)||(table[i][j-1].cnt != 2)))
        {
            up = true;
        }
        if((table[i][j].right == false)&&((table[i+1][j].cnt != 2)||(i==matSize-2)))
        {
            right = true;
        }
        if((table[i][j].down == false)&&((table[i][j+1].cnt != 2)||(j==matSize-2)))
        {
            down = true;
        }
        if((table[i][j].left == false)&&((table[i-1][j].cnt != 2)||(i == 0)))
        {
            left = true;
        }
    }
    srand(time(NULL));

    if((up == false)&&(right == false)&&(down == false)&&(left == false))
    {
        return -1;
    }
    do
    {
        side = rand()%4;
        switch(side)
        {
        case 0:
            if(up == true)
            {
                return 0;
            }
            break;
        case 1:
            if(down == true)
            {
                return 2;
            }
            break;
        case 2:
            if(right == true)
            {
                return 1;
            }
            break;
        case 3:
            if(left == true)
            {
                return 3;
            }
            break;
        }
        //cout<<"Here\n";

    }
    while(true);

}

void visited(bool viz[][15],bool &allViz)
{
    for(int indx = 0; indx < matSize-1; indx++)
    {

        for(int jndx = 0; jndx < matSize-1; jndx++)
        {

            if((viz[indx][jndx] != true))
            {
                allViz = false;
                break;
            }
            allViz = true;
        }
        if(allViz == false)
            break;
    }
}
int chooseSide(int i, int j)
{
    int vars[4]= {-1,-1,-1,-1},cnt=0, val;

    if(table[i][j].up == false)
    {

        for(int in = 0; in < 4; in++)
        {
            if(vars[in] == -1)
            {
                //cout<<"Up done"<<" I:"<<i<<" J:"<<j<<"\n";
                vars[in] = 0;
                cnt++;
                break;
            }
        }
    }
    if(table[i][j].right == false)
    {

        for(int in = 0; in < 4; in++)
        {
            if(vars[in] == -1)
            {
                //cout<<"Right done"<<" I:"<<i<<" J:"<<j<<"\n";
                vars[in] = 1;
                cnt++;
                break;
            }
        }
    }
    if(table[i][j].down == false)
    {

        for(int in = 0; in < 4; in++)
        {
            if(vars[in] == -1)
            {
                //cout<<"Down done"<<" I:"<<i<<" J:"<<j<<"\n";
                vars[in] = 2;
                cnt++;
                break;
            }
        }
    }
    if(table[i][j].left == false)
    {

        for(int in = 0; in < 4; in++)
        {
            if(vars[in] == -1)
            {
                //cout<<"Left done"<<" I:"<<i<<" J:"<<j<<"\n";
                vars[in] = 3;
                cnt++;
                break;
            }
        }
    }
    //cout<<"Here3\n";
    val = rand()%cnt;
    //cout<<"Value:"<<vars[val]<<"\n";
    return vars[val];

}

void chooseSide_chain(int i, int j, int vars[])
{
    int cnt=0, val;

    if(table[i][j].up == false)
    {

        for(int in = 0; in < 4; in++)
        {
            if(vars[in] == -1)
            {
                //cout<<"Up done"<<" I:"<<i<<" J:"<<j<<"\n";
                vars[in] = 0;
                cnt++;
                break;
            }
        }
    }
    if(table[i][j].right == false)
    {

        for(int in = 0; in < 4; in++)
        {
            if(vars[in] == -1)
            {
                //cout<<"Right done"<<" I:"<<i<<" J:"<<j<<"\n";
                vars[in] = 1;
                cnt++;
                break;
            }
        }
    }
    if(table[i][j].down == false)
    {

        for(int in = 0; in < 4; in++)
        {
            if(vars[in] == -1)
            {
                //cout<<"Down done"<<" I:"<<i<<" J:"<<j<<"\n";
                vars[in] = 2;
                cnt++;
                break;
            }
        }
    }
    if(table[i][j].left == false)
    {

        for(int in = 0; in < 4; in++)
        {
            if(vars[in] == -1)
            {
                //cout<<"Left done"<<" I:"<<i<<" J:"<<j<<"\n";
                vars[in] = 3;
                cnt++;
                break;
            }
        }
    }
    //cout<<"Here3\n";
    //val = rand()%cnt;
    //cout<<"Value:"<<vars[val]<<"\n";
    //return vars;

}

void chain(int i, int j, bool marked[][15])
{
    int vars[4]= {-1,-1,-1,-1};
    if(marked[i][j] == true)
    {
        return;
    }
    marked[i][j] = true;
    int cnt = 0;
    chooseSide_chain(i,j, vars);
    int side;
    while(side != -1)
    {
        side = -1;
        for(; cnt < 4; cnt++)
        {
            if (vars[cnt] != -1)
            {
                side = vars[cnt];
                break;
            }
        }
        switch(side)
        {
        case 0:
            if(j>0 && table[i][j-1].active == true)
            {
                chain(i, j-1, marked);
            }
            break;
        case 1:
            if(i < matSize-2 && table[i+1][j].active == true)
            {
                chain(i+1, j, marked);
            }
            break;
        case 2:
            if(j < matSize-2 && table[i][j+1].active == true)
            {
                chain(i, j+1, marked);
            }
            break;
        case 3:
            if(i>0 && table[i-1][j].active == true)
            {
                chain(i-1, j, marked);
            }
            break;
        }
    }

}

void actionEasy(lista &L)
{
    bool done = false;
    do
    {
        int side,i=matSize,j=matSize;
        bool stage1 = false, stage2 = false;
        bool viz[15][15];
        for(int st = 0; st < 15; st++)
        {
            for(int sc = 0; sc < 15; sc++)
            {
                if(table[sc][st].active == true)
                {
                    viz[sc][st] = false;
                }
                else if(table[sc][st].active == false)
                {
                    viz[sc][st] = true;
                }

            }
        }
        bool allViz = false;
        srand(time(NULL));
        stage1 = false;
        for(int in = 0; in < matSize-1; in++)
        {
            for(int jn = 0; jn < matSize-1; jn++)
            {
                if((table[in][jn].cnt < 2)&&(table[in][jn].active == true))
                {
                    stage1 = true;
                    //cout<<"IN:"<<in<<" JN:"<<jn<<" cnt:"<<table[in][jn].cnt<<"\n";
                    break;
                }
            }
            if(stage1 == true)
                break;
        }

        if(stage1 == false)
        {
            stage2 = true;
        }
        bool found_S1 = false;
        for(i = 0; i < matSize - 1; i++)
        {
            for(j = 0; j < matSize - 1; j++)
            {
                if(table[i][j].cnt == 3 && table[i][j].active == true)
                {
                    found_S1 = true;
                    break;
                }

            }
            if(found_S1 == true)
            {
                cout<<"I: "<<i<<"J: "<<j<<"\n";
                break;
            }
        }

        if(stage1 == true && found_S1 == false)
        {
            do
            {
                do
                {
                    //cout<<"Here2\n";
                    viz[i][j] = true;
                    visited(viz, allViz);
                    i = rand()%(matSize-1);
                    j = rand()%(matSize-1);
                }
                while((table[i][j].complete == true)||((viz[i][j] == true)&&(allViz == false))||(table[i][j].active == false));
                viz[i][j] = true;
                visited(viz, allViz);
            }
            while((checkSides(i,j) == -1)&&(allViz == false));

            if((checkSides(i,j) == -1)&&(allViz == true))
            {
                cout<<"Here\n";
                bool found = false;
                for(i = 0; i < matSize-1; i++)
                {
                    for(j = 0; j < matSize-1; j++)
                    {
                        if((table[i][j].cnt < 2)&&(table[i][j].active == true))
                        {
                            cout<<"Is2:"<<i<<"Js2:"<<j<<"\n";
                            found = true;
                            break;
                        }
                    }
                    if(found == true)
                    {
                        //cout<<"Done: i:"<<i<<" j:"<<j<<"\n";
                        break;
                    }

                }
            }
        }
        else if(stage2 == true)
        {
            //stage2
            bool fComp = false;

            struct cell
            {
                bool marked[15][15];

                int maxChain;
                int i;
                int j;
            };

            bool marked[15][15];


            for(int i = 0; i < 15; i++)
                for(int j = 0; j < 15; j++)
                {
                    marked[i][j] = false;
                }
            for(i = 0; i < matSize-1; i++)
            {
                for(j = 0; j < matSize-1; j++)
                {
                    if(table[i][j].cnt == 3)
                    {
                        fComp = true;
                        break;
                    }
                }
                if(fComp == true)
                    break;
            }

            if(fComp == false)
            {
                do
                {
                    i = rand()%(matSize-1);
                    j = rand()%(matSize-1);
                }
                while((table[i][j].complete == true)||(table[i][j].active == false));
            }

        }
        if(stage1 == true)
        {
            side = checkSides(i,j);
            //cout<<"SIDEPRIEM1:"<<side<<"\n";
        }

        if((stage2 == true)||(side == -1))
        {
            side = chooseSide(i,j);
            //cout<<"SIDEPRIEM:"<<side<<"\n";
        }

        switch(side)
        {
        case 0:
            done = template1(i,j,L);
            //cout<<"Side:"<<side<<" I:"<<i<<" J:"<<j<<" Viz:"<<allViz<<"\n";
            break;
        case 1:
            done = template2(i,j,L);
            //cout<<"Side:"<<side<<" I:"<<i<<" J:"<<j<<" Viz:"<<allViz<<"\n";
            break;
        case 2:
            done = template3(i,j,L);
            //cout<<"Side:"<<side<<" I:"<<i<<" J:"<<j<<" Viz:"<<allViz<<"\n";
            break;
        case 3:
            done = template4(i,j,L);
            //cout<<"Side:"<<side<<" I:"<<i<<" J:"<<j<<" Viz:"<<allViz<<"\n";
            break;
        }
        //cout<<done<<"\n";
        cout<<"Side:"<<side<<" I:"<<i<<" J:"<<j<<" Viz:"<<allViz<<"\n";
        if(stage1 == true)
            cout<<"Stage1 true\n";
        else if(stage2 == true)
        {
            cout<<"Stage2 true\n";
        }
    }
    while(!done);
}

void actionMedium()
{




}





