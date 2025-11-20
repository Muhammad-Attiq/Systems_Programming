#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int current_task = 0;
int total_tasks = 10;
int turn = 0;

void* worker(void* arg) {
    int id = *(int*)arg;

    while (1) {
        if (current_task >= total_tasks) break;

        if (turn == id) {
            printf("Thread %d processing task %d\n", id, current_task);
            current_task++;
            turn = (turn + 1) % 3;
            sleep(1);
        }
    }

    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {0, 1, 2};

    for (int i = 0; i < 3; i++)
        pthread_create(&threads[i], NULL, worker, &ids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    printf("All tasks completed\n");
    return 0;
}
