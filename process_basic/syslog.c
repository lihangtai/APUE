#include <stdio.h>
#include <syslog.h>

int main(){

    openlog("Mylogger", LOG_PID, LOG_USER);
    syslog(LOG_INFO, " this is a test message");

    closelog();

    return 0;
}
