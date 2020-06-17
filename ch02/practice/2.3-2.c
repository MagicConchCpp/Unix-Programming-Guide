/*
 * @author MagicConch
 * @description 
 * gcc 2.3-2 -o 2.3-2
 * ./2.3-2 2.3-2.txt
 * 在标准输入中输入文本，回车键 + <Ctrl +D> 结束。
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);

int main(int argc, char *argv[]) {
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];

    if (argc != 2) {
        fprintf(stderr, "usage: %s destination file", *argv);
        exit(1);
    }

    if ( (in_fd = open("/dev/tty", O_RDONLY)) == -1 )
        oops("Cannot open /dev/tty", "");

    if ( (out_fd = creat(argv[1], COPYMODE)) == -1 )
        oops("Cannot creat", argv[1]);

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