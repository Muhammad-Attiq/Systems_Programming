#include <stdio.h>
#include <pthread.h>

void* hello_thread(void* arg) {
    int thread_num = *(int*)arg;
    printf("HELLO from thread %d | Thread ID: %lu\n", thread_num, pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_nums[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, hello_thread, &thread_nums[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("ALL threads completed\n");

    return 0;
}
