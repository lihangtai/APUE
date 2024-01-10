#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int fileA, fileB;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    // 打开文件 A 以只读方式
    fileA = open(argv[1], O_RDONLY);
    if (fileA == -1) {
        perror("Error opening fileA.txt");
        return -1;
    }

    // 创建或打开文件 B 以可写方式，如果文件不存在则创建
    fileB = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,0600);
    if (fileB == -1) {
        perror("Error opening/creating fileB.txt");
        close(fileA);
        return -1;
    }

    // 读取并写入文件内容
    while ((bytesRead = read(fileA, buffer, sizeof(buffer))) > 0) {
        bytesWritten = write(fileB, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Write error");
            close(fileA);
            close(fileB);
            return -1;
        }
    }

    // 关闭文件描述符
    close(fileA);
    close(fileB);

    printf("File copied successfully.\n");
    return 0;
}

