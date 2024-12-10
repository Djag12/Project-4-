#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Function to allocate and initialize a new list
list_t* list_alloc() {
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL) {
        fprintf(stderr, "Error allocating memory for list\n");
        exit(1);
    }
    list->head = NULL;
    return list;
}

// Function to get the length of the list
int list_length(list_t *list) {
    int length = 0;
    node_t *current = list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

// Function to add a value to the front of the list
void list_add_to_front(list_t *list, int value) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error allocating memory for node\n");
        exit(1);
    }
    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
}

// Function to add a value to the back of the list
void list_add_to_back(list_t *list, int value) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error allocating memory for node\n");
        exit(1);
    }
    new_node->value = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        node_t *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to add a value at a specific index
void list_add_at_index(list_t *list, int value, int index) {
    if (index < 0) {
        return;
    }

    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error allocating memory for node\n");
        exit(1);
    }
    new_node->value = value;

    if (index == 0) {
        new_node->next = list->head;
        list->head = new_node;
        return;
    }

    node_t *current = list->head;
    for (int i = 0; current != NULL && i < index - 1; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    new_node->next = current->next;
    current->next = new_node;
}

// Function to remove a value from the front of the list
int list_remove_from_front(list_t *list) {
    if (list->head == NULL) {
        fprintf(stderr, "Error: List is empty\n");
        return -1;
    }
    node_t *temp = list->head;
    int value = temp->value;
    list->head = list->head->next;
    free(temp);
    return value;
}

// Function to remove a value from the back of the list
int list_remove_from_back(list_t *list) {
    if (list->head == NULL) {
        fprintf(stderr, "Error: List is empty\n");
        return -1;
    }
    if (list->head->next == NULL) {
        int value = list->head->value;
        free(list->head);
        list->head = NULL;
        return value;
    }
    node_t *current = list->head;
    while (current->next && current->next->next) {
        current = current->next;
    }
    int value = current->next->value;
    free(current->next);
    current->next = NULL;
    return value;
}

// Function to remove a value at a specific index
int list_remove_at_index(list_t *list, int index) {
    if (index < 0 || list->head == NULL) {
        fprintf(stderr, "Error: Invalid index or empty list\n");
        return -1;
    }
    if (index == 0) {
        return list_remove_from_front(list);
    }

    node_t *current = list->head;
    for (int i = 0; current != NULL && i < index - 1; i++) {
        current = current->next;
    }
    if (current == NULL || current->next == NULL) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return -1;
    }
    node_t *temp = current->next;
    int value = temp->value;
    current->next = temp->next;
    free(temp);
    return value;
}

// Function to check if a value is in the list
int list_is_in(list_t *list, int value) {
    node_t *current = list->head;
    while (current != NULL) {
        if (current->value == value) {
            return 1;  // Found
        }
        current = current->next;
    }
    return 0;  // Not found
}

// Function to get the index of a value in the list
int list_get_index_of(list_t *list, int value) {
    node_t *current = list->head;
    int index = 0;
    while (current != NULL) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;  // Not found
}

// Function to get the element at a specific index
int list_get_elem_at(list_t *list, int index) {
    if (index < 0 || list->head == NULL) {
        fprintf(stderr, "Error: Invalid index or empty list\n");
        return -1;
    }

    node_t *current = list->head;
    for (int i = 0; current != NULL && i < index; i++) {
        current = current->next;
    }
    if (current == NULL) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return -1;
    }
    return current->value;
}

// Function to convert the list to a string representation
char* listToString(list_t *list) {
    static char buf[1024];
    buf[0] = '\0';  // Reset the buffer
    node_t *current = list->head;
    while (current != NULL) {
        char temp[64];
        snprintf(temp, sizeof(temp), "%d -> ", current->value);
        strcat(buf, temp);
        current = current->next;
    }
    strcat(buf, "NULL");
    return buf;
}

// Function to free the list and deallocate memory
void list_free(list_t *list) {
    node_t *current = list->head;
    while (current != NULL) {
        node_t *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
