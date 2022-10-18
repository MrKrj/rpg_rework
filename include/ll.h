
#ifndef LINKED_LIST_H
    #define LINKED_LIST_H

    #include <stdbool.h>
    #include <stddef.h>

typedef unsigned int uint_t;

typedef enum type_e {
    INTEGER,
    CHAR,
    STR,
    DOUBLE
} type_t;

typedef struct node_s {
    type_t type;
    void *data;
    struct node_s *prev;
    struct node_s *next;
} node_t;

// Get size list
uint_t L_size(node_t *);

// Get empty boolean
bool L_empty(node_t *);

// Display all nodes from list
void L_display(node_t *);

// Delete & free node
void L_delete(node_t *);

// Delete & free all nodes from list
void L_clear(node_t **);

// Add node to end of list & return new node
node_t *L_push_back(node_t **, type_t, ...);

// Add node to begin of list & return new node
node_t *L_push_front(node_t**, type_t, ...);

// Delete & return last node from list (not freed)
node_t *L_pop_back(node_t **);

// Delete & return first node from list (not freed)
node_t *L_pop_front(node_t **);

// Delete & free first node from list
void L_erase_front(node_t **);

// Delete & free last node from list
void L_erase_back(node_t **);

// Get first node from list
node_t *L_begin(node_t *);

// Get last node from list
node_t *L_end(node_t *);

// Get int data
int L_int(node_t *);

// Get double data
double L_double(node_t *);

// Get char data
char L_char(node_t *);

// Get str data
char *L_str(node_t *);



#endif /* LINKED_LIST_H */