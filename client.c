#include "libs.h"

int main(int argc, char **argv) {
    char *message = "Message from client";
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        printf("Can't create socket");
        return -1;
    }

    const struct sockaddr_in server_addr = {AF_INET, htons(PORT), inet_addr("127.0.0.1")};
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Connection error\n");
        return -1;
    }


    if(strcmp(argv[1], "PRINT") == 0) {
        if(argc < 3) {
            printf("No message!\n");
            return -1;
        }
        char *buf = calloc(strlen(argv[2]) + 1, 1);
        buf[0] = '1';
        strcat(buf, argv[2]);
        if(write(sock_fd, buf, strlen(buf))< 0) {
            printf("Can't write message");
            return -1;
        }
        free(buf);
    }

    if(strcmp(argv[1],"EXIT") == 0) {
        char buf[1];
        buf[0] = '0';
        write(sock_fd, buf, 1);
    }

    close(sock_fd);
    return 0;



}