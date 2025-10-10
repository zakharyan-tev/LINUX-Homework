#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void check(bool arg, const char* msg) {
    if (arg) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv)
{
    check(argc != 2, "Usage");

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    check(fd == -1, "open");

    int fd2 = dup(fd);
    check(fd2 == -1, "dup");

    const char str[] = "first line\n";
    const char str2[] = "second line\n";

    check(write(fd, str, sizeof(str) - 1) == -1, "write fd");
    check(write(fd2, str2, sizeof(str2) - 1) == -1, "write fd2");

    close(fd);
    close(fd2);

    return 0;
}
