#include <stdio.h>
#include <stdbool.h> 
int Q = 1 ; 
void Rotation(int n , int table[n][n][4] , int , int , int   ) ;  
void getcharType(int n , int table[n][n][4] , int , int , char) ; 
bool Checkcell( int n , int table[n][n][4] , int , int  ) ; 
void solution( int n , int table[n][n][4] , int table2[n][n][4] ,  int  , int) ; 
void printTable(int n , int table[n][n][4] , int table2[n][n][4]) ; 

int main(){
   int n  , FirstRot; 
   char celltype ; 
   scanf("%d" , &n) ; 
   int table[n][n][4] ; 
   int table2[n][n][4] ; 
   for (int i = 0; i < n; i++) { 
     for (int j = 0; j < n; j++){
        scanf(" %c%d" , &celltype , &FirstRot ) ; 
        getcharType( n , table , i , j , celltype) ; 
        Rotation( n , table , i , j , FirstRot) ; 
        for(int k = 0 ; k < 4 ; k ++ ){
            table2[i][j][k] = table[i][j][k] ; 
        }
     }
   }
 //  printTable( n , table ,table2) ; 
   solution(n , table , table2 , 0 , 0 ) ; 

    return 0   ; 
}

void solution (int n , int table[n][n][4] , int table2[n][n][4] , int i  , int j ) {
    if(Q == 1 ) {
    //    printf("%d : %d \n" , i , j ) ; 
      if( (i != n - 1) || (j != n - 1)) {
      //  printf("%d : %d \n" , i , j ) ; 
        for(int a = 0 ; a < 4 ; a ++  ){
       solution(n , table ,table2 , ((i+1)%n) , j + (i + 1)/n ) ; 
       Rotation( n , table , i , j , 1) ;
        }
      }else{
        for(int c = 0 ; c < 4 ; c++ ) {
      //      printf("%d : %d\n" , i , j) ; 
        int count  = 0 ; 
        for(int x = 0 ; x < n ; x ++){
            for( int y = 0 ; y < n ; y ++ ){
                if (Checkcell(n , table , x , y ) == 1 ){
                    count ++ ; 
                }
        }
      }
     // printf("%d\n" , count) ; 
      if( count == (n * n) ){
        printTable( n , table2 , table) ; 
        Q = 0 ; 
        break ;
      }
      Rotation(n , table , i , j , 1 ) ; 
    }
   }
  }
}

void printTable(int n , int table[n][n][4] , int table2[n][n][4]) {
    for(int i = 0 ; i < n ; i ++){
        for (int j = 0; j < n; j++){
            for(int k = 0 ; k  < 4 ; k ++) { 
                int check = 0 ;
                for(int z = 0 ;  z < 4 ; z++){
                    if(table[i][j][z] == table2[i][j][z]) check ++  ; 
                }
                if(check == 4 ) {
                    printf("%d " , k) ; 
                    break;
                }
                Rotation( n , table , i , j  , 1) ; 
            }
        }
        printf("\n") ;
        
    }
}


bool Checkcell( int n , int table[n][n][4] , int i  , int j  ) {
   if(table[i][j][1] != table[i][(j+1)%n][3]) return false ; 
   if(table[i][j][2] != table[(i+1)%n][j][0]) return false ; 
   if(table[i][j][3] != table[i][(j+n-1)%n][1]) return false ; 
   if(table[i][j][0] != table[(i+n-1)%n][j][2]) return false ; 

   return true ;
}

void Rotation(int n , int table[n][n][4] , int i , int j  , int x  ) {
    int fix[4] ; 
    for (int  z = 0; z < 4; z++)
    {
        fix[z] = table[i][j][z] ; 
    }
    
     for (int  z = 0; z < 4; z++)
    {
        table[i][j][(z + x)%4 ] = fix[z] ;
    }
}

void getcharType(int n , int table[n][n][4] , int i , int j  , char type) {
 if(type == 'S' || type == 'T'){
    table[i][j][0] = 0  , table[i][j][1] = 1  , table[i][j][2] = 1  , table[i][j][3] = 1  ;
 } else{
    if(type == 'C'){
        table[i][j][0] = 1  ,table[i][j][1] = 0  ,table[i][j][2] = 0  ,table[i][j][3] = 0   ; 
    } else{
        if(type == 'L') {
            table[i][j][0] = 1  ,table[i][j][1] = 1  ,table[i][j][2] = 0  ,table[i][j][3] = 0   ;
        } else{
            table[i][j][0] = 1  ,table[i][j][1] = 0  ,table[i][j][2] = 1  ,table[i][j][3] = 0   ; 
        }
    }
 }
}
