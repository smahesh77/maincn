#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() { // Corrected the function declaration of main
    int client;
    char buffer[1024];
    struct sockaddr_in servAddr;
    socklen_t addrSize;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) { // Check if socket creation failed
        perror("Socket creation failed");
        return 1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Corrected the struct member name

    if (connect(client, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) { // Check if connection failed
        perror("Connection failed");
        return 1;
    }

    printf("1. Sending data to server...\n"); // Corrected the newline character

    strcpy(buffer, "Hi This is client\n"); // Corrected the function name

    send(client, buffer, strlen(buffer), 0); // Changed 19 to strlen(buffer)

    recv(client, buffer, 1024, 0);
    printf("4. Data received: %s\n", buffer); // Added a newline character

    close(client);

    return 0;
}

