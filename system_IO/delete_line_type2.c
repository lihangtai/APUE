#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    FILE *file_read = fopen(argv[1], "r");
    if (file_read == NULL) {
        perror("Error opening file for reading");
        return -1;
    }

    FILE *file_write = fopen(argv[1], "r+");
    if (file_write == NULL) {
        perror("Error opening file for writing");
        fclose(file_read);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    int line_to_delete = atoi(argv[2]);
    long write_pos = 0;

    // 读取并写入，跳过要删除的行
    while (fgets(line, MAX_LINE_LENGTH, file_read) != NULL) {
        line_number++;
        if (line_number != line_to_delete) {
            fseek(file_write, write_pos, SEEK_SET);
            fputs(line, file_write);
            fflush(file_write);
            write_pos = ftell(file_write);
        } else {
            write_pos = ftell(file_write);
        }
    }

    // 截断文件
    ftruncate(fileno(file_write), write_pos);

    // 关闭文件
    fclose(file_read);
    fclose(file_write);

    return 0;
}

