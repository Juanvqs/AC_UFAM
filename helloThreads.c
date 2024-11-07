#include <pthread.h>
#include <stdio.h>

void *funcao_thread (){
    printf ("hello da thread\n");
}


int main (){
    pthread_t thread1;


    pthread_create (&thread1, NULL, funcao_thread, NULL );
    pthread_join (thread1, NULL);

    return 1;
}