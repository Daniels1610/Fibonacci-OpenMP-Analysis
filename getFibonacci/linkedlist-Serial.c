// linkedlist-Serial
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// CONSTANTS
#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

// STRUCTS
struct node {
   int data;
   int fibdata;
   struct node* next;
};
typedef struct node node;

// FUNCTIONS
int fib(int n);
void processwork(node* p);
node* init_list(node* p);

int main(int argc, char *argv[]) {
   double start, end;
   node *p=NULL; node *temp=NULL; node *head=NULL;
   
   // printf("Process linked list\n");
   // printf("  Each linked list node will be processed by function 'processwork()'\n");
   // printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N+1,FS);      

   p = init_list(p);
   head = p;

   start = omp_get_wtime();
   {
      while (p != NULL) {
      processwork(p);
      p = p->next;
      }
   }

   end = omp_get_wtime();
   p = head;
   while (p != NULL) {
      // printf("%d : %d\n",p->data, p->fibdata);
      temp = p->next;
      free (p);
      p = temp;
   }  
   free (p);
   printf("%f\n", end - start);
   return 0;
}

int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fib(n - 1);
      y = fib(n - 2);
	  return (x + y);
   }
}

void processwork(node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

node* init_list(node* p) {
   int i;
   node* head = NULL;
   node* temp = NULL;
   
   head = malloc(sizeof(node));
   p = head;
   p->data = FS;
   p->fibdata = 0;
   for (i = 0; i < N; i++) {
      temp = malloc(sizeof(node));
      p->next = temp;
      p = temp;
      p->data = FS + i + 1;
      p->fibdata = i + 1;
   }
   p->next = NULL;
   return head;
}