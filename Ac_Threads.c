#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int **matrizA, **matrizB, **matrizResultado;
int tamanho, num_threads;

// Função para iniciar as matrizes
void iniciar_matrizes() {
    matrizA = (int **)malloc(tamanho * sizeof(int *));
    matrizB = (int **)malloc(tamanho * sizeof(int *));
    matrizResultado = (int **)malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++) {
        matrizA[i] = (int *)malloc(tamanho * sizeof(int));
        matrizB[i] = (int *)malloc(tamanho * sizeof(int));
        matrizResultado[i] = (int *)malloc(tamanho * sizeof(int));
        for (int j = 0; j < tamanho; j++) {
            matrizA[i][j] = i + j;
            matrizB[i][j] = i + j;
            matrizResultado[i][j] = 0;
        }
    }
}

void liberar_matrizes() {
    for (int i = 0; i < tamanho; i++) {
        free(matrizA[i]);
        free(matrizB[i]);
        free(matrizResultado[i]);
    }
    free(matrizA);
    free(matrizB);
    free(matrizResultado);
}

 // Função executada por cada thread para realizar parte da multiplicação
void *multiplicar(void *arg) {
    int id_thread = *(int *)arg;
    int inicio = id_thread * (tamanho / num_threads);
    int fim = (id_thread + 1) * (tamanho / num_threads);
    if (id_thread == num_threads - 1) {
        fim = tamanho;
    }
    for (int i = inicio; i < fim; i++) {
        for (int j = 0; j < tamanho; j++) {
            for (int k = 0; k < tamanho; k++) {
                matrizResultado[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <tamanho da matriz> <numero de threads>\n", argv[0]);
        return 1;
    }

    tamanho = atoi(argv[1]);
    num_threads = atoi(argv[2]);
    if (num_threads > tamanho) {
        printf("O número de threads deve ser menor ou igual à tamanho da matriz.\n");
        return 1;
    }

    iniciar_matrizes();

    pthread_t threads[num_threads];
    int thread_ids[num_threads];
    clock_t inicio = clock();

    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiplicar, &thread_ids[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t fim = clock();
    double tempo_total = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo total: %.4f segundos\n", tempo_total);

    liberar_matrizes();
    return 0;
}
