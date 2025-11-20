#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

typedef struct {
    int start;
    int end;
    int count;
} Segment;

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0) return 0;
    return 1;
}

void* find_primes(void* arg) {
    Segment* s = (Segment*)arg;
    s->count = 0;
    for (int i = s->start; i <= s->end; i++)
        if (is_prime(i)) s->count++;
    return NULL;
}

int main() {
    struct timeval t1, t2;
    pthread_t threads[4];
    Segment seg[4];

    int range = 10000;
    int part = range / 4;

    gettimeofday(&t1, NULL);

    for (int i = 0; i < 4; i++) {
        seg[i].start = i * part + 1;
        seg[i].end = (i == 3) ? range : (i + 1) * part;
        pthread_create(&threads[i], NULL, find_primes, &seg[i]);
    }

    int total = 0;
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
        total += seg[i].count;
    }

    gettimeofday(&t2, NULL);
    long parallel_time = (t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec);

    gettimeofday(&t1, NULL);

    int seq_count = 0;
    for (int i = 1; i <= range; i++)
        if (is_prime(i)) seq_count++;

    gettimeofday(&t2, NULL);
    long seq_time = (t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec);

    printf("Parallel prime count: %d\n", total);
    printf("Sequential prime count: %d\n", seq_count);
    printf("Parallel time: %ld microseconds\n", parallel_time);
    printf("Sequential time: %ld microseconds\n", seq_time);

    return 0;
}
