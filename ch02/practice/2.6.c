/*
 * @author MagicConch
 * @description 
 * gcc 2.6.c -o 2.6
 * ./2.6
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 1024

void oops(char *, char *);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "usage : %s <file>", argv[0]);
        exit
    }

    int fd1, fd2, fd3;
    char buf[BUFFERSIZE];
    if ( (fd1 = open(argv[1], O_RDONLY)) == -1 ) 
        oops("fd1: Cannot open file", "2.6.txt");
    if ( (fd2 = open(argv[1], O_WRONLY)) == -1 ) 
        oops("fd2: Cannot open file", "2.6.txt");
    if ( (fd3 = open(argv[1], O_RDONLY)) == -1 ) 
        oops("fd3: Cannot open file", "2.6.txt");
    
    int rev_len = 0;
    rev_len = read(fd1, buf, 20);
    if (rev_len == -1)
        oops("Read error", "fd1");
    buf[rev_len] = '\0';
    puts(buf);

    char write_buf[] = "testing 123...";
    if ( (write(fd2, write_buf, sizeof(write_buf))) == -1)
        oops("Write error", "fd2");

    rev_len = read(fd3, buf, 20);
    if (rev_len == -1)
        oops("Read error", "fd2");
    buf[rev_len] = '\0';
    puts(buf);
}

void oops(char *s1, char *s2) {
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}
