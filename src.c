#include <stdio.h>
#include <stdbool.h>

int checkOrder[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void input(int n, int table[n][n][4], int table2[n][n][4], bool fixed[n][n]);
void rotate(int n, int table[n][n][4], int, int, int);
void getCharType(int n, int table[n][n][4], int, int, char);
bool checkCell(int n, int table[n][n][4], int, int);
bool solution(int n, int table[n][n][4], int table2[n][n][4], bool fixed[n][n], int, int);
void printTable(int n, int table[n][n][4], int table2[n][n][4]);
bool checkBranch(int n, int table[n][n][4], bool fixed[n][n], int, int);
void copyFixes(int n, bool fixed[n][n], bool lastfixed[n][n]);
bool backToServer(int n, int table[n][n][4], bool visited[n][n], int, int);
void resetVisited(int n, bool visited[n][n]);
bool isStraightWire(int n, int table[n][n][4], int, int);
bool isLastCell(int n, bool fixed[n][n]);

int main()
{
    int n;
    scanf("%d", &n);
    int table[n][n][4];
    int table2[n][n][4];
    bool fixed[n][n];
    input(n, table, table2, fixed);
    if (solution(n, table, table2, fixed, n / 2, n / 2))
        printTable(n, table, table2);
    else
        printf("WRONG");

    return 0;
}

bool solution(int n, int table[n][n][4], int table2[n][n][4], bool fixed[n][n], int i, int j)
{
    static int callCount = 0;
    //printf("Call:%d\t%d|%d\n", callCount++, i, j);
    //printTable(n, table, table2);
    fixed[i][j] = 1;
    bool isLast = isLastCell(n, fixed);
    int maxRotation = 4;
    if (isStraightWire(n, table, i, j))
        maxRotation = 2;
    for (int w = 0; w < maxRotation; w++)
    {
        if (checkBranch(n, table, fixed, i, j))
        {
            if(isLast)
                return true;
            bool fixed2[n][n];
            for (int k = 0; k < 4; k++)
            {
                int i2 = (n + i + checkOrder[k][0]) % n;
                int j2 = (n + j + checkOrder[k][1]) % n;
                if (fixed[i2][j2] == 0)
                {
                    copyFixes(n, fixed2, fixed);
                    if (solution(n, table, table2, fixed, i2, j2))
                        return true;
                    copyFixes(n, fixed, fixed2);
                    break;
                }
            }
        }
        //printf("Rotate:s %d %d\n", i, j);
        rotate(n, table, i, j, 1);
    }

    int isAns = 1;
    for (int z = 0; z < n; z++)
    {
        for (int y = 0; y < n; y++)
        {
            if (!checkCell(n, table, z, y))
            {
                isAns = 0;
                break;
            }
        }
        if (isAns == 0)
            break;
    }
    if (isAns == 1)
    {
        printf("here");
        for (int z = 0; z < n; z++)
        {
            for (int y = 0; y < n; y++)
            {
                bool visited[n][n];
                resetVisited(n, visited);
                if (!backToServer(n, table, visited, z, y))
                {
                    isAns = 0;
                    break;
                }
            }
            if (isAns == 0)
                break;
        }
        if (isAns == 1)
            return true;
    }
    return false;
}

bool backToServer(int n, int table[n][n][4], bool visited[n][n], int i, int j)
{
    if ((i == n / 2) && (j == n / 2))
    {
        return true;
    }
    visited[i][j] = 1;
    if ((table[i][j][1] == 1 && table[i][(j + 1) % n][3] == 1) && visited[i][(j + 1) % n] == 0)
    {
        // bool visited2[n][n] ;
        // copyFixes( n , visited2 , visited) ;
        if (backToServer(n, table, visited, i, (j + 1) % n))
            return true;
    }
    if ((table[i][j][2] == 1 && table[(i + 1) % n][j][0] == 1) && visited[(i + 1) % n][j] == 0)
    {
        // bool visited2[n][n] ;
        // copyFixes( n , visited2 , visited) ;
        if (backToServer(n, table, visited, (i + 1) % n, j))
            return true;
    }
    if ((table[i][j][0] == 1 && table[(i + n - 1) % n][j][2] == 1) && visited[(i + n - 1) % n][j] == 0)
    {
        // bool visited2[n][n] ;
        // copyFixes( n , visited2 , visited) ;
        if (backToServer(n, table, visited, (i + n - 1) % n, j))
            return true;
    }
    if ((table[i][j][3] == 1 && table[i][(j + n - 1) % n][1] == 1) && visited[i][(j + n - 1) % n] == 0)
    {
        //          bool visited2[n][n] ;
        //            copyFixes( n , visited2 , visited) ;
        if (backToServer(n, table, visited, i, (j + n - 1) % n))
            return true;
    }
    return false;
}

bool checkBranch(int n, int table[n][n][4], bool fixed[n][n], int i, int j)
{
    int temp[4] = {2, 2, 2, 2};
    if (fixed[(i + n - 1) % n][j])
        temp[0] = table[(i + n - 1) % n][j][2];
    if (fixed[i][(j + 1) % n])
        temp[1] = table[i][(j + 1) % n][3];
    if (fixed[(i + 1) % n][j])
        temp[2] = table[(i + 1) % n][j][0];
    if (fixed[i][(j + n - 1) % n])
        temp[3] = table[i][(j + n - 1) % n][1];
    //  printf("%d : %d : %d : %d \n" , table[i][j][0] , temp[1] , temp[2] ,temp[3]) ;
    for (int k = 0; k < 4; k++)
    {
        if ((temp[0] == table[i][j][0] || temp[0] == 2) && (temp[1] == table[i][j][1] || temp[1] == 2))
        {
            if ((temp[2] == table[i][j][2] || temp[2] == 2) && (temp[3] == table[i][j][3] || temp[3] == 2))
            {
                return true;
            }
        }
    }
    return false;
}

void input(int n, int table[n][n][4], int table2[n][n][4], bool fixed[n][n])
{
    int firstRot;
    char celltype;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf(" %c%d", &celltype, &firstRot);
            getCharType(n, table, i, j, celltype);
            rotate(n, table, i, j, firstRot);
            for (int k = 0; k < 4; k++)
            {
                table2[i][j][k] = table[i][j][k];
            }
            fixed[i][j] = 0;
        }
    }
}

void printTable(int n, int table[n][n][4], int table2[n][n][4])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int check = 0;
                for (int z = 0; z < 4; z++)
                {
                    if (table[i][j][(z + k) % 4] == table2[i][j][z])
                        check++;
                }
                if (check == 4)
                {
                    if (j != n - 1)
                        printf("%d ", k);
                    else
                        printf("%d", k);
                    break;
                }
            }
        }
        printf("\n");
    }
}

bool checkCell(int n, int table[n][n][4], int i, int j)
{
    if (table[i][j][1] != table[i][(j + 1) % n][3])
        return false;
    if (table[i][j][2] != table[(i + 1) % n][j][0])
        return false;
    if (table[i][j][3] != table[i][(j + n - 1) % n][1])
        return false;
    if (table[i][j][0] != table[(i + n - 1) % n][j][2])
        return false;

    return true;
}

void rotate(int n, int table[n][n][4], int i, int j, int x)
{
    int fix[4];
    for (int z = 0; z < 4; z++)
    {
        fix[z] = table[i][j][z];
    }

    for (int z = 0; z < 4; z++)
    {
        table[i][j][(z + x) % 4] = fix[z];
    }
}

bool isLastCell(int n, bool fixed[n][n])
{
    int fixedCount = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fixed[i][j] == 1)
                fixedCount++;
        }
    }
    if (fixedCount == n * n)
        return true;
    return false;
}

bool isStraightWire(int n, int table[n][n][4], int i, int j)
{
    if (table[i][j][0] == table[i][j][2] && table[i][j][1] == table[i][j][3])
        return true;
    return false;
}

void getCharType(int n, int table[n][n][4], int i, int j, char type)
{
    if (type == 'S' || type == 'T')
    {
        table[i][j][0] = 0, table[i][j][1] = 1, table[i][j][2] = 1, table[i][j][3] = 1;
    }
    else
    {
        if (type == 'C')
        {
            table[i][j][0] = 1, table[i][j][1] = 0, table[i][j][2] = 0, table[i][j][3] = 0;
        }
        else
        {
            if (type == 'L')
            {
                table[i][j][0] = 1, table[i][j][1] = 1, table[i][j][2] = 0, table[i][j][3] = 0;
            }
            else
            {
                table[i][j][0] = 1, table[i][j][1] = 0, table[i][j][2] = 1, table[i][j][3] = 0;
            }
        }
    }
}

void copyFixes(int n, bool fixed[n][n], bool lastfixed[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fixed[i][j] = lastfixed[i][j];
        }
    }
}

void resetVisited(int n, bool visited[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
    }
}
