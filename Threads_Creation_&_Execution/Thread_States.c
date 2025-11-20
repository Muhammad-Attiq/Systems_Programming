#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* sleeper(void* arg) {
    int t = *(int*)arg;
    sleep(t);
    return NULL;
}

int main() {
    pthread_t th[3];
    int times[3] = {5, 10, 15};

    for (int i = 0; i < 3; i++)
        pthread_create(&th[i], NULL, sleeper, &times[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(th[i], NULL);

    printf("All threads finished.\n");
    return 0;
}
