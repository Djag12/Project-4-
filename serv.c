#include <netinet/in.h> // structure for storing address information 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <sys/socket.h> // for socket APIs 
#include <sys/types.h> 
#include "list.h"

#define PORT 9001
#define ACK "ACK"

int main(int argc, char const* argv[]) 
{ 
    int n, val, idx;
    // create server socket 
    int servSockD = socket(AF_INET, SOCK_STREAM, 0); 
    if (servSockD < 0) {
        perror("Socket creation failed");
        exit(1);
    }
  
    // string buffer to store data sent to/from client 
    char buf[1024];
    char sbuf[1024];
    char* token;

    // define server address 
    struct sockaddr_in servAddr; 
    servAddr.sin_family = AF_INET; 
    servAddr.sin_port = htons(PORT); 
    servAddr.sin_addr.s_addr = INADDR_ANY; 
  
    // bind socket to the specified IP and port 
    if (bind(servSockD, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Bind failed");
        exit(1);
    }
  
    // listen for connections 
    if (listen(servSockD, 1) < 0) {
        perror("Listen failed");
        exit(1);
    }
  
    // accept client connection 
    int clientSocket = accept(servSockD, NULL, NULL); 
    if (clientSocket < 0) {
        perror("Accept failed");
        exit(1);
    }
    printf("Client connected successfully!\n");

    // create an empty list 
    list_t *mylist = list_alloc();  

    while (1) {
        // receive messages from client socket 
        n = recv(clientSocket, buf, sizeof(buf), 0);
        buf[n] = '\0';

        if (n > 0) {
            printf("Received command: %s\n", buf);  // Debugging: print received command
            token = strtok(buf, " ");

            if (strcmp(token, "exit") == 0) {
                list_free(mylist);
                printf("Exiting server...\n");
                exit(1);
            }
            else if (strcmp(token, "get_length") == 0) {
                val = list_length(mylist);
                sprintf(sbuf, "Length = %d", val);
            }
            else if (strcmp(token, "add_front") == 0) {
                token = strtok(NULL, " ");  // get value
                val = atoi(token);
                list_add_to_front(mylist, val);
                printf("After add_front: %s\n", listToString(mylist));  // Debugging
                sprintf(sbuf, "%s%d", ACK, val);
            }
            else if (strcmp(token, "add_back") == 0) {
                token = strtok(NULL, " ");  // get value
                val = atoi(token);
                list_add_to_back(mylist, val);
                printf("After add_back: %s\n", listToString(mylist));  // Debugging
                sprintf(sbuf, "%s%d", ACK, val);
            }
            else if (strcmp(token, "add_at_index") == 0) {
                token = strtok(NULL, " ");  // get index
                idx = atoi(token);
                token = strtok(NULL, " ");  // get value
                val = atoi(token);
                list_add_at_index(mylist, val, idx);
                printf("After add_at_index: %s\n", listToString(mylist));  // Debugging
                sprintf(sbuf, "%s%d at index %d", ACK, val, idx);
            }
            else if (strcmp(token, "remove_last") == 0) {
                val = list_remove_from_back(mylist);
                printf("After remove_last: %s\n", listToString(mylist));  // Debugging
                sprintf(sbuf, "%s%d", ACK, val);
            }
            else if (strcmp(token, "remove_first") == 0) {
                val = list_remove_from_front(mylist);
                printf("After remove_first: %s\n", listToString(mylist));  // Debugging
                sprintf(sbuf, "%s%d", ACK, val);
            }
            else if (strcmp(token, "remove_position") == 0) {
                token = strtok(NULL, " ");  // get index
                idx = atoi(token);
                val = list_remove_at_index(mylist, idx);
                printf("After remove_position: %s\n", listToString(mylist));  // Debugging
                sprintf(sbuf, "%s%d", ACK, val);
            }
            else if (strcmp(token, "contains") == 0) {
                token = strtok(NULL, " ");  // get value
                val = atoi(token);
                int result = list_is_in(mylist, val);
                sprintf(sbuf, "%s%d: %s", "Contains ", val, result ? "YES" : "NO");
            }
            else if (strcmp(token, "get_element") == 0) {
                token = strtok(NULL, " ");  // get index
                idx = atoi(token);
                val = list_get_elem_at(mylist, idx);
                sprintf(sbuf, "Element at index %d = %d", idx, val);
            }
            else if (strcmp(token, "get_index") == 0) {
                token = strtok(NULL, " ");  // get value
                val = atoi(token);
                idx = list_get_index_of(mylist, val);
                sprintf(sbuf, "Index of %d = %d", val, idx);
            }
            else if (strcmp(token, "to_string") == 0) {
                sprintf(sbuf, "List: %s", listToString(mylist));
            }
            else if (strcmp(token, "print") == 0) {
                sprintf(sbuf, "List: %s", listToString(mylist));
            }

            // send message to client socket 
            send(clientSocket, sbuf, sizeof(sbuf), 0);
        }
        memset(buf, '\0', 1024);
    }
  
    return 0; 
}
