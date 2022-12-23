#include <stdio.h>
#include <stdbool.h>

int checkOrder[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void Rotation(int n, int table[n][n][4], int, int, int);
void getcharType(int n, int table[n][n][4], int, int, char);
bool Checkcell(int n, int table[n][n][4], int, int);
bool solution(int n, int table[n][n][4], int table2[n][n][4], bool fixed[n][n], int, int);
void printTable(int n, int table[n][n][4], int table2[n][n][4]);
bool checkBranch(int n, int table[n][n][4], bool fixed[n][n], int, int);
void Copyfixes(int n, bool fixed[n][n], bool lastfixed[n][n]);
bool BackToServer(int n, int table[n][n][4], bool visited[n][n], int, int , int , int );
void Resetvisited(int n, bool visited[n][n]);
bool isStraightWire(int n, int table[n][n][4], int, int);
bool isLastCell(int n, bool fixed[n][n]);
bool IsAns(int n , int table[n][n][4]  ) ;  
bool Iscomputer( int n , int table[n][n][4] , int  , int  );
bool Table_loop( int n , int table[n][n][4]) ;

int main()
{
    int n, FirstRot;
    char celltype;
    scanf("%d", &n);
    int table[n][n][4];
    int table2[n][n][4];
    bool fixed[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf(" %c%d", &celltype, &FirstRot);
            getcharType(n, table, i, j, celltype);
            Rotation(n, table, i, j, FirstRot);
            for (int k = 0; k < 4; k++)
            {
                table2[i][j][k] = table[i][j][k];
            }
            fixed[i][j] = 0;
        }
    }
    
    if (solution(n, table, table2, fixed, n / 2 , n / 2 ))
        printTable(n, table, table2);
    else
        printf("WRONG");
   //  printf("%d"  ,Table_loop( n , table) ) ; 
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
            if(isLast){
                if(IsAns( n, table)){
                   // printf("%d\n" , Table_loop( n, table)) ; 
                    if(Table_loop(n , table)) return false ; 
                    return true ;
                }
                return false;
            }
            bool fixed2[n][n];
            for (int k = 0; k < 4; k++)
            {
                int i2 = (n + i + checkOrder[k][0]) % n;
                int j2 = (n + j + checkOrder[k][1]) % n;
                if (fixed[i2][j2] == 0)
                {
                    Copyfixes(n, fixed2, fixed);
                    if (solution(n, table, table2, fixed, i2, j2))
                        return true;
                    Copyfixes(n, fixed, fixed2);
                    break;
                }
            }
        }
        //printf("Rotate:s %d %d\n", i, j);
        Rotation(n, table, i, j, 1);
    }
    
//    if(IsAns( n , table)){
        //printf("%d\n" , Table_loop( n , table)) ; 
      //  if(Table_loop( n, table)){
    //        return false ; 
    //    }else{
      //      return true ; 
    //    }
  //  }else{
    return false ;
//    }
}
bool BackToServer(int n, int table[n][n][4], bool visited[n][n], int i, int j , int x , int y ){
    if ((i == x ) && (j == y) )
    {
        return true;
    }
    visited[i][j] = 1;
    if ((table[i][j][1] == 1 && table[i][(j + 1) % n][3] == 1) && visited[i][(j + 1) % n] == 0)
    {
        // bool visited2[n][n] ;
        // Copyfixes( n , visited2 , visited) ;
        if (BackToServer(n, table, visited, i, (j + 1) % n , x , y))
            return true;
    }
    if ((table[i][j][2] == 1 && table[(i + 1) % n][j][0] == 1) && visited[(i + 1) % n][j] == 0)
    {
        // bool visited2[n][n] ;
        // Copyfixes( n , visited2 , visited) ;
        if (BackToServer(n, table, visited, (i + 1) % n, j , x , y))
            return true;
    }
    if ((table[i][j][0] == 1 && table[(i + n - 1) % n][j][2] == 1) && visited[(i + n - 1) % n][j] == 0)
    {
        // bool visited2[n][n] ;
        // Copyfixes( n , visited2 , visited) ;
        if (BackToServer(n, table, visited, (i + n - 1) % n, j , x ,y ))
            return true;
    }
    if ((table[i][j][3] == 1 && table[i][(j + n - 1) % n][1] == 1) && visited[i][(j + n - 1) % n] == 0)
    {
        //          bool visited2[n][n] ;
        //            Copyfixes( n , visited2 , visited) ;
        if (BackToServer(n, table, visited, i, (j + n - 1) % n , x , y))
            return true;
    }
    return false;
}

bool checkBranch(int n, int table[n][n][4], bool fixed[n][n], int i, int j){
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

bool IsAns(int n , int table[n][n][4]  ) { 
    int IsAns = 1;
     for (int z = 0; z < n; z++)
     {
        for (int y = 0; y < n; y++)
        {
            if (!Checkcell(n, table, z, y))
            {
                IsAns = 0;
                break;
            }
        }
        if (IsAns == 0)
            break;
     }
     if (IsAns == 1)
     {
        for (int z = 0; z < n; z++)
        {
            for (int y = 0; y < n; y++)
            {
                bool visited[n][n];
                Resetvisited(n, visited);
                if (!BackToServer(n, table, visited, z, y , n/2 , n/2))
                {
                    IsAns = 0;
                    break;
                }
            }
            if (IsAns == 0)
                break;
        }
        if (IsAns == 1)
            return true;
    }
    return false;
    
    
    
}

void printTable(int n, int table[n][n][4], int table2[n][n][4]){
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

bool Checkcell(int n, int table[n][n][4], int i, int j){
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

bool Table_loop( int n , int table[n][n][4]) { 
    
    for (int s = 0; s < n  ; s++) {
            for (int w = 0; w < n; w++) {
                         int lastcheck = 0 ; 
                for (int p = 0; p < n; p++) {
                    for (int q = 0; q < n; q++) {
                        if( Iscomputer(n , table , p , q) ){
                            bool visited[n][n] ; 
                            Resetvisited( n,  visited) ; 
                            if(BackToServer(n , table , visited ,  s , w , p , q)) lastcheck ++ ; 
                            if(lastcheck == 1 ) break ; 
                          }
                        }
                        if(lastcheck == 1 ) break ; 
                    }
                    if(lastcheck == 0 ) return true  ; 
                }
            }
      return false ; 
}

void Rotation(int n, int table[n][n][4], int i, int j, int x){
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

bool isLastCell(int n, bool fixed[n][n]){
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

bool isStraightWire(int n, int table[n][n][4], int i, int j){
    if (table[i][j][0] == table[i][j][2] && table[i][j][1] == table[i][j][3])
        return true;
    return false;
}

void getcharType(int n, int table[n][n][4], int i, int j, char type){
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

void Copyfixes(int n, bool fixed[n][n], bool lastfixed[n][n]){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fixed[i][j] = lastfixed[i][j];
        }
    }
}

void Resetvisited(int n, bool visited[n][n]){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
    }
}

bool Iscomputer( int n , int table[n][n][4] , int i , int j ) {
    int PCconnect = 0 ;
    for (int k = 0 ; k < 4 ; k++) {
        if(table[i][j][k]) PCconnect ++ ;
    }
    
    if(PCconnect == 1) return true ; 
    return false ; 
}
