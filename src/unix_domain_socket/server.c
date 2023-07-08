#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/socket"

int main() {
    int sockfd, client_sockfd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;
    char buffer[256];

    // Create a Unix domain socket
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s\n", SOCKET_PATH);

    while (1) {
        // Accept a client connection
        client_len = sizeof(struct sockaddr_un);
        client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
        if (client_sockfd == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("Client connected\n");

        // Receive data from the client
        ssize_t numBytes = read(client_sockfd, buffer, sizeof(buffer) - 1);
        if (numBytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[numBytes] = '\0';

        printf("Received from client: %s\n", buffer);

        // Process the client request (in this example, we just send back the received message)
        if (write(client_sockfd, buffer, strlen(buffer)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Close the client socket
        close(client_sockfd);
    }

    // Close the server socket
    close(sockfd);

    // Remove the socket file
    unlink(SOCKET_PATH);

    return 0;
}
