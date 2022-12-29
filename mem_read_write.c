#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s pid offset [value]\n", argv[0]);
        return 1;
    }

    pid_t pid = (pid_t)atoi(argv[1]);
    off_t offset = (off_t)strtoull(argv[2], NULL, 0);

    char mem_file[64];
    sprintf(mem_file, "/proc/%d/mem", pid);

    int fd = open(mem_file, O_RDWR);
    if (fd == -1) {
        perror("Error opening mem file");
        return 1;
    }

    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("Error seeking in mem file");
        close(fd);
        return 1;
    }

    if (argc == 3) {
        // Read value from memory
        char* buffer = (char*)malloc(1024 + 1); // Can be extended with realloc
        if(buffer == NULL) {
            printf("Error could not allocate memory");
        }
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("Error reading from mem file");
            close(fd);
            return 1;
        }
        printf("Read %ld bytes: %s\n", bytes_read, buffer);
    } else {
        // Write value to memory
        const char *value = argv[3];
        ssize_t bytes_written = write(fd, value, strlen(value));
        if (bytes_written == -1) {
            perror("Error writing to mem file");
            close(fd);
            return 1;
        }
        printf("Wrote %ld bytes: %s\n", bytes_written, value);
    }

    close(fd);
    return 0;
}
