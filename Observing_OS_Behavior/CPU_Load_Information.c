#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    double loadavg[3];

    printf("=== System Load Averages ===\n");

    getloadavg(loadavg, 3);
    printf("Before task:\n");
    printf(" 1 min: %.2f, 5 min: %.2f, 15 min: %.2f\n",
           loadavg[0], loadavg[1], loadavg[2]);

    printf("\nRunning CPU-intensive task...\n");
    for (long i = 0; i < 1000000000; i++);

    getloadavg(loadavg, 3);
    printf("During task:\n");
    printf(" 1 min: %.2f, 5 min: %.2f, 15 min: %.2f\n",
           loadavg[0], loadavg[1], loadavg[2]);

    printf("\nWaiting for system to settle...\n");
    sleep(10);
    getloadavg(loadavg, 3);
    printf("After task:\n");
    printf(" 1 min: %.2f, 5 min: %.2f, 15 min: %.2f\n",
           loadavg[0], loadavg[1], loadavg[2]);

    printf("\nObservation complete.\n");
    return 0;
}
