#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 64

int main() {
    int src_fd = open("src.txt", O_RDONLY);
    if (src_fd == -1) {
        perror("open src");
        return 1;
    }

    int dst_fd = open("dst.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("open dst");
        close(src_fd);
        return 1;
    }

    char buf[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(src_fd, buf, BUFFER_SIZE)) > 0) {
        bytes_written = write(dst_fd, buf, bytes_read);
        if (bytes_written != bytes_read) {
            perror("~write");
            break;
        }
    }

    close(src_fd);
    close(dst_fd);
    printf("拷贝完成\n");
    return 0;
}