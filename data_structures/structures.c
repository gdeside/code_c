#include<stdio.h> 
#include<stdlib.h>
  
struct Point 
{ 
   int x, y; 
}; 
  
int main() { 
   struct Point p1 = {1, 2}; 
  
   // p2 is a pointer to structure p1 
   struct Point *p2 = &p1; 
   
   struct Point *p3=malloc(sizeof(struct Point));
   p3->x=2;
   p3->y=1;
      // Accessing structure members using structure pointer 
   printf("%d %d \n", p2->x, p2->y); 
   printf("%d %d\n", p3->x, p3->y); 
   return 0; 
}