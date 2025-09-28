#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        perror("Wrong arguments");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("Error getting file size");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    const int BUF_SIZE = 4096;
    char buffer[BUF_SIZE];
    for (int i = 0; i < BUF_SIZE; i++) {
        buffer[i] = '\0';
    }

    off_t remaining = file_size;
    while (remaining > 0) {
        ssize_t to_write = (remaining > BUF_SIZE) ? BUF_SIZE : remaining;
        ssize_t written = write(fd, buffer, to_write);
        if (written == -1) {
            perror("Error writing to file");
            close(fd);
            exit(EXIT_FAILURE);
        }
        remaining -= written;
    }

    close(fd);
    return 0;
}
