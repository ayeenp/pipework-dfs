
#include <stdio.h>
#include <stdbool.h>

//You saw nothing !
void reset(int n , bool visited[n][n]) ; 
//translate type of a square to a int 
int translate(char ) ;
// to check two square is connect or not 
bool IsConnect(int n , int table[n][n][3]  ,  int  , int , int , int ) ;
// to check are we have electricity in this square or not 
bool IsElectric(int n , int table[n][n][3] ,  bool visited[n][n] ,  int , int  ) ;

//printing solution 
void Print(int n ,  int table[n][n][3] ) ; 

// backtrack for finding solution 
bool solution(int n , int table[n][n][3] , bool visited[n][n]  , int , int  ) ;  

int main()
{    int n , computers = 0  ;
     char help ; 
     scanf("%d" , &n) ; 
     // the first index is type of what it is :  S = 0 , C = 1 , L = 2 , T = 3 , I = 4  
     int table[n][n][3]; 
     bool visited[n][n] ;
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
             scanf(" %c%d" , &help , &table[i][j][1]) ; 
             table[i][j][0] = translate(help) ;
             if(table[i][j][0] == 1){
              computers ++ ;
             }
             table[i][j][2] = table[i][j][1] ; 
             visited[i][j] = false  ; 
         }
     }
    bool end = solution(n, table , visited , 0 , 0) ; 
    return 0 ;
}

void reset(int n , bool visited[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = false ; 
        }
    }
} 


int translate(char x ) {
    if(x == 'S') {
        return 0 ;
    } else {
        if(x == 'C') {
            return 1 ;
        } else {
            if(x == 'L') {
                return 2 ;
            } else {
                if(x == 'T') {
                    return 3 ; 
                } else {
                    return 4 ; 
                }
            }
        }
    }
}

bool IsConnect(int n , int table[n][n][3] , int x1   , int y1 , int x2 , int y2 ) {
    // when they are in a column :
    if( y1 == y2){
        if((table[x1][y1][0] == 1 && table[x1][y1][1] == 0) || (table[x1][y1][0] == 4 && table[x1][y1][1] %2 == 0) ){
           if(table[x2][y2][0] == 1 && table[x2][y2][1] == 2 && table[x1][y1][0] != 1) return true ;
           if(table[x2][y2][0] == 2 &&(table[x2][y2][1] == 1 || table[x2][y2][1] == 2)) return true ; 
           if((table[x2][y2][0] == 0 || table[x2][y2][0] == 3) && table[x2][y2][1] != 2) return true ; 
           if(table[x2][y2][0] == 4 && table[x2][y2][1] %2 == 0) return true ; 
        } else {
            if(table[x1][y1][0] == 2 && (table[x1][y1][1] == 0 || table[x1][y1][1] == 3)){
              if(table[x2][y2][0] == 1 && table[x2][y2][1] == 2 && table[x1][y1][0] != 1) return true ;
              if(table[x2][y2][0] == 2 &&(table[x2][y2][1] == 1 || table[x2][y2][1] == 2)) return true ; 
              if((table[x2][y2][0] == 0 || table[x2][y2][0] == 3) && table[x2][y2][1] != 2) return true ; 
              if(table[x2][y2][0] == 4 && table[x2][y2][1] % 2 == 0) return true ; 
            }else {
             if((table[x1][y1][0] == 0 || table[x1][y1][0] == 3 ) && table[x1][y1][1] != 0 ) {
              if(table[x2][y2][0] == 1 && table[x2][y2][1] == 2 && table[x1][y1][0] != 1) return true ;
              if(table[x2][y2][0] == 2 &&(table[x2][y2][1] == 1 || table[x2][y2][1] == 2)) return true ; 
              if((table[x2][y2][0] == 0 || table[x2][y2][0] == 3) && table[x2][y2][1] != 2) return true ; 
              if(table[x2][y2][0] == 4 && table[x2][y2][1] %2 == 0) return true ;   
               }
            }
        }
    } else {
     //when they are in a row
     if((table[x1][y1][0] == 1  && table[x1][y1][1] == 1) || (table[x1][y1][0] == 4 && table[x1][y1][1] %2 == 1) ){
         if(table[x2][y2][0] == 1 && table[x1][y1][0] != 1 && table[x2][y2][1] == 3  ) return true ;
         if(table[x2][y2][0] == 2 &&( table[x2][y2][1] == 2 || table[x2][y2][1] == 3)) return true ; 
         if((table[x2][y2][0] == 0 || table[x2][y2][0] == 3)  && table[x2][y2][1] != 3) return true ; 
         if(table[x2][y2][0] == 4 && table[x2][y2][1] %2 ==  1) return true ; 
     }else{
         if(table[x1][y1][0] == 2 && (table[x1][y1][1] == 0 || table[x1][y1][1] == 1)) {
           if(table[x2][y2][0] == 1 && table[x1][y1][0] != 1 && table[x2][y2][1] == 3  ) return true ;
           if(table[x2][y2][0] == 2 &&( table[x2][y2][1] == 2 || table[x2][y2][1] == 3)) return true ; 
           if((table[x2][y2][0] == 0 || table[x2][y2][0] == 3)  && table[x2][y2][1] != 3) return true ; 
           if(table[x2][y2][0] == 4 && table[x2][y2][1] %2  == 1) return true ;
         } else {
          if( (table[x1][y1][0] == 0 || table[x1][y1][0] == 3 ) && table[x1][y1][1] != 1){
             if(table[x2][y2][0] == 1 && table[x1][y1][0] != 1 && table[x2][y2][1] == 3  ) return true ;
             if(table[x2][y2][0] == 2 &&( table[x2][y2][1] == 2 || table[x2][y2][1] == 3)) return true ; 
             if((table[x2][y2][0] == 0 || table[x2][y2][0] == 3)  && table[x2][y2][1] != 3) return true ; 
             if(table[x2][y2][0] == 4 && table[x2][y2][1] %2  == 1) return true ;             
             }
         }
      }
    }
    return false ;
} 

bool IsElectric(int n , int table[n][n][3] , bool visited[n][n] ,  int i , int j ) { 
    if((i == n/2  && j == n/2 )) { 
         
        return true ; 
    }
    visited[i][j] = true ;
    if((visited[(i+1) % n][j])==0 && IsConnect(n , table , (i + 1)%n , j , i , j) ) {
        if(IsElectric(n , table , visited , (i+1)%n , j)) return true ; 
    }

    if((visited[(i+n-1) % n][j])==0 && IsConnect(n , table , i , j , (i+n-1)%n , j) ) {
        if(IsElectric(n , table , visited , (i+n-1)%n , j)) return true ; 
    }
    
    if((visited[i][(j+1)%n])==0 && IsConnect(n , table , i , j , i , (j+1)%n) ) {
        if(IsElectric(n , table , visited , i , (j+1)%n)) return true ; 
    } 
    
    if((visited[i][(j + n -1) %n ])==0 && IsConnect(n , table , i , (j+n-1)%n , i , j) ) {
        if(IsElectric(n , table , visited , i , (j+n-1)%n )) return true ; 
    }    
     
    return false ; 
}


void Print(int n , int table[n][n][3] ) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d " , (n + table[i][j][1] - table[i][j][2]) % n ) ; 
        }
        printf("\n") ;
    }
}


 bool solution(int n , int table[n][n][3] , bool visited[n][n]   , int i  , int j    ){
     int check = 0  ;
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n; j++){ ;
                reset(n , visited) ;
                if(IsElectric(n , table , visited , i , j)){
                    check ++ ; 
                 }
            }
        }
    if(check == n * n){
        return true ; 
    } 
    
    
    for (int z = 0; z < 4; z++) {
        table[i][j][1] += z ; 
        table[i][j][1] %= 4 ;
        if( i != n - 1){
            //printf("ghkj") ; 
                if( solution(n , table , visited , i + 1 , j  ) == true ){
                      Print(n , table)  ;
                      break ; 
                }
            } else {
                if( solution( n, table , visited , 0 , j + 1 ) == true){
                    Print(n , table) ;
                    break ; 
            }
        }
    }
    
    return false ; 
} 