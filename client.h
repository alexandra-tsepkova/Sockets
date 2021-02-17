#include "libs.h"

int my_client(int argc, char **argv) {
    char *message = "Message from client";
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        printf("Can't create socket");
        return -1;
    }

    const struct sockaddr_in server_addr = {AF_INET, htons(PORT), inet_addr("127.0.0.1")};
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Connection error");
        return -1;
    }

    if(strcmp(argv[1], "PRINT") == 0) {
        if(write (sock_fd, argv[2], strlen(argv[2])) < 0) {
            printf("Can't write message");
            return -1;
        }
    }

    close(sock_fd);
    return 0;



}