#include "libs.h"

int my_server(int argc, char **argv) {
    char buf[100];
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0) {
        printf("Can't create socket\n");
        return -1;
    }

    const struct sockaddr_in sock_addr = {AF_INET, htons(PORT), inet_addr("127.0.0.1")};

    if (bind(sock_fd, (struct sockaddr*)(&sock_addr), sizeof(sock_addr)) < 0) {
        printf("Can't assign address to a socket\n");
        close(sock_fd);
        return -1;
    }

    if (listen(sock_fd, 1) < 0) {
        printf("Can't connect to socket\n");
        close(sock_fd);
        return -1;
    }

    struct sockaddr_in con_sock_addr;
    socklen_t con_socklen;
    int newsock_fd = accept(sock_fd, (struct sockaddr*)(&con_sock_addr), &con_socklen);
    if(newsock_fd < 0) {
        printf("Can't connect\n");
        return -1;
    }


    if (strcmp(argv[1],"PRINT")) {

        int pr_size = strlen(argv[1]);
        int mes_size = read(newsock_fd, buf, pr_size);
        if (mes_size != pr_size) {
            printf("Error while receiving message\n");
            return -1;
        }

        printf("\nReceived message: ");
        puts(buf);

    }

    if (strcmp(argv[2], "EXIT") == 0) {
        close(sock_fd);

    }

}

