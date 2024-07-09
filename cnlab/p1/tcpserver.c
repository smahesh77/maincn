#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() { // Corrected the function declaration of main

    int server, newsock;
    char buffer[1024];
    struct sockaddr_in servAddr;
    struct sockaddr_storage store;
    socklen_t addrSize;

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) { // Check if socket creation failed
        perror("Socket creation failed");
        return 1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Corrected the quotation marks

    if (bind(server, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) { // Check if binding failed
        perror("Binding failed");
        return 1;
    }

    if (listen(server, 5) < 0) { // Corrected the function name and added missing parenthesis
        perror("Listen failed");
        return 1;
    }

    printf("Listening...\n"); // Changed "Listening" to "Listening..."

    addrSize = sizeof(store);
    newsock = accept(server, (struct sockaddr *) &store, &addrSize);
    if (newsock < 0) { // Check if accept failed
        perror("Accept failed");
        return 1;
    }

    recv(newsock, buffer, 1024, 0);
    printf("2. Data received: %s\n", buffer); // Added a newline character

    strcpy(buffer, "Hi, This is server\n"); // Corrected the function name

    printf("3. Sending data to client...\n");
    send(newsock, buffer, strlen(buffer), 0); // Changed 19 to strlen(buffer)

    close(newsock);
    close(server);

    return 0; // Added return statement
}

