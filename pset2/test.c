#include <stdio.h>
 
void doubleit( int *x, int *y){
   *x *= 2;
   *y *= 2;
}
 
int main(void){
   int x = 10;
   int y = 5;
   doubleit( &x, &y);
   printf("%i %i",x,y);
   return 0;
}
