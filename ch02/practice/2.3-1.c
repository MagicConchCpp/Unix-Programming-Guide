/*
 * @author MagicConch
 * @description 
 * gcc 2.3-1.c -o 2.3-1
 * ./2.3-1 2.3-1.c
 * 打印文件内容到标准输出中
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 4096

void oops(char *, char *);

int main(int argc, char *argv[]) {
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];

    if (argc != 2) {
        fprintf(stderr, "usage: %s source file", *argv);
        exit(1);
    }

    if ( (in_fd = open(argv[1], O_RDONLY)) == -1 )
        oops("Cannot open", argv[1]);

    if ( (out_fd = open("/dev/tty", O_WRONLY)) == -1 )
        oops("Cannot open /dev/tty", "");

    while ( (n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
        if ( write(out_fd, buf, n_chars) != n_chars )
            oops("Write error to /dev/tty", "");

    if (n_chars == -1)
        oops("Read error from", argv[1]);

    if ( close(in_fd) == -1 || close(out_fd) == -1)
        oops("Error closing files", "");
    
    return 0;
}

void oops(char *s1, char *s2) {
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}