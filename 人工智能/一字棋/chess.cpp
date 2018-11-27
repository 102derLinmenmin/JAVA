#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> P;

const int MAXN = 5;
const int INF = 0x3f3f3f3f;

char maze[MAXN][MAXN];

void initMaze();                    // ��ʼ������
void printMaze();                   // ������ǰ����
int checkWin(char x);               // ����Ƿ�Ӯ��
int myTurn();                       // ʹ��������
int aiTurn();                       // ����������
P findBest(int depth, int result);  // �ҵ�������ӵ�
int calculate();                    // ���� e(p)

int main()
{
    initMaze();
    printf("������û������������·����룺0  \n ");
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
    if( isOver == 1 ) puts("��ϲ�㣬���ʤ��~");
    else if( isOver == 2 ) puts("���ó��ϣ����ǵĻ�����ʤ����~");
    else puts("������ǻ�����һ������Ӵ~");
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
    puts("Ŀǰ�������:\n");
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
    puts("��������Ҫ���õ�λ�ã���������ڵ�һ�е�һ��λ�������룺0 0");
    int x, y;
    scanf("%d %d", &x, &y);
    while( maze[x][y] != ' ' ) {
        printf("��ѽ�����λ���Ѿ����Ź���,����һ�Σ�\n");
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
    puts("���ܻ������º�����\n");
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
