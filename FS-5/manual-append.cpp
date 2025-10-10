#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>\n";
        return EXIT_FAILURE;
    }

    int fd1 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    int fd2 = dup(fd1);
    if (fd2 == -1) {
        perror("dup");
        close(fd1);
        return EXIT_FAILURE;
    }

    const char* line1 = "first line\n";
    const char* line2 = "second line\n";

    if (write(fd1, line1, 11) == -1) {
        perror("write fd1");
        close(fd1);
        close(fd2);
        return EXIT_FAILURE;
    }

    if (write(fd2, line2, 12) == -1) {
        perror("write fd2");
        close(fd1);
        close(fd2);
        return EXIT_FAILURE;
    }

    close(fd1);
    close(fd2);

    return EXIT_SUCCESS;
}
