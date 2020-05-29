#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
using namespace std;

const int width  = 40; 
const int height = 20; 
int level;          
int head_x, head_y;=
int food_x, food_y;
int direction = 0;
bool GameStatus;
int score;
int End_x[100], End_y[100];
int Size;

void Level()
{
    setlocale(0, "");
    cin >> level;

    switch(level)
        {
            case 1: Sleep(500);
                break;
            case 2: Sleep(350);
                break;
            case 3: Sleep(200);
                break;
            default: cout << "Вы неправильно ввели значение\n";
                break;
                }
}
void Start_Setting()
{
    GameStatus = true;
    direction = 0;
    head_x = width/4;
    head_y = height/4;
    srand(time(NULL));
    food_x = rand()%(width);
    food_y = rand()%(height);
    score = 0;
}

void Draw()
{
    system ("cls");
    for(int i=0; i<width+1; i++)
    cout <<"%";
    cout<< endl;

    for(int i=0; i<height; i++)
    {
       for(int j=0; j<width; j++)
       {
            if (j == 0 || j == width - 1)
            cout<<"%";


            if (i== head_y && j==head_x)
               cout <<'@';
            else
            if (i== food_y && j==food_x)
               cout <<'$';
            else
            {
            bool Queue = false;
            for (int k=0; k<Size; k++)
            {
                if(End_x[k] == j && End_y[k] == i )
                    {
                    Queue = true;
                    cout<<'*';
                    }
            }
            if (!Queue)
            cout <<" ";
        }
       }
        cout << endl;
    }

    for(int i=0; i<width + 1; i++)

        cout<< "%";
        cout << endl;

    cout << "Score: " << score << endl;
}
void Keyboard()
{
    if (_kbhit())
    {
        switch(_getch())
        {
    case 72 :
        if (direction != 3) direction =1;
        break;
    case 77:
        if (direction != 4) direction =2;
        break;
    case 80:
        if (direction != 1) direction =3;
        break;
    case 75:
        if (direction != 2) direction =4;
        break;
    case 27:
        GameStatus = false;
        break;
        }
    }
}

void Update_Field()
{
    int pred_X = End_x[0];// t-x предыдущий
    int pred_Y = End_y[0];
    int pred2_X, pred2_Y;
    End_x[0] = head_x; End_y[0] = head_y;
    for (int i = 1; i < Size; i++)
            {
                pred2_X = End_x[i];
                pred2_Y = End_y[i];
                End_x[i] = pred_X;
                End_y[i] = pred_Y;
                pred_X = pred2_X;
                pred_Y = pred2_Y;
            }
    switch(direction)
    {
    case 1:
        head_y--;
        break;
    case 2:
        head_x++;
        break;
    case 3:
        head_y++;
        break;
    case 4:
        head_x--;
        break;
    }
/* ЭТО ЕСЛИ МЫ ЗАХОТИМ СДЕЛАТЬ, ЧТОБЫ НАШЕ ПОЛЕ БЫЛО "БЕСКОНЕЧНЫМ"
    if (head_x >= width - 1)
    head_x = 0;
    else if (head_x < 0)
    head_x = width - 2;

    if (head_y >= height - 1)
    head_y = 0;
    else if (head_y < 0)
    head_y = height - 2;
*/
// Это если мы хотим усложнить задачу и сделать поле ограниченное
if (head_x>width || head_x <0 || head_y > height || head_y <0)
    GameStatus = false;

    if (head_x == food_x && head_y == food_y)
    {
        food_x = rand()%(width-1);
        food_y = rand()%(height-1);
        score +=10;
        Size++;
    }
    for (int i = 0; i < Size; i++)
    {
        if (End_x[i]==head_x && End_y[i]==head_y)
    GameStatus = false;
    }
}


int main()
{
    setlocale(0, "");
    cout <<"Выберите уровень сложности:"<<endl;
    cout <<"1 уровень - легкий"<<endl;
    cout <<"2 уровень - средний"<<endl;
    cout <<"3 уровень - сложный"<<endl;
    //cin >> level;
    Start_Setting();
    Level();
 //   if (!cin.fail())
        while(GameStatus)
        {
         cout <<"Чтобы играть, нужно нажимать на стрелочки на вашей клавиатуре\n";
         Draw();
         Keyboard();
         Update_Field();
        }
        cout << "Вы проиграли ((("<< endl;
 //   else
    return 0;
}
