#include <iostream>
#include <windows.h>
#include <time.h>
#include <vector>
#define Enemies_size 24
using namespace std;

char levels;
int shield;
int hours = 0, minutes = 0, seconds = 0;
char PacMapEasy[20][100];
char mapEasy[20][100] = {
    "###################################################################################################",
    "| ............................................................................................... |",
    "|  ...............................................................................................|",
    "|...###....###########....##   ######### ... ################.........#################...........|",
    "| ............................................................................................... |",
    "|#####.......###################..........#############.........#################......#####..... |",
    "| ..............................................................................................  |",
    "| ..... # ....... ################################# ...... #....#############.....################|",
    "| ..... # ......  # ............................. # ...... # ...........#.............#...........|",
    "|.......# .................................................#............#.............#...........|",
    "|.......# .............################### ................#............#.............#...........|",
    "|.......#..................................................# ...........#.............#...........|",
    "|.......# ........#...............................#........#............#.............#...........|",
    "|.......#.........#################################.....................#.............#...........|",
    "|.................................................................................................|",
    "|.................................................................................................|",
    "| ...###....###########....##....#########......################.......###############............|",
    "|.................................................................................................|",
    "|.................................................................................................|",
    "###################################################################################################"};

char PacMapNormal[20][70];
char mapNormal[20][70] = {
    "#####################################################################",
    "| ................................................................. |",
    "|  .................................................................|",
    "|...###....###########....##   ######### ... ################.......|",
    "| ................................................................. |",
    "|#####.......###################..........#############.........### |",
    "| ................................................................. |",
    "| ..... # ....... #################################........#........|",
    "| ..... # ......  # ............................. # ...... # .......|",
    "|.......# .................................................#........|",
    "|.......# .............################### ................#........|",
    "|.......#..................................................# .......|",
    "|.......# ........#...............................#........#........|",
    "|.......#.........#################################.................|",
    "|...................................................................|",
    "|...................................................................|",
    "| ...###....###########....##....#########......################....|",
    "|...................................................................|",
    "|...................................................................|",
    "#####################################################################"};

char PacMapHard[20][50];
char mapHard[20][50] = {
    "#################################################",
    "| ..............................................|",
    "|  .............................................|",
    "|...###....###########....##   ######### ... ###|",
    "| ..............................................|",
    "|#####.......###################..........######|",
    "| ..............................................|",
    "| ..... # ..... ####################......#.....|",
    "| ..... # ....  # .................#......#.....|",
    "|.......# ................................#.....|",
    "|.......# ...........######## ............#.....|",
    "|.......#.................................#.....|",
    "|.......# ......#..................#......#.....|",
    "|.......#.......####################......#.....|",
    "|...............................................|",
    "|...............................................|",
    "| ...###....###########....##....#########......|",
    "|...............................................|",
    "|...............................................|",
    "#################################################"};

void timeCalculate()
{
     cout << "Time : " << hours << " : " << minutes << " : " << seconds;
     Beep(500, 200);
     seconds++;
     if (seconds == 60)
     {
          seconds = 0;
          minutes++;
          if (minutes == 60)
          {
               minutes = 0;
               hours++;
          }
     }
}
void ShowMapEasy()
{
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
     for (int i = 0; i < 20; i++)
     {
          cout << mapEasy[i] << endl;
     }
}

void ShowMapNormal()
{
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
     for (int i = 0; i < 20; i++)
     {
          cout << mapNormal[i] << endl;
     }
}

void ShowMapHard()
{
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
     for (int i = 0; i < 20; i++)
     {
          cout << mapHard[i] << endl;
     }
}
void gotoxy(int x, int y)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {(SHORT)x, (SHORT)y}; // Cast to SHORT
    SetConsoleCursorPosition(hStdout, position);
}

struct Object//entity
{
     int x;
     int y;
};

struct Movement//walk
{
     int walk_Movement;
     int x;
     int y;
     int back;
};

struct Target
{
     int x;
     int y;
};

struct Enemy
{
     int ex;
     int ey;
     char name;
     vector<Target> enemyPath;
     vector<Movement> PathArray;
};

vector<Enemy> enemies;

void AddObjectEasy(int x, int y, int wc, int back, int index)
{
     if (PacMapEasy[y][x] == ' ' || PacMapEasy[y][x] == '.')
     {
          PacMapEasy[y][x] = '#';
          Movement temp;
          temp.x = x;
          temp.y = y;
          temp.walk_Movement = wc;
          temp.back = back;
          enemies[index].PathArray.push_back(temp);
     }
}

void AddObjectNormal(int x, int y, int wc, int back, int index)
{
     if (PacMapNormal[y][x] == ' ' || PacMapNormal[y][x] == '.')
     {
          PacMapNormal[y][x] = '#';
          Movement temp;
          temp.x = x;
          temp.y = y;
          temp.walk_Movement = wc;
          temp.back = back;
          enemies[index].PathArray.push_back(temp);
     }
}

void AddObjectHard(int x, int y, int wc, int back, int index)
{
     if (PacMapHard[y][x] == ' ' || PacMapHard[y][x] == '.')
     {
          PacMapHard[y][x] = '#';
          Movement temp;
          temp.x = x;
          temp.y = y;
          temp.walk_Movement = wc;
          temp.back = back;
          enemies[index].PathArray.push_back(temp);
     }
}

void FindPathEasy(int index, int x, int y)
{
     memcpy(PacMapEasy, mapEasy, sizeof(mapEasy));
     enemies[index].PathArray.clear();
     Movement temp;
     temp.x = enemies[index].ex;
     temp.y = enemies[index].ey;
     temp.walk_Movement = 0;
     temp.back = -1;

     enemies[index].PathArray.push_back(temp);
     int i = 0;
     while (i < enemies[index].PathArray.size())
     {
          if (enemies[index].PathArray[i].x == x && enemies[index].PathArray[i].y == y)
          {
               enemies[index].enemyPath.clear();
               Target temp2;
               while (enemies[index].PathArray[i].walk_Movement != 0)
               {
                    temp2.x = enemies[index].PathArray[i].x;
                    temp2.y = enemies[index].PathArray[i].y;
                    enemies[index].enemyPath.push_back(temp2);

                    i = enemies[index].PathArray[i].back;
               }

               break;
          }
          AddObjectEasy(enemies[index].PathArray[i].x + 1, enemies[index].PathArray[i].y, enemies[index].PathArray[i].walk_Movement + 1, i, index);
          AddObjectEasy(enemies[index].PathArray[i].x - 1, enemies[index].PathArray[i].y, enemies[index].PathArray[i].walk_Movement + 1, i, index);
          AddObjectEasy(enemies[index].PathArray[i].x, enemies[index].PathArray[i].y + 1, enemies[index].PathArray[i].walk_Movement + 1, i, index);
          AddObjectEasy(enemies[index].PathArray[i].x, enemies[index].PathArray[i].y - 1, enemies[index].PathArray[i].walk_Movement + 1, i, index);

          i++;
     }

     enemies[index].PathArray.clear();
}

void FindPathNormal(int index, int x, int y)
{
     memcpy(PacMapNormal, mapNormal, sizeof(mapNormal));
     enemies[index].PathArray.clear();
     Movement temp;
     temp.x = enemies[index].ex;
     temp.y = enemies[index].ey;
     temp.walk_Movement = 0;
     temp.back = -1;

     enemies[index].PathArray.push_back(temp);
     int i = 0;

     while (i < enemies[index].PathArray.size())
     {
          if (enemies[index].PathArray[i].x == x && enemies[index].PathArray[i].y == y)
          {
               enemies[index].enemyPath.clear();
               Target temp2;
               while (enemies[index].PathArray[i].walk_Movement != 0)
               {
                    temp2.x = enemies[index].PathArray[i].x;
                    temp2.y = enemies[index].PathArray[i].y;
                    enemies[index].enemyPath.push_back(temp2);

                    i = enemies[index].PathArray[i].back;
               }

               break;
          }
          AddObjectNormal(enemies[index].PathArray[i].x + 1, enemies[index].PathArray[i].y, enemies[index].PathArray[i].walk_Movement + 1, i, index);
          AddObjectNormal(enemies[index].PathArray[i].x - 1, enemies[index].PathArray[i].y, enemies[index].PathArray[i].walk_Movement + 1, i, index);
          AddObjectNormal(enemies[index].PathArray[i].x, enemies[index].PathArray[i].y + 1, enemies[index].PathArray[i].walk_Movement + 1, i, index);
          AddObjectNormal(enemies[index].PathArray[i].x, enemies[index].PathArray[i].y - 1, enemies[index].PathArray[i].walk_Movement + 1, i, index);

          i++;
     }

     enemies[index].PathArray.clear();
}

void FindPathHard(int index, int x, int y)
{
     memcpy(PacMapHard, mapHard, sizeof(mapHard));
     enemies[index].PathArray.clear();
     Movement temp;
     temp.x = enemies[index].ex;
     temp.y = enemies[index].ey;
     temp.walk_Movement = 0;
     temp.back = -1;

     enemies[index].PathArray.push_back(temp);
     int i = 0;
     while (i < enemies[index].PathArray.size())
     {
          if (enemies[index].PathArray[i].x == x && enemies[index].PathArray[i].y == y)
          {
               enemies[index].enemyPath.clear();
               Target temp2;
               while (enemies[index].PathArray[i].walk_Movement != 0)
               {
                    temp2.x = enemies[index].PathArray[i].x;
                    temp2.y = enemies[index].PathArray[i].y;
                    enemies[index].enemyPath.push_back(temp2);

                    i = enemies[index].PathArray[i].back;
               }

               break;
          }
          AddObjectHard(enemies[index].PathArray[i].x + 1, enemies[index].PathArray[i].y, enemies[index].PathArray[i].walk_Movement + 1, i, index);
          AddObjectHard(enemies[index].PathArray[i].x - 1, enemies[index].PathArray[i].y, enemies[index].PathArray[i].walk_Movement + 1, i, index);
          AddObjectHard(enemies[index].PathArray[i].x, enemies[index].PathArray[i].y + 1, enemies[index].PathArray[i].walk_Movement + 1, i, index);
          AddObjectHard(enemies[index].PathArray[i].x, enemies[index].PathArray[i].y - 1, enemies[index].PathArray[i].walk_Movement + 1, i, index);

          i++;
     }

     enemies[index].PathArray.clear();
}
void ShieldForEnemy(int x,int y)
{
    int placex,placey;

    if(levels=='e'||levels=='E'){
            if(PacMapEasy[y][x]!='#'||PacMapEasy[y][x]!='|')
    {
    placex=1+rand()%98;
    placey=1+rand()%18;
    gotoxy(placex,placey);
    cout<<"@";
    }

    if(mapEasy[x][y]==placex && mapEasy[x][y]==placey)
    {
        shield++;
    }
    gotoxy(101,7);
    cout<<"Shields : "<<shield;

    }
}

int main()
{
     srand(time(NULL));
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

     bool running = true;
     int Prev_x;
     int Prev_y;
     int x = 14;
     int y = 15;
     int score = 0;

     static CONSOLE_FONT_INFOEX Font;
     HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
     GetCurrentConsoleFontEx(output, 0, &Font);
     Font.cbSize = sizeof(Font);
     Font.nFont = 25;
     Font.dwFontSize.X = 10;
     Font.dwFontSize.Y = 25;
     Font.FontFamily = FF_ROMAN;
     Font.FontWeight = FW_BOLD;
     SetCurrentConsoleFontEx(output, FALSE, &Font);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);

     gotoxy(25, 3);
     cout << "WELCOME TO PAC_MAN GAME" << endl
          << endl;
     cout << "Instructions :\n\t\t1. Arrow Keys to move your hero\n\t\t2. Eat the dots gain points\n\t\t3. Don't get caught by the Eater\n\n";
     cout << "Select Level :" << endl;
     cout << "\t\tH -> Hard\n\t\tN -> Normal\n\t\tE -> Easy\n\nYour Level : ";
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

     int SpeedLevel;
     cin >> levels;

     if (levels == 'E' || levels == 'e')
     {
          SpeedLevel = 3;
          for (int totalEnemies = 0; totalEnemies < 3; totalEnemies++)
          {
               Enemy tmpEnemy;
               tmpEnemy.name = 'A'+totalEnemies;
               tmpEnemy.ex = 1 + rand() % 96;
               tmpEnemy.ey = 1 + rand() % 17;

               enemies.push_back(tmpEnemy);
          }
          system("cls");

          ShowMapEasy();

          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

         // gotoxy(x, y);
         // cout<< "P";
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
          int counter = 0;
ShieldForEnemy(x,y);
          while (running)
          {
               gotoxy(x, y);
               cout << " ";

               Prev_x = x;
               Prev_y = y;

               if (GetAsyncKeyState(VK_UP))
               {
                    if (mapEasy[y - 1][x] == '.')
                    {
                         y--;
                         score++;
                    }
                    else if (mapEasy[y - 1][x] == ' ')
                         y--;
               }

               else if (GetAsyncKeyState(VK_DOWN))
               {
                    if (mapEasy[y + 1][x] == '.')
                    {
                         y++;
                         score++;
                    }
                    else if (mapEasy[y + 1][x] == ' ')
                         y++;
               }

               else if (GetAsyncKeyState(VK_LEFT))
               {
                    if (mapEasy[y][x - 1] == '.')
                    {
                         x--;
                         score++;
                    }
                    else if (mapEasy[y][x - 1] == ' ')
                         x--;
               }

               else if (GetAsyncKeyState(VK_RIGHT))
               {
                    if (mapEasy[y][x + 1] == '.')
                    {
                         x++;
                         score++;
                    }
                    else if (mapEasy[y][x + 1] == ' ')
                         x++;
               }

               else if (GetAsyncKeyState(VK_ESCAPE))
               {
                    cout << endl
                         << endl
                         << endl;
                    exit(0);
               }

               int index = 0;
               while (index < enemies.size())
               {
                    if (Prev_x != x || Prev_y != y)
                    {
                         FindPathEasy(index, x, y);
                    }
                    index++;
               }


               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
               gotoxy(x, y);
               cout << "P";
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               index = 0;
               while (index < enemies.size())
               {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    //mapEasy[enemies[index].ey][enemies[index].ex] ;
                    gotoxy(enemies[index].ex, enemies[index].ey);
                    cout << ".";
                    index++;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

               }

               index = 0;
               while (index < enemies.size())
               {
                    if (counter % SpeedLevel == 0 && enemies[index].enemyPath.size() != 0)
                    {
                         enemies[index].ex = enemies[index].enemyPath.back().x;
                         enemies[index].ey = enemies[index].enemyPath.back().y;
                         enemies[index].enemyPath.pop_back();
                    }
                    index++;
               }

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

               index = 0;
               while (index < enemies.size())
               {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);

                    gotoxy(enemies[index].ex, enemies[index].ey);
                    cout << enemies[index].name;
                    index++;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               }
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

               index = 0;
               while (index < enemies.size())
               {
                    if (enemies[index].ex == x && enemies[index].ey == y)
                    {
                         running = false;
                         break;
                    }
                    index++;
               }


               gotoxy(101, 1);
               cout << "Your Level: Easy ";
               gotoxy(101, 3);
               cout << "Your Score: " << score;
               gotoxy(101, 5);
               timeCalculate();

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

               counter++;
          }


     }

     else if (levels == 'N' || levels == 'n')
     {

          for (int totalEnemies = 0; totalEnemies < 4; totalEnemies++)
          {
               Enemy tempEnemy;
               tempEnemy.name = 'A' + totalEnemies;
               tempEnemy.ex = 1 + rand() % 66;
               tempEnemy.ey = 1 + rand() % 18;

               enemies.push_back(tempEnemy);
          }

          SpeedLevel = 2;

          system("cls");
          ShowMapNormal();

          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

          gotoxy(x, y);
          cout << "P";
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
          int counter = 0;

          while (running)
          {
               gotoxy(x, y);
               cout << " ";

               Prev_x = x;
               Prev_y = y;

               if (GetAsyncKeyState(VK_UP))
               {
                    if (mapNormal[y - 1][x] == '.')
                    {
                         y--;
                         score++;
                    }
                    else if (mapNormal[y - 1][x] == ' ')
                         y--;
               }

               else if (GetAsyncKeyState(VK_DOWN))
               {
                    if (mapNormal[y + 1][x] == '.')
                    {
                         y++;
                         score++;
                    }
                    else if (mapNormal[y + 1][x] == ' ')
                         y++;
               }

               else if (GetAsyncKeyState(VK_LEFT))
               {
                    if (mapNormal[y][x - 1] == '.')
                    {
                         x--;
                         score++;
                    }
                    else if (mapNormal[y][x - 1] == ' ')
                         x--;
               }

               else if (GetAsyncKeyState(VK_RIGHT))
               {
                    if (mapNormal[y][x + 1] == '.')
                    {
                         x++;
                         score++;
                    }
                    else if (mapNormal[y][x + 1] == ' ')
                         x++;
               }

               else if (GetAsyncKeyState(VK_ESCAPE))
               {
                    cout << endl
                         << endl
                         << endl;
                    exit(0);
               }
               int index = 0;
               while (index < enemies.size())
               {
                    if (Prev_x != x || Prev_y != y)
                    {
                         FindPathNormal(index, x, y);
                    }
                    index++;
               }

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
               gotoxy(x, y);
               cout << "P";
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               index = 0;
               while (index < enemies.size())
               {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    mapNormal[enemies[index].ey][enemies[index].ex] = '.';
                    gotoxy(enemies[index].ex, enemies[index].ey);
                    cout << ".";
                    index++;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               }

               index = 0;
               while (index < enemies.size())
               {
                    if (counter % SpeedLevel == 0 && enemies[index].enemyPath.size() != 0)
                    {
                         enemies[index].ex = enemies[index].enemyPath.back().x;
                         enemies[index].ey = enemies[index].enemyPath.back().y;
                         enemies[index].enemyPath.pop_back();
                    }
                    index++;
               }

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

               index = 0;
               while (index < enemies.size())
               {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);

                    gotoxy(enemies[index].ex, enemies[index].ey);
                    cout << enemies[index].name;
                    index++;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               }

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

               index = 0;
               while (index < enemies.size())
               {
                    if (enemies[index].ex == x && enemies[index].ey == y)
                    {
                         running = false;
                         break;
                    }
                    index++;
               }
               gotoxy(81, 1);
               cout << "Your Level: Normal ";
               gotoxy(81, 3);
               cout << "Your Score: " << score;
               gotoxy(81, 5);
               timeCalculate();
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

               counter++;
          }
     }

     else if (levels == 'H' || levels == 'h')
     {

          SpeedLevel = 1;

          system("cls");
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

          for (int totalEnemies = 0; totalEnemies < 5; totalEnemies++)
          {
               Enemy tempEnemy;
               tempEnemy.name = 'A' + totalEnemies;
               tempEnemy.ex = 1 + rand() % 46;
               tempEnemy.ey = 1 + rand() % 17;

               enemies.push_back(tempEnemy);
          }
          system("cls");

          ShowMapHard();

          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

          gotoxy(x, y);
          cout << "P";
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
          int counter = 0;

          while (running)
          {
               gotoxy(x, y);
               cout << " ";

               Prev_x = x;
               Prev_y = y;

               if (GetAsyncKeyState(VK_UP))
               {
                    if (mapHard[y - 1][x] == '.')
                    {
                         y--;
                         score++;
                    }
                    else if (mapHard[y - 1][x] == ' ')
                         y--;
               }

               else if (GetAsyncKeyState(VK_DOWN))
               {
                    if (mapHard[y + 1][x] == '.')
                    {
                         y++;
                         score++;
                    }
                    else if (mapHard[y + 1][x] == ' ')
                         y++;
               }

               else if (GetAsyncKeyState(VK_LEFT))
               {
                    if (mapHard[y][x - 1] == '.')
                    {
                         x--;
                         score++;
                    }
                    else if (mapHard[y][x - 1] == ' ')
                         x--;
               }

               else if (GetAsyncKeyState(VK_RIGHT))
               {
                    if (mapHard[y][x + 1] == '.')
                    {
                         x++;
                         score++;
                    }
                    else if (mapHard[y][x + 1] == ' ')
                         x++;
               }

               else if (GetAsyncKeyState(VK_ESCAPE))
               {
                    cout << endl
                         << endl
                         << endl;
                    exit(0);
               }
               int index = 0;
               while (index < enemies.size())
               {
                    if (Prev_x != x || Prev_y != y)
                    {
                         FindPathHard(index, x, y);
                    }
                    index++;
               }

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
               gotoxy(x, y);
               cout << "P";
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               index = 0;
               while (index < enemies.size())
               {

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);

                    mapHard[enemies[index].ey][enemies[index].ex] = '.';
                    gotoxy(enemies[index].ex, enemies[index].ey);
                    cout << ".";
                    index++;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               }
               index = 0;
               while (index < enemies.size())
               {
                    if (counter % SpeedLevel == 0 && enemies[index].enemyPath.size() != 0)
                    {
                         enemies[index].ex = enemies[index].enemyPath.back().x;
                         enemies[index].ey = enemies[index].enemyPath.back().y;
                         enemies[index].enemyPath.pop_back();
                    }
                    index++;
               }

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

               index = 0;
               while (index < enemies.size())
               {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);

                    gotoxy(enemies[index].ex, enemies[index].ey);
                    cout << enemies[index].name;
                    index++;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               }

               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

               index = 0;
               while (index < enemies.size())
               {
                    if (enemies[index].ex == x && enemies[index].ey == y)
                    {
                         running = false;
                         break;
                    }
                    index++;
               }
               gotoxy(61, 1);
               cout << "Your Level: Easy ";
               gotoxy(61, 3);
               cout << "Your Score: " << score;
               gotoxy(61, 5);
               timeCalculate();
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

               counter++;
          }
     }

     else
     {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
          cout << " \n\n\tEnter correct Input !!!!";
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
          exit(0);
     }

     system("cls");
     gotoxy(15, 5);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
     cout << "You Lose!!!!!\n\t\t\t Your Score is : " << score << "\n\t\t\t Your Level : " << levels << endl
          << endl;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

     cin.get();

     return 0;

} // end main function
