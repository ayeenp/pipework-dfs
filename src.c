#include <stdio.h>
#include <stdbool.h> 
int Q = 1 ; 

void Rotation(int n , int table[n][n][4] , int , int , int   ) ;  
void getcharType(int n , int table[n][n][4] , int , int , char) ; 
bool Checkcell( int n , int table[n][n][4] , int , int  ) ; 
void solution( int n , int table[n][n][4] , int table2[n][n][4] , bool fixed[n][n] , int  , int) ; 
void printTable(int n , int table[n][n][4] , int table2[n][n][4]) ; 
bool checkBranch(int n , int table[n][n][4] , bool fixed[n][n] , int , int ) ; 
void Copyfixes(int n , bool fixed[n][n] , bool lastfixed[n][n]) ; 
bool BackToServer(int n , int table[n][n][4] , bool visited[n][n] ,   int , int) ; 
void Resetvisited(int n , bool visited[n][n]) ; 

int main(){
   int n  , FirstRot; 
   char celltype ; 
   scanf("%d" , &n) ; 
   int table[n][n][4] ; 
   int table2[n][n][4] ; 
   bool fixed[n][n] ;
   for (int i = 0; i < n; i++) { 
     for (int j = 0; j < n; j++){
        scanf(" %c%d" , &celltype , &FirstRot ) ; 
        getcharType( n , table , i , j , celltype) ; 
        Rotation( n , table , i , j , FirstRot) ; 
        for(int k = 0 ; k < 4 ; k ++ ){
            table2[i][j][k] = table[i][j][k] ; 
        }
        fixed[i][j] = 0 ; 
     }
   }
    solution(n , table , table2 , fixed ,  0 , 0 ) ; 
    
    return 0   ; 
}

void solution (int n , int table[n][n][4] , int table2[n][n][4] , bool fixed[n][n] ,  int i  , int j ) {
    if(Q == 1 ) {
      if( (i != n - 1) || (j != n - 1)) {
          fixed[i][j] = 1 ; 
        if( i == 0 && j == 0 ){
            for (int w = 0; w < 4  ; w++) {
                bool fixed2[n][n] ;
                Copyfixes(n , fixed2 , fixed) ; 
                solution(n , table , table2 , fixed , (i+1) % n , j + ((i+1)/n) ) ;
                Copyfixes(n , fixed , fixed2) ; 
                Rotation( n , table , i , j , 1) ; 
            }
        }else {
               if(checkBranch( n , table , fixed , (i+1)%n , j + ((i+1)/n) )) {
                if( j == 0 ){
                    //printf("%d : %d \n" , i , j) ; 
                   for (int c = 0 ; c < 4  ; c++) {
                      if( (table[i][j][0] == table[(i+n-1) % n][j][2]) || fixed[(i+n-1)%n][j] == 0  ){
                           bool fixed3[n][n] ; 
                           Copyfixes(n , fixed3 , fixed) ; 
                           solution(n , table , table2 , fixed , (i+1) % n , j + ((i+1)/n) ) ;
                           Copyfixes(n , fixed ,fixed3) ; 
                      }
                      Rotation( n , table , i , j , 1) ; 
                    } 
                } else{
                    for (int r = 0;  r < 4  ; r++) {
                       // printf("%d : %d \n" , i , j ) ; 
                        if(((table[i][j][0] == table[(i+n-1)% n][j][2]) || fixed[(i+n-1)%n][j] == 0) && (table[i][j][3] == table[i][(j+n-1)%n][1])){
                            bool fixed4[n][n] ; 
                            Copyfixes(n ,fixed4 , fixed ) ;
                            solution(n , table , table2 , fixed , (i+1) % n , j + ((i+1)/n) ) ;
                            Copyfixes(n , fixed , fixed4 ) ; 
                        }
                        Rotation( n , table , i , j , 1) ; 
                    }
                } 
            }
          }
        } else {
        //    printf("saf") ; 
            for (int x = 0 ; x < 4 ; x++) {
                if(checkBranch(n , table , fixed ,  i , j)){
                    int IsAns = 1 ; 
                    for (int z = 0; z < n ; z++) {
                        for(int y = 0 ; y < n ; y ++){
                            if(Checkcell(n , table , z , y) == 0){
                                IsAns = 0 ;
                                break ; 
                            }
                        }
                        if(IsAns ==0) break ; 
                    }
                    if(IsAns == 1) {
                        for (int z = 0; z < n ; z++) {
                          for(int y = 0 ; y < n ; y ++){
                              bool visited[n][n] ; 
                              Resetvisited( n , visited) ; 
                              if(BackToServer(n , table , visited , z , y) == 0 ) {
                                  IsAns = 0 ;
                                  break ;
                              }
                            }
                              if(IsAns == 0) break ; 
                         }
                         if(IsAns == 1 ) {
                        printTable( n , table2 , table) ; 
                        Q = 0 ; 
                        break ; 
                         }
                    }
                }
                Rotation(n , table , i , j , 1) ; 
            }
        }
  }
}


bool BackToServer(int n , int table[n][n][4] , bool visited[n][n] ,  int i  , int j){
    if( (i == n/2) && (j == n/2)  ){
        return true ; 
    }
    visited[i][j] = 1 ; 
    if( (table[i][j][1] == 1 && table[i][(j+1)% n ][3] == 1) && visited[i][(j+1) % n] == 0 ) {
            //bool visited2[n][n] ;
            //Copyfixes( n , visited2 , visited) ;
         if(BackToServer( n , table , visited , i , (j + 1 )%n)) return true  ; 
    }
    if( (table[i][j][2] == 1 && table[(i+1) % n][j][0] == 1) && visited[(i+1) % n ][j] == 0){
            //bool visited2[n][n] ;
            //Copyfixes( n , visited2 , visited) ;
         if(BackToServer( n , table , visited , (i+1) % n , j )) return true  ;
    } 
    if( (table[i][j][0] == 1 && table[(i+n-1) % n][j][2] == 1)  && visited[(i+n-1) % n][j] == 0) {
            //bool visited2[n][n] ;
            //Copyfixes( n , visited2 , visited) ;
          if(BackToServer( n , table , visited , (i+n-1)%n , j )) return true  ; 
    } 
    if( (table[i][j][3] == 1 && table[i][(j+n-1)%n][1] == 1) && visited[i][(j+n-1) % n] == 0) {
  //          bool visited2[n][n] ;
//            Copyfixes( n , visited2 , visited) ; 
         if(BackToServer( n , table ,visited  ,  i , (j+n-1 ) %n)) return true  ; 
    } 
    return false ; 
}

bool checkBranch(int n , int table[n][n][4] , bool fixed[n][n] , int i  , int j ) {
    int temp[4] = { 2 , 2 , 2 , 2 } ;
    if(fixed[(i+n-1)%n][j]) temp[0] = table[(i+n-1) % n][j][2] ; 
    if(fixed[i][(j+1)%n]) temp[1] = table[i][(j+1)%n][3] ;
    if(fixed[(i+1)%n][j]) temp[2] = table[(i+1)%n][j][0] ; 
    if(fixed[i][(j+n-1)]) temp[3] = table[i][(j+n-1)%n][1] ;
  //  printf("%d : %d : %d : %d \n" , table[i][j][0] , temp[1] , temp[2] ,temp[3]) ; 
    for (int k = 0; k < 4; k++) {
        if((temp[0] == table[i][j][0]  || temp[0] == 2 ) && (temp[1] == table[i][j][1]  || temp[1] == 2 ) ) {
            if((temp[2] == table[i][j][2]  || temp[2] == 2 ) && (temp[3] == table[i][j][3]  || temp[3] == 2 )){
             return true ;             
            }
        }
        Rotation(n , table , i , j , 1) ;
    }
    return false ; 
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


void Copyfixes(int n , bool fixed[n][n] , bool lastfixed[n][n] ) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fixed[i][j] = lastfixed[i][j] ; 
        }
    }
}    

void Resetvisited(int n , bool visited[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
           visited[i][j] = false ; 
        }
    }
} 
