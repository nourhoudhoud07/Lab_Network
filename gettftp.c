#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUFFER_SIZE 516

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void receiveFile(int sockfd, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        error("Error opening file for writing");
    }

    while (1) {
        char buffer[MAX_BUFFER_SIZE];
        int bytes_received = recv(sockfd, buffer, MAX_BUFFER_SIZE, 0);
        if (bytes_received < 0) {
            error("Error receiving data");
        } else if (bytes_received == 0) {
            break;  // End of file
        }

        fwrite(buffer, 1, bytes_received, file);

        if (bytes_received < MAX_BUFFER_SIZE) {
            break;  // Last block received
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <filename>\n", argv[0]);
        exit(1);
    }

    const char *host = argv[1];
    const char *filename = argv[2];

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(69);
    server_addr.sin_addr.s_addr = inet_addr(host);

    sendto(sockfd, "get", 3, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    receiveFile(sockfd, filename);

    close(sockfd);
    return 0;
}
