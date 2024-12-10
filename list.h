#ifndef LIST_H
#define LIST_H

typedef struct node {
    int value;
    struct node *next;
} node_t;

typedef struct {
    node_t *head;
} list_t;

// Function prototypes
list_t* list_alloc();
int list_length(list_t *list);
void list_add_to_front(list_t *list, int value);
void list_add_to_back(list_t *list, int value);
void list_add_at_index(list_t *list, int value, int index);  // Add to specific index
int list_remove_from_front(list_t *list);
int list_remove_from_back(list_t *list);
int list_remove_at_index(list_t *list, int index);
int list_is_in(list_t *list, int value);  // Check if value is in list
int list_get_index_of(list_t *list, int value);  // Get index of value
int list_get_elem_at(list_t *list, int index);
char* list_to_string(list_t *list);
char* listToString(list_t *list);  // Convert list to string
void list_free(list_t *list);

#endif // LIST_H