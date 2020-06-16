#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// #define SHOWHOST

void showtime(long);
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
    // if (utbufp->ut_type != USER_PROCESS)
    //     return;
    
    printf("%-8.8s", utbufp->ut_user);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    showtime(utbufp->ut_tv.tv_sec);

    #ifdef SHOWHOST
    if (utbufp->ut_host[0] != '\0')
        printf("(%s)", utbufp->ut_host);
    #endif
    printf("\n");
}

void showtime(long timeval) {
    char *cp;
    cp = ctime(&timeval);
    printf("%12.12s", cp + 4);
}