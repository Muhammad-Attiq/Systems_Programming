#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void read_memory_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/meminfo");
        exit(1);
    }

    char label[64];
    unsigned long value;
    char unit[32];
    int count = 0;

    printf("\n=== Memory Information ===\n");
    while (fscanf(fp, "%63s %lu %31s", label, &value, unit) == 3) {
        if ((strcmp(label, "MemTotal:") == 0) ||
            (strcmp(label, "MemFree:") == 0) ||
            (strcmp(label, "MemAvailable:") == 0) ||
            (strcmp(label, "Buffers:") == 0) ||
            (strcmp(label, "Cached:") == 0)) {

            printf("%-15s %10lu %s\n", label, value, unit);
            count++;
        }
        if (count >= 5)
            break;
    }
    fclose(fp);
}

void read_cpu_usage() {
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/stat");
        exit(1);
    }

    char cpu[8];
    unsigned long user, nice, system, idle, iowait, irq, softirq;

    fscanf(fp, "%s %lu %lu %lu %lu %lu %lu %lu",
           cpu,
           &user, &nice, &system, &idle, &iowait, &irq, &softirq);

    fclose(fp);

    unsigned long total = user + nice + system + idle + iowait + irq + softirq;
    unsigned long busy = total - idle;

    printf("\n=== CPU Usage Snapshot ===\n");
    printf("User Time:   %lu\n", user);
    printf("System Time: %lu\n", system);
    printf("Idle Time:   %lu\n", idle);
    printf("CPU Busy:    %.2f%%\n", (busy * 100.0) / total);
}

int main() {
    printf("Comparing System Info with top/htop/free\n");
    printf("======================================\n");

    for (int i = 0; i < 3; i++) {
        printf("\n--- Snapshot %d ---\n", i + 1);
        read_memory_info();
        read_cpu_usage();
        sleep(2);
    }

    printf("\nNow open another terminal and compare with:\n");
    printf(" htop\n");
    printf(" top\n");
    printf(" free -m\n");

    return 0;
}
