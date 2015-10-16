/*
 *--------------------------------------------------------------------------
 *   File Name: Mine.cc
 * 
 *      Author: Zhao Yanbai [zhaoyanbai@126.com]
 *              Sat Feb 26 19:41:52 2011
 * 
 * Description: none
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
typedef struct
{
    bool    isMine;
    bool    isOpen;
    int     Neghbors;
} Mine;
    
const int maxrow = 100;
const int maxcol = 100;
Mine map[maxrow][maxcol];
int    R, C, N;


bool isMine(int row, int col)
{
    if(row<0 || col <0 || row>=R || col>=C) return false;
    return map[row][col].isMine;
}
void Mark()
{
    for(int i=0; i<R; i++)
    {
        for(int j=0; j<C; j++)
        {
            if(map[i][j].isMine) continue;
            int count=0;
            for(int m=i-1; m<=i+1; m++)
            {
                for(int n=j-1; n<=j+1; n++)
                {
                    if(isMine(m, n))
                    {
                        count++;
                    }
                }
            }
            map[i][j].Neghbors = count;
        }
    }
}

void CreateMap(const int row, const int col, const int n)
{
    int r, c;

    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            map[i][j].isMine = false;
            map[i][j].isOpen = false;
            map[i][j].Neghbors = 0;
        }
    }

    srand(time(NULL));

    for(int i=0; i<n; i++)
    {
        while(true)
        {
            r = rand() % row;
            c = rand() % col;
            if(map[r][c].isMine) continue;
            map[r][c].isMine = true;
            break;
        }
    }

    Mark();
}

void PrintMap()
{
    cout<<" ";
    for(int i=0; i<C; i++)
        cout<<" "<<i;
    cout<<endl;
    for(int i=0; i<R; i++)
    {
        cout<<i<<" ";
        for(int j=0; j<C; j++)
        {
            if(!map[i][j].isOpen)
            {
                cout<<"# ";
                continue;
            }

            if(map[i][j].isMine)
            {
                cout<<"* ";
            }
            else
            {
                if(map[i][j].Neghbors>0)
                    cout<<map[i][j].Neghbors<<" ";
                else
                {
                    cout<<"  ";
                }
            }
        }
        cout<<endl;
    }
}


void EraseZeroGrid(int row, int col)
{
    if(row<0 || row>=R || col<0 || col >=C) return;

    if(map[row][col].isOpen) return;
    map[row][col].isOpen = true;
    if(map[row][col].Neghbors>0) return;


    for(int i=row-1; i<=row+1; i++)
        for(int j=col-1; j<=col+1; j++)
        {
            if(i==row && j==col) continue;
            EraseZeroGrid(i, j);
        }


}

bool Click(int row, int col)
{
    if(map[row][col].isMine) return false;

    EraseZeroGrid(row, col);


    return true;
}

void PrintRawMap(int r, int c)
{
    cout<<" ";
    for(int i=0; i<C; i++)
        cout<<" "<<i;
    cout<<endl;
    for(int i=0; i<R; i++)
    {
        cout<<i<<" ";
        for(int j=0; j<C; j++)
        {
            if(i==r && j==c)
            {
                cout<<"X ";
                continue;
            }
            if(map[i][j].isMine)
                cout<<"* ";
            else
            {
                if(map[i][j].Neghbors>0)
                    cout<<map[i][j].Neghbors<<" ";
                else
                    cout<<"  ";
            }
        }
        cout<<endl;
    }
}

bool isWin()
{
    int count=0;
    for(int i=0; i<R; i++)
        for(int j=0; j<C; j++)
            if(!map[i][j].isOpen)
                count++;
    return count==N;
}

int main()
{
    int row, col;
    R=C=N=10;

    CreateMap(R, C, N);
    
    bool bWin = false;
    while(true)
    {
        PrintMap();
        cout<<">>";
        cin>>row>>col;

        if(row >= R || col >= C || row < 0 || col < 0)
        {
            continue;
        }

        if(!Click(row, col))
        {
            PrintRawMap(row, col);
            break;
        }
        if(isWin())
        {
            bWin = true;
            break;
        }
    }


    cout << (bWin ? "Win..." : "Lose...") << endl;

    return 0;
}
