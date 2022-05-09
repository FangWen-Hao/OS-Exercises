#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _list_node_t {
    int iteration;
    struct _list_node_t *next;
} list_node_t;

typedef struct _list_t {
    list_node_t *head;
    list_node_t *tail;
    int length;
} list_t;

int alloc_list(list_t *list, int length) {
    list_node_t *local_list;

    assert(list != NULL && length >= 0);

    if (list == NULL || length < 0) {
        return 1;
    }

    list->length = length;

    if(length == 0) { // Empty list.
        list->head = NULL;
        list->tail = NULL;
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (i == 0) {
            list->head = calloc(1, sizeof(list_node_t));
            if (list->head == NULL)
                return 2;
            local_list = list->head;
        } else {
            local_list->next = calloc(1, sizeof(list_node_t));
            if (local_list->next == NULL)
                return 2;
            local_list = local_list->next;
        }
    }

    list->tail = local_list;

    return 0;
}

int free_list1(list_t *list) {

    assert(list != NULL);

    if (list == NULL) {
        return 1;
    }

    if (list->head == NULL)
        return 0; // Empty list.

    for(list_node_t *local_list = list->head, *tn2 = list->head->next; local_list != NULL; ) {
        free(local_list);
        local_list = tn2;
        if (tn2 != NULL)
            tn2 = tn2->next;
    }

    return 0;
}


int free_list2(list_t *list) {
    list_node_t *n0, *n1;

    assert(list != NULL);

    if (list == NULL) {
        return 1;
    }

    if (list->head == NULL)
        return 0; // Empty list.

    n0 = list->head;
    n1 = n0->next;

    while(n0 != NULL) {
        free(n0);

        n0 = n1;

        if(n1 != NULL) {
            n1 = n1->next;
        }
    }

    return 0;
}

int init_list(list_t *list, int *e, int elen) {
    int i;
    list_node_t *n;
    // head = stack bottom = LRU page. = e[0].
    // tail = stack top = MRU page. = e[elen-1].

    assert(list != NULL && e != NULL && elen > 0 && list->length == elen);

    if (list == NULL || e == NULL || elen <= 0 || list->length != elen) {
        return 1;
    }

    for(i = 0, n = list->head; i < elen && n != NULL; i++, n = n->next) {
        n->iteration = e[i];
    }

    return 0;
}

int contained_by_list(list_t *list, int expected_result) {
    // If e occurs more than once, the search terminates when the first occurrence is found.
    list_node_t *n;


    assert(list != NULL);

    if(list == NULL) {
        return -1;
    }

    if(list->length == 0) { // Empty list.
        return 0;
    }

    n = list->head;

    while (n != NULL) {
        if(n->iteration == expected_result)
            return 1; // found!
        n = n->next;
    }

    return 0; // Not in list!
}

int remove_node_from_list(list_t *list, int e, list_node_t **removed_node) {
    // Searches for the first node with entry e, removes it from the list if found, the removed node is returned to the called in *removed_node. If not found *removed_node = NULL.
    // Returns 0 if the e is not in the list. Returns 1 if e is found. Other values indicate an error occurred.
    list_node_t *b, *n, *a;

    assert(list != NULL && removed_node != NULL);

    if (list == NULL || removed_node == NULL) {
        return -1;
    }

    if(list->length == 0) { // Empty list.
        *removed_node = NULL;
        return 0;
    }

    /*
        3 cases:
            Head removal
            Tail removal
            Middle removal
    */

    b = NULL;
    n = list->head;

    while(n != NULL) {
        if(n->iteration == e) {
            break;
        }

        b = n;
        n = n->next;
    }

    if(n == NULL) { // e is not in the list.
        *removed_node = NULL;
        return 0;
    }

    *removed_node = n; // Return removed node.
    list->length--; // Removing 1 node.

    if(list->length == 0) { // Removing the only node in the list.
        assert(list->head == list->tail);
        list->head = NULL;
        list->tail = NULL;
        return 1;
    }

    a = n->next; // node after the node being removed.

    if(n == list->head) { // head removal
        list->head = a; // new head is the node after the current head.
        n->next = NULL; // unlink node being removed.
        return 1;
    }

    if(n == list->tail) { // tail removal
        list->tail = b; // new tail is node before the node being removed.
        list->tail->next = NULL; // Tail next must be marked NULL.
        return 1;
    }

    // middle removal
    assert(b != NULL && a != NULL);
    b->next = a;
    n->next = NULL;

    return 1;

//  list->length-- ; if found e and removed it. ++ inside add_head_to_list/tail/at().
}

int add_tail_to_list(list_t *list, list_node_t *node) {
    assert(list != NULL && node != NULL);

    if(list == NULL || node == NULL) {
        return -1;
    }

    node->next = NULL; // Tail next must be marked NULL.
    list->length++;
    if(list->length == 1) { // first node being added to the list
        list->head = node;
        list->tail = node;
        return 0;
    }

    list->tail->next = node;
    list->tail = node;

    return 0;
}

int add_head_to_list(list_t *list, list_node_t *node) {
    assert(list != NULL && node != NULL);

    if(list == NULL || node == NULL) {
        return -1;
    }

    list->length++;

    if(list->length == 1) { // first node being added to the list
        list->head = node;
        list->tail = node;
        node->next = NULL; // Tail next must be marked NULL.
        return 0;
    }

    node->next = list->head;
    list->head = node;
    return 0;
}

int print_list(list_t *list) {
    list_node_t *node;

    if(list == NULL) {
        printf("list NULL!\n");
        return 1;
    }

    if(list->head == NULL || list->length == 0){
        printf("list empty!\n");
        return 2;
    }

    node = list->head;

    while(node != NULL) {
        printf("%d->", node->iteration);
        node = node->next;
    }

    printf("\n");

    return 0;
}
