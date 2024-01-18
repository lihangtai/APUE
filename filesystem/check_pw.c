#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <shadow.h>
#include <crypt.h>
#include <string.h>
#define SIZE 1024

int main(int argc, char *argv[]) {

    char *input_passwd;
    struct spwd *shadowline;
    char *final_pw;
    if (argc < 2) {
        fprintf(stderr, "plz follow the standard pattern\n");
        exit(-1);
    }
    input_passwd = getpass("Password input:");
    shadowline = getspnam(argv[1]);
    final_pw = crypt(input_passwd, shadowline->sp_pwdp);

    if (strcmp(shadowline->sp_pwdp, final_pw) == 0) {
        puts("ok!");
    } else {
        puts("failed!");
    }
    exit(0);
}


