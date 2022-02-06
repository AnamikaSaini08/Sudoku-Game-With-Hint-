#include<iostream>
#include<conio.h>
#include<bits/stdc++.h>

using namespace std;

int grid[9][9] =
{{3 ,0, 6, 5 ,0 ,8 ,4 ,0 ,0},
{5, 2, 0 ,0 ,0 ,0 ,0 ,0 ,0},
{0 ,8 ,7, 0 ,0 ,0 ,0 ,3 ,1},
{0 ,0 ,3 ,0 ,1 ,0 ,0 ,8 ,0},
{9, 0, 0, 8, 6 ,3 ,0, 0, 5},
{0 ,5 ,0 ,0, 9 ,0 ,6 ,0 ,0},
{1 ,3, 0, 0 ,0 ,0 ,2 ,5 ,0},
{0, 0, 0, 0, 0 ,0 ,0 ,7 ,4},
{0 ,0 ,5 ,2 ,0 ,6 ,3 ,0 ,0}};
int result[9][9] =
{{3 ,0, 6, 5 ,0 ,8 ,4 ,0 ,0},
{5, 2, 0 ,0 ,0 ,0 ,0 ,0 ,0},
{0 ,8 ,7, 0 ,0 ,0 ,0 ,3 ,1},
{0 ,0 ,3 ,0 ,1 ,0 ,0 ,8 ,0},
{9, 0, 0, 8, 6 ,3 ,0, 0, 5},
{0 ,5 ,0 ,0, 9 ,0 ,6 ,0 ,0},
{1 ,3, 0, 0 ,0 ,0 ,2 ,5 ,0},
{0, 0, 0, 0, 0 ,0 ,0 ,7 ,4},
{0 ,0 ,5 ,2 ,0 ,6 ,3 ,0 ,0}};

void screenShow();
void mapping_vertex(vector<vector<int> >&);
void enterChoice(vector<vector<int> >&record , int&win);
void gameLevel();
void erasing(int x , int y,vector<vector<int> >& , int&);
void printSuduko();
inline int hint(int , int );
bool isSafe(int, int, int);
void solution();

void mapping_vertex(vector<vector<int> >&record)
{
    for(int i=0 ; i<9 ; i++)
    {
        for(int j=0 ; j<9 ; j++)
        {
            if(grid[i][j])
            {
                vector<int>temp;
                temp.push_back(i);
                temp.push_back(j);
                record.push_back(temp);
            }
        }
    }
}
void erasing(int x , int y , vector<vector<int> >&record, int &win)
{
    for(int i=0 ; i<record.size() ; i++)
    {
        if(record[i][0]==x && record[i][1]==y)
        {
            cout<<"This can not be erased";
            getch();
            return;
        }
    }
    grid[x][y] = 0;
    win+=1;
}

void printSuduko()
{
    cout<<"       ";
    for(int i=0 ; i<9 ; i++)
    {
        cout<<i<<"     ";
    }
    cout<<endl<<endl;
    for(int i=0 ; i<9 ; i+=1)
    {
        cout<<i<<"      ";
        for(int j=0 ; j<9 ; j+=1)
        {
            if(grid[i][j]==0)
            {
                cout<<"_"<<"     ";
            }
            else
            {
                cout<<grid[i][j]<<"     ";
            }
        }
        cout<<endl<<endl;
    }
}


int hint(int row , int col)
{
    return result[row][col];
}

void enterChoice(vector<vector<int> >&record , int &win)
{
   int choice , chance=3;
   int row , col , n;

   while(1)
   {
       cout<<"\033[2J\033[1;1H";
       printSuduko();

       if(win==0)
       {
           cout<<"You won the game"<<endl;
           getch();
           exit(0);
       }
       cout<<"1:  Hint"<<endl;
       cout<<"2:  Enter co-ordinate(x,y) in which number want to enter"<<endl;
       cout<<"3:  Erase"<<endl;
       cout<<"4:  Exit"<<endl;


       cout<<"Enter choice:  "<<endl;
       cin>>choice;

       switch(choice)
       {
       case 1:
              cout<<"Enter co-ordinate(x,y):  "<<endl;
              cin>>row>>col;
              cout<<hint(row , col)<<endl;
              getch();
              break;
       case 2:
           cout<<"Enter co-ordinate(x,y)"<<endl;
           cin>>row>>col;
           cout<<"Enter number: "<<endl;
           cin>>n;
           if(isSafe(row, col , n))
           {
               win--;
               grid[row][col] = n;
               cin.get();
           }
           else{
            cout<<"Wrong number ";
            chance--;
            if(chance==0)
            {
                cout<<"You lose the game :( "<<endl;
                cout<<"Press any key to exit "<<endl;
                cin.get();
                return;
            }
            else{
                cout<<chance<<" chance left"<<endl;
                getch();
            }
           }
           break;

       case 3:
                cout<<"Enter co-ordinate(x,y) which want to delete"<<endl;
                cin>>row>>col;
                erasing(row,col,record,win);
                getch();
                break;
       case 4:
                cout<<"Thankyou"<<endl;
                cin.get();
                exit(0);

       }
   }
}

bool isSafe_result(int row , int col , int k)
{
    //VERTICAL

    for(int i=0 ; i<9 ; i++)
    {
        if(result[i][col] == k)
            return false;
    }

    //HORIZONTAL

    for(int i=0 ; i<9 ; i++)
    {
        if(result[row][i] == k)
            return false;
    }

    //3*3 MATRIX
    int rs,re,cs,ce;

    for(int i=0 ; i<9 ; i+=3)
    {
        if(row>=i && row<i+3)
        {
            rs = i;
            re = i+2;
        }
    }
    for(int i=0 ; i<9 ; i+=3)
    {
        if(col>=i && col<i+3)
        {
            cs = i;
            ce = i+2;
        }
    }

    for(int i=rs ; i<=re ; i++)
    {
        for(int j=cs ; j<=ce ; j++)
        {
            if(result[i][j] == k)
                return false;
        }
    }
    return true;
}

bool isSafe(int row , int col , int k)
{
    //VERTICAL

    for(int i=0 ; i<9 ; i++)
    {
        if(grid[i][col] == k)
            return false;
    }

    //HORIZONTAL

    for(int i=0 ; i<9 ; i++)
    {
        if(grid[row][i] == k)
            return false;
    }

    //3*3 MATRIX
    int rs,re,cs,ce;

    for(int i=0 ; i<9 ; i+=3)
    {
        if(row>=i && row<i+3)
        {
            rs = i;
            re = i+2;
        }
    }
    for(int i=0 ; i<9 ; i+=3)
    {
        if(col>=i && col<i+3)
        {
            cs = i;
            ce = i+2;
        }
    }

    for(int i=rs ; i<=re ; i++)
    {
        for(int j=cs ; j<=ce ; j++)
        {
            if(grid[i][j] == k)
                return false;
        }
    }
    return true;
}

bool solution(int row , int col)
{
    if(row==9)
        return true;

    //FILLED
    if(result[row][col]!=0)
    {
        if(col==8)
            return solution(row+1 , 0);
        else
            return solution(row , col+1);
    }

    //NOT FILLED
    for(int k=1; k<=9 ; k++)
    {
        if(isSafe_result(row , col , k))
        {
            result[row][col] = k;

            if(col==8)
            {
                if(solution(row+1 , 0))
                    return true;
            }

            else{
                if(solution(row , col+1))
                    return true;
            }

        }
        result[row][col] = 0;
    }
    return false;
}



void screenShow()
{
    cout<<"1:  Game Rule"<<endl;
    cout<<"2:  Play Game"<<endl;
    cout<<"3:  Exit"<<endl;
    cout<<"\n\n Enter your choice:  "<<endl;

    int choice;
    cin>>choice;

    switch(choice)
    {
    case 1:
        break;

    case 2:
        system("cls");
        break;
    case 3:
        exit(0);

    }
}
int main()
{
   vector<vector<int> >record;
   mapping_vertex(record);

   int win = 81 - record.size();

   solution(0,0);
   screenShow();
   enterChoice(record , win);
   screenShow();
}