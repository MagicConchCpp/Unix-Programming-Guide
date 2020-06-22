/*
 * @author MagicConch
 * @description 
 * gcc 2.10.c -o 2.10
 * ./2.10
 * 打印出root（当前用户）
 */


#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// #define SHOWHOST

void showtime(long);
void show_info(struct utmp *utbufp);

int main() {
    struct utmp cur_record;
    int utmp_fd;
    int reclen= sizeof(cur_record);
    char *my_line = ttyname(0);
    if ( (utmp_fd = open(UTMP_FILE, O_RDONLY)) == -1 ) {
        perror(UTMP_FILE);
        exit(1);
    }
    while ( read(utmp_fd, &cur_record, reclen) == reclen ) {
        if ( my_line == NULL || strcmp(my_line, cur_record.ut_line) == 0 )
            show_info(&cur_record);
    }
    close(utmp_fd);
    return 0;
}

void show_info(struct utmp *utbufp) {
    if (utbufp->ut_type != USER_PROCESS)
        return;
    
    printf("%s", utbufp->ut_user);
}
