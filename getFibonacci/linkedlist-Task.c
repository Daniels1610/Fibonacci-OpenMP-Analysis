// linkedlist-Task
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// CONSTANTS
#ifndef N 
#define N 4
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
   int num_threads = atoi(argv[1]);
   omp_set_num_threads(num_threads);

   node *p=NULL; node *temp=NULL ;node *head=NULL;
   double start, end;
   
   p = init_list(p);
   start = omp_get_wtime();

   // Get Linked List size
   #pragma omp parallel firstprivate(p)
   {
      #pragma omp single 
      {
         while (p != NULL) {
            #pragma omp task 
              {processwork(p);} // printf("%d : %d\n", p->data, p->fibdata);} // Display Fibonacci Number
            p = p->next; 
         }
      }
   }
   
   free(p);
   end = omp_get_wtime();
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
   node* head = NULL; node* temp = NULL;
   
   head = malloc(sizeof(node));
   p = head;
   p->data = FS;
   p->fibdata = 0;
   for (i = 0; i < N; i++) {
      temp  =  malloc(sizeof(node));
      p->next = temp;
      p = temp;
      p->data = FS + i + 1;
      p->fibdata = i+1;
   }
   p->next = NULL;
   
   return head;
}