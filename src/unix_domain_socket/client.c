#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/socket"

int main() {
    int sockfd;
    struct sockaddr_un addr;

    // Create a Unix domain socket
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up the address structure
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Send data to the server
    const char* message = "Hello, server!";
    if (write(sockfd, message, strlen(message)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Receive data from the server
    char buffer[256];
    ssize_t numBytes = read(sockfd, buffer, sizeof(buffer) - 1);
    if (numBytes == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[numBytes] = '\0';

    printf("Received: %s\n", buffer);

    // Close the socket
    close(sockfd);

    return 0;
}
