#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_BUFFER_SIZE 516

// Function to create a TFTP WRQ packet 
void create_wrq_packet(char *packet, const char *filename) {
   t
}

// Function to perform TFTP upload
void perform_tftp_upload(const char *host, const char *filename) {
    // Get the server's address using getaddrinfo
    struct addrinfo hints, *server_info;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_DGRAM; 

    int status = getaddrinfo(host, "69", &hints, &server_info);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    // Iterate through the list of addresses and reserve a connection socket
    int sockfd = -1;
    for (struct addrinfo *p = server_info; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            perror("socket error");
            continue;
        }

        

        break; 
    }

    if (sockfd == -1) {
        fprintf(stderr, "Unable to reserve a connection socket.\n");
        freeaddrinfo(server_info);
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(server_info); 
    close(sockfd); 
}




int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s host file\n", argv[0]);
        return 1;  // Return an error code
    }

    const char *host = argv[1];
    const char *file_to_upload = argv[2];

    perform_tftp_upload(host, file_to_upload);

    return 0;  // Return success
}
