#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> P;

const int MAXN = 5;
const int INF = 0x3f3f3f3f;

char maze[MAXN][MAXN];

void initMaze();                    // 初始化数组
void printMaze();                   // 画出当前棋盘
int checkWin(char x);               // 检查是否赢了
int myTurn();                       // 使用者下棋
int aiTurn();                       // 机器人下棋
P findBest(int depth, int result);  // 找到最佳落子点
int calculate();                    // 计算 e(p)

int main()
{
    initMaze();
    printf("如果想让机器先走请在下方输入：0  \n ");
    int op;
    scanf("%d", &op);
    int isOver = 0;
    if( op ) {
        while( !isOver ) {
            isOver = myTurn();
            if( isOver ) break;
            system("cls");
            isOver = aiTurn();
        }
    }
    else {
        while( !isOver ) {
            isOver = aiTurn();
            if( isOver ) break;
            isOver = myTurn();
            system("cls");
        }
    }
    if( isOver == 1 ) puts("恭喜你，获得胜利~");
    else if( isOver == 2 ) puts("承让承认，我们的机器人胜利啦~");
    else puts("你和我们机器人一样聪明哟~");
    system("pause");
    return 0;
}

void initMaze()
{
    for( int i = 0; i < MAXN; ++ i ) {
        for( int j = 0; j < MAXN; ++ j ) {
            maze[i][j] = ' ';
        }
    }
}
void printMaze()
{
    puts("目前棋况如下:\n");
    for( int i = 0; i < MAXN; ++ i ) {
        for( int j = 0; j < MAXN; ++ j ) {
            if( j < 2 ) {
                printf("  %c%c |", maze[i][j], " \n"[j == MAXN - 1]);
            }
            else {
                printf("  %c%c", maze[i][j], " \n"[j == MAXN - 1]);
            }
        }
        if( i < 2 ) {
            printf(" ---------------\n");
        }
        puts("");
    }
}
int checkWin(char x)
{
    int diaL = 0, diaR = 0, equ = 0;
    for( int i = 0; i < MAXN; ++ i ) {
        int raw = 0, col = 0;
        for( int j = 0; j < MAXN; ++ j ) {
            if( maze[i][j] == x ) raw++;
            if( maze[j][i] == x ) col++;
            if( maze[i][j] == ' ' ) equ++;
        }
        if( maze[i][i] == x ) diaL++;
        if( maze[i][MAXN - i - 1] == x ) diaR++;
        if( raw == MAXN || col == MAXN || diaL == MAXN || diaR == MAXN ) return 1;
    }
    if( !equ ) return 2;
    return 0;
}
int myTurn()
{
    puts("输入你想要放置的位置，例如放置在第一行第一个位置则输入：0 0");
    int x, y;
    scanf("%d %d", &x, &y);
    while( maze[x][y] != ' ' ) {
        printf("啊呀，这个位置已经被放过啦,再试一次？\n");
        scanf("%d %d", &x, &y);
    }
    maze[x][y] = 'O';
    printMaze();
    int result = checkWin('O');
    if( result == 1 ) return 1;
    else if( result == 2 ) return 3;
    return 0;
}
int aiTurn()
{
    puts("智能机器人下好棋啦\n");
    pair<int, int> loc = findBest(3, -INF);
    maze[loc.second / MAXN][loc.second % MAXN] = 'X';
    printMaze();
    int result = checkWin('X');
    if( result == 1 ) return 2;
    else if( result == 2 ) return 3;
    return 0;
}
P findBest(int depth, int result)
{
    if( !depth ) return make_pair(calculate(), -1);
    if( depth & 1 ) {
        P Max = make_pair(-INF, -1);
        for( int i = 0; i < MAXN; ++ i ) {
            for( int j = 0; j < MAXN; ++ j ) {
                if( maze[i][j] == ' ' ) {
                    maze[i][j] = 'X';
                    if( calculate() == INF ) {
                        maze[i][j] = ' ';
                        return Max = make_pair(INF, i * MAXN + j);
                    }
                    else if( checkWin('X') == 2 ) {
                        maze[i][j] = ' ';
                        return Max = make_pair(0, i * MAXN + j);
                    }
                    P tmp = findBest(depth - 1, Max.first);
                    if( Max.first <= tmp.first ) {
                        Max = tmp;
                        Max.second = i * MAXN + j;
                    }
                    maze[i][j] = ' ';
                    if( depth == 1 && Max.first >= result ) return Max;
                }
            }
        }
        return Max;
    }
    else {
        P Min = make_pair(INF, -1);
        for( int i = 0; i < MAXN; ++ i ) {
            for( int j = 0; j < MAXN; ++ j ) {
                if( maze[i][j] == ' ' ) {
                    maze[i][j] = 'O';
                    if( calculate() == -INF ) {
                        maze[i][j] = ' ';
                        return Min = make_pair(-INF, i * MAXN + j);
                    }
                    else if( checkWin('O') == 2 ) {
                        maze[i][j] = ' ';
                        return Min = make_pair(0, i * MAXN + j);
                    }
                    P tmp = findBest(depth - 1, Min.first);
                    if( Min.first >= tmp.first ) {
                        Min = tmp;
                        Min.second = i * MAXN + j;
                    }
                    maze[i][j] = ' ';
                    if( result > Min.first ) return Min;
                }
            }
        }
        return Min;
    }
}
int calculate()
{
    if( checkWin('X') == 1 ) return INF;
    else if( checkWin('O') == 1 ) return -INF;
    int resX = 0, resO = 0;
    int diaLX = 0, diaRX = 0, diaLO = 0, diaRO = 0;
    for( int i = 0; i < MAXN; ++ i ) {
        int rawX = 0, colX = 0, rawO = 0, colO = 0;
        for( int j = 0; j < MAXN; ++ j ) {
            if( maze[i][j] == 'X' || maze[i][j] == ' ' ) rawX++;
            if( maze[j][i] == 'X' || maze[j][i] == ' ' ) colX++;
            if( maze[i][j] == 'O' || maze[i][j] == ' ' ) rawO++;
            if( maze[j][i] == 'O' || maze[j][i] == ' ' ) colO++;
        }
        if( maze[i][i] == 'X' || maze[i][i] == ' ' ) diaLX++;
        if( maze[i][MAXN - i - 1] == 'X' || maze[i][MAXN - i - 1] == ' ' ) diaRX++;
        resX += (rawX == MAXN) + (colX == MAXN);
        if( maze[i][i] == 'O' || maze[i][i] == '.' ) diaLO++;
        if( maze[i][MAXN - i - 1] == 'O' || maze[i][MAXN - i - 1] == ' ' ) diaRO++;
        resO += (rawO == MAXN) + (colO == MAXN);
    }
    resX += (diaLX == MAXN) + (diaRX == MAXN);
    resO += (diaLO == MAXN) + (diaRO == MAXN);
    return resX - resO;
}
