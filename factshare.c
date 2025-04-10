#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *shm_name = "/os_lab";
    int fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open failed");
        return 1;
    }

    if (ftruncate(fd, sizeof(int)) == -1) {
        perror("ftruncate failed");
        return 1;
    }

    int *data = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    printf("ENTER THE NUMBER: ");
    scanf("%d", &data[0]);

    // Now read and calculate factorial
    int num = data[0];
    long long fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }

    printf("FACTORIAL OF %d IS: %lld\n", num, fact);

    // Cleanup
    munmap(data, sizeof(int));
    close(fd);
    shm_unlink(shm_name);

    return 0;
}
