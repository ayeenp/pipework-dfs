
#include <stdio.h>
#include <stdbool.h>

// you saw nothing!
void resetVisited(int n, bool visited[n][n]);

// translate type of cell to int
int translateToInt(char);

// check if two squares are connected or not
bool isConnected(int n, int table[n][n][3], int, int, int, int);

// check if we have electricity in this square or not
bool isElectric(int n, int table[n][n][3], bool visited[n][n], int, int);

// printing solution
void printRotationTable(int n, int table[n][n][3]);

// backtrack to find solution
bool solution(int n, int table[n][n][3], bool visited[n][n], int, int);

// input the table
void input(int n, int table[n][n][3], bool visited[n][n], int *);

int main()
{
    int n, computersCount = 0;
    scanf("%d", &n);
    int table[n][n][3];
    bool visited[n][n];
    input(n, table, visited, &computersCount);
    printf("out%d", computersCount);
    bool end = solution(n, table, visited, 0, 0);
    return 0;
}

bool solution(int n, int table[n][n][3], bool visited[n][n], int i, int j)
{
    static long long callCount = 0;
    int check = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            resetVisited(n, visited);
            if (isElectric(n, table, visited, i, j))
            {
                check++;
            }
        }
    }
    if (check == n * n)
    {
        return true;
    }

    for (int z = 0; z < 4; z++)
    {
        printf("%d %d %d\n", i, j, z);
        printRotationTable(n, table);
        printf("%lld", callCount);
        callCount++;
        printf("\n");
        if (i != n - 1)
        {
            if (solution(n, table, visited, i + 1, j) == true)
            {
                printRotationTable(n, table);
                break;
            }
        }
        else if (j != n - 1)
        {
            if (solution(n, table, visited, 0, j + 1) == true)
            {
                printRotationTable(n, table);
                break;
            }
        }
        table[i][j][1] += 1;
        table[i][j][1] %= 4;
    }

    return false;
}

bool isElectric(int n, int table[n][n][3], bool visited[n][n], int i, int j)
{
    if ((i == n / 2 && j == n / 2))
    {

        return true;
    }
    visited[i][j] = true;
    if ((visited[(i + 1) % n][j]) == 0 && isConnected(n, table, (i + 1) % n, j, i, j))
    {
        if (isElectric(n, table, visited, (i + 1) % n, j))
            return true;
    }

    if ((visited[(i + n - 1) % n][j]) == 0 && isConnected(n, table, i, j, (i + n - 1) % n, j))
    {
        if (isElectric(n, table, visited, (i + n - 1) % n, j))
            return true;
    }

    if ((visited[i][(j + 1) % n]) == 0 && isConnected(n, table, i, j, i, (j + 1) % n))
    {
        if (isElectric(n, table, visited, i, (j + 1) % n))
            return true;
    }

    if ((visited[i][(j + n - 1) % n]) == 0 && isConnected(n, table, i, (j + n - 1) % n, i, j))
    {
        if (isElectric(n, table, visited, i, (j + n - 1) % n))
            return true;
    }

    return false;
}

bool isConnected(int n, int table[n][n][3], int x1, int y1, int x2, int y2)
{
    // when they are in a column :
    if (y1 == y2)
    {
        if ((table[x1][y1][0] == 1 && table[x1][y1][1] == 0) || (table[x1][y1][0] == 4 && table[x1][y1][1] % 2 == 0))
        {
            if (table[x2][y2][0] == 1 && table[x2][y2][1] == 2 && table[x1][y1][0] != 1)
                return true;
            if (table[x2][y2][0] == 2 && (table[x2][y2][1] == 1 || table[x2][y2][1] == 2))
                return true;
            if ((table[x2][y2][0] == 0 || table[x2][y2][0] == 3) && table[x2][y2][1] != 2)
                return true;
            if (table[x2][y2][0] == 4 && table[x2][y2][1] % 2 == 0)
                return true;
        }
        else
        {
            if (table[x1][y1][0] == 2 && (table[x1][y1][1] == 0 || table[x1][y1][1] == 3))
            {
                if (table[x2][y2][0] == 1 && table[x2][y2][1] == 2 && table[x1][y1][0] != 1)
                    return true;
                if (table[x2][y2][0] == 2 && (table[x2][y2][1] == 1 || table[x2][y2][1] == 2))
                    return true;
                if ((table[x2][y2][0] == 0 || table[x2][y2][0] == 3) && table[x2][y2][1] != 2)
                    return true;
                if (table[x2][y2][0] == 4 && table[x2][y2][1] % 2 == 0)
                    return true;
            }
            else
            {
                if ((table[x1][y1][0] == 0 || table[x1][y1][0] == 3) && table[x1][y1][1] != 0)
                {
                    if (table[x2][y2][0] == 1 && table[x2][y2][1] == 2 && table[x1][y1][0] != 1)
                        return true;
                    if (table[x2][y2][0] == 2 && (table[x2][y2][1] == 1 || table[x2][y2][1] == 2))
                        return true;
                    if ((table[x2][y2][0] == 0 || table[x2][y2][0] == 3) && table[x2][y2][1] != 2)
                        return true;
                    if (table[x2][y2][0] == 4 && table[x2][y2][1] % 2 == 0)
                        return true;
                }
            }
        }
    }
    else
    {
        // when they are in a row
        if ((table[x1][y1][0] == 1 && table[x1][y1][1] == 1) || (table[x1][y1][0] == 4 && table[x1][y1][1] % 2 == 1))
        {
            if (table[x2][y2][0] == 1 && table[x1][y1][0] != 1 && table[x2][y2][1] == 3)
                return true;
            if (table[x2][y2][0] == 2 && (table[x2][y2][1] == 2 || table[x2][y2][1] == 3))
                return true;
            if ((table[x2][y2][0] == 0 || table[x2][y2][0] == 3) && table[x2][y2][1] != 3)
                return true;
            if (table[x2][y2][0] == 4 && table[x2][y2][1] % 2 == 1)
                return true;
        }
        else
        {
            if (table[x1][y1][0] == 2 && (table[x1][y1][1] == 0 || table[x1][y1][1] == 1))
            {
                if (table[x2][y2][0] == 1 && table[x1][y1][0] != 1 && table[x2][y2][1] == 3)
                    return true;
                if (table[x2][y2][0] == 2 && (table[x2][y2][1] == 2 || table[x2][y2][1] == 3))
                    return true;
                if ((table[x2][y2][0] == 0 || table[x2][y2][0] == 3) && table[x2][y2][1] != 3)
                    return true;
                if (table[x2][y2][0] == 4 && table[x2][y2][1] % 2 == 1)
                    return true;
            }
            else
            {
                if ((table[x1][y1][0] == 0 || table[x1][y1][0] == 3) && table[x1][y1][1] != 1)
                {
                    if (table[x2][y2][0] == 1 && table[x1][y1][0] != 1 && table[x2][y2][1] == 3)
                        return true;
                    if (table[x2][y2][0] == 2 && (table[x2][y2][1] == 2 || table[x2][y2][1] == 3))
                        return true;
                    if ((table[x2][y2][0] == 0 || table[x2][y2][0] == 3) && table[x2][y2][1] != 3)
                        return true;
                    if (table[x2][y2][0] == 4 && table[x2][y2][1] % 2 == 1)
                        return true;
                }
            }
        }
    }
    return false;
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

void input(int n, int table[n][n][3], bool visited[n][n], int *computersCount)
{
    char cellType;
    // the first index is type of what it is :  S = 0 , C = 1 , L = 2 , T = 3 , I = 4
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf(" %c%d", &cellType, &table[i][j][1]);
            table[i][j][0] = translateToInt(cellType);
            if (table[i][j][0] == 1)
                *computersCount = *computersCount + 1;
            table[i][j][2] = table[i][j][1];
            visited[i][j] = false;
        }
    }
}

int translateToInt(char x)
{
    if (x == 'S')
    {
        return 0;
    }
    else
    {
        if (x == 'C')
        {
            return 1;
        }
        else
        {
            if (x == 'L')
            {
                return 2;
            }
            else
            {
                if (x == 'T')
                {
                    return 3;
                }
                else
                {
                    return 4;
                }
            }
        }
    }
}

void printRotationTable(int n, int table[n][n][3])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", (n + table[i][j][1] - table[i][j][2]) % n);
        }
        printf("\n");
    }
}
