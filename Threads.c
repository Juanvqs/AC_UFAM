#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX (100)

void *hello_thread(void *arg) {
   printf("Hello da thread %lld\n", (long long int) arg);
   return NULL;
}

int main(int argc, char *argv[]) {
   if (argc != 2) {
      fprintf(stderr, "uso: %s <n_threads>\n", argv[0]);
      exit(1);
   }

   int n_threads  = atoi(argv[1]); 
   
   // cria threads
   pthread_t pid[MAX];
   for (int i = 0; i < n_threads; i++) {
      pthread_create(&pid[i], NULL, hello_thread,(void *) (long long int) i);
   }

   // join threads
   for (int i = 0; i < n_threads; i++)
      pthread_join(pid[i], NULL);
   
   return 0;
}
