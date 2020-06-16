#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SHOWHOST

void show_info(struct utmp *utbufp);

int main() {
    struct utmp cur_record;
    int utmp_fd;
    int reclen= sizeof(cur_record);
    // printf("%d", reclen);

    if ( (utmp_fd = open(UTMP_FILE, O_RDONLY)) == -1 ) {
        perror(UTMP_FILE);
        exit(1);
    }
    while ( read(utmp_fd, &cur_record, reclen) == reclen ) {
        show_info(&cur_record);
    }
    close(utmp_fd);
    return 0;    
}

void show_info(struct utmp *utbufp) {
    printf("%-8.8s", utbufp->ut_user);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    printf("%d", utbufp->ut_tv.tv_sec);

    #ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
    #endif
    printf("\n");
}