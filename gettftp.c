#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_BUFFER_SIZE 516

// Function to create a TFTP RRQ packet 
void create_rrq_packet(char *packet, const char *filename) {
    
    packet[0] = 0x00;
    packet[1] = 0x01;
    strcpy(&packet[2], filename);
    strcpy(&packet[2 + strlen(filename) + 1], "octet");
}

// Function to perform TFTP download
void perform_tftp_download(const char *host, const char *filename) {
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

        // Build RRQ packet
        char rrq_packet[MAX_BUFFER_SIZE];
        create_rrq_packet(rrq_packet, filename);
			
        // Send RRQ packet to the server
        ssize_t bytes_sent = sendto(sockfd, rrq_packet, strlen(rrq_packet), 0, p->ai_addr, p->ai_addrlen);
        if (bytes_sent == -1) {
            perror("sendto error");
            close(sockfd);
            freeaddrinfo(server_info);
            exit(EXIT_FAILURE);
        }

        break;
    }

    // Add logic to receive and handle Data (DAT) packets and their acknowledgments (ACK)
    // ...

    freeaddrinfo(server_info); 
    close(sockfd); 
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s host file\n", argv[0]);
        return 1;  
    }

    const char *host = argv[1];
    const char *file_to_download = argv[2];

    perform_tftp_download(host, file_to_download);

    return 0;  
}
