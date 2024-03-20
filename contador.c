#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 2048
#define NUM_THREADS 1

typedef struct {
    FILE *file;
    const char *word;
    int start;
    int end;
    int count;
    sem_t *count_sem;
} ThreadArgs;

void *count_occurrences(void *args_ptr) {
    ThreadArgs *args = (ThreadArgs *)args_ptr;

    char line[MAX_LINE_LENGTH];
    size_t word_length = strlen(args->word);

    fseek(args->file, args->start, SEEK_SET);

    char *lowercase_word = strdup(args->word);
    for (int i = 0; lowercase_word[i] != '\0'; i++) {
        lowercase_word[i] = tolower(lowercase_word[i]);
    }

    while (ftell(args->file) < args->end && fgets(line, sizeof(line), args->file) != NULL) {
        char *pos = line;

        char *lowercase_line = strdup(line);
        for (int i = 0; lowercase_line[i] != '\0'; i++) {
            lowercase_line[i] = tolower(lowercase_line[i]);
        }

        while ((pos = strstr(pos, lowercase_word)) != NULL) {
            pos += word_length;
            sem_wait(args->count_sem);
            args->count++;
            sem_post(args->count_sem);
        }

        free(lowercase_line);
    }

    free(lowercase_word);
    return NULL;
}

int main() {
    const char *filename = "elquijote.txt";
    const char *word = "presto";

    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    int total_count = 0;
    clock_t start, end;
    double time_spent;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    int part_size = file_size / NUM_THREADS;
    rewind(file);

    sem_t count_sem;
    sem_init(&count_sem, 0, 1);

    start = clock();

    for (int i = 0; i < NUM_THREADS; ++i) {
        args[i].file = file;
        args[i].word = word;
        args[i].start = i * part_size;
        args[i].end = (i == NUM_THREADS - 1) ? file_size : (i + 1) * part_size;
        args[i].count = 0;
        args[i].count_sem = &count_sem;
        pthread_create(&threads[i], NULL, count_occurrences, &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
        total_count += args[i].count;
    }

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Ejecutando busqueda con %d hilos.\n", NUM_THREADS);
    printf("La palabra '%s' aparece %d veces en el archivo '%s'.\n", word, total_count, filename);
    printf("Tiempo de ejecución: %f segundos.\n", time_spent);

    sem_destroy(&count_sem);

    fclose(file);

    return EXIT_SUCCESS;
}

