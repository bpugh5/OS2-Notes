#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    int struct node *next;
};

head == NULL;
T1's next -> NULL
T1's value == 1
T2's next -> NULL
T2's value == 2

head -> (2) -> NULL

head -> (1) -> NULL

void llist_insert(struct node **head, int value) {
    struct node *new = malloc(sizeof(struct node));
    new->value = value;

          (T1 new)
             v
    head -> (3) -> (4) -> NULL
             ^
          (T2 new)

    lock();

    new->next = *head;    T1  // could be interrupted here and cause a node to vanish (both point to NULL head)
    *head = new;   T2

    unlock();
}

int llist_delete(struct node **head) {

    lock();

    struct node *old_head = *head;
    *head = old_head->next;

    unlock();
    
    int value = old_head->value;
    free(old_head);
    
    return value;
}

struct node *llist_find(struct node *head, int value) {
    
    lock();

    while (head != NULL) {
        if (head->value == value) {
            return_value = head;
            break;
        }
        head = head->next;
    }

    unlock();
    return return_value;
}

void llist_print(struct node *head) {
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }

    putchar('\n');
}

