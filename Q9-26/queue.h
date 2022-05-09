/*!
    @header Array based queue
    An interface to array based queue.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _queue_t {
    int headi;
    int taili;
    int *queue_arr;
    int arr_length;
    int num_entries;
} queue_t;

/*!
    @function queue_alloc

    @discussion Initializes a queue supporting a maximum of queueLength entries.

    @param queue    Pointer to a queue_t

    @param queueLength    Desired max. number of queue entries.

    @result 0 on success. Other values indicate error.
*/
int queue_alloc(queue_t *queue, int queueLength) {

    if (queue == NULL || queueLength <= 0) {
        assert(0);
        return 1;
    }

    queue->headi = 0;
    queue->taili = 0;
    /*
        queueLength + 1 allows us to distinguish between empty and full queue in an
        array based queue implementation.
    */
    queue->arr_length = queueLength + 1;

    queue->queue_arr = calloc(queue->arr_length, sizeof(int));

    if (queue->queue_arr == NULL) {
        assert(0);
        return 2;
    }

    queue->num_entries = 0;

    return 0;
}

/*!

    @function queue_free

    @discussion The complement of queue_alloc().

    @param queue    Pointer to a queue_t that was previously initialized with
                queue_alloc(). Call this function when you are done using the
                queue.

    @result 0 on success. Other values indicate error.
*/
int queue_free(queue_t *queue) {

    if (queue == NULL || queue->queue_arr == NULL) {
        assert(0);
        return 1;
    }

    free(queue->queue_arr);

    return 0;
}

/*!
    @function queue_is_full

    @discussion Tests if the queue is full.

    @param queue    Pointer to a queue_t that was previously initialized with
                queue_alloc().

    @result Otherwise Returns 1 if the queue is full, returns 0 if it is not
            full. Other values indicate error.

*/
int queue_is_full(queue_t *queue) {

    if (queue == NULL || queue->taili < 0 || queue->headi < 0 || queue->arr_length < 0) {
        assert(0);
        return -1;
    }

    return (queue->taili + 1) % queue->arr_length == queue->headi;
}

/*!
    @function enqueue

    @discussion Enqueues the given entry to the tail queue.

    @param queue    Pointer to a queue_t that was previously initialized with
                queue_alloc().
    @param entry    The entry being added.

    @result 0 on success. Other values indicate an error.
*/
int enqueue(queue_t *queue, int entry) {
    int r;

    if (queue == NULL || queue->queue_arr == NULL) {
        assert(0);
        return 1;
    }

    r = queue_is_full(queue);

    if (r != 0 && r != 1) {
        // queue_is_full() error.
        assert(0);
        return 2;
    }

    if (r == 1) {
        // queue is full.
        return 3;
    }

    // queue is not full, add the entry.
    queue->queue_arr[queue->taili] = entry;

    queue->taili = (queue->taili + 1) % queue->arr_length;

    if (queue->num_entries >= queue->arr_length - 1) {
        // Invalid/unexpected number of entries
        assert(0);
        return 4;
    }

    queue->num_entries++;

    return 0;
}

/*!
    @function queue_is_empty

    @discussion Tests if the queue is empty.

    @param queue    Pointer to a queue_t that was previously initialized with
                queue_alloc().

    @result Returns 1 if the queue is empty, returns 0 if it is not empty. Other
            values indicate error.

*/
int queue_is_empty(queue_t *queue) {

    if (queue == NULL || queue->taili < 0 || queue->headi < 0 || queue->arr_length < 0) {
        assert(0);
        return -1;
    }

    return queue->headi == queue->taili;
}

/*!
    @function dequeue

    @discussion Dequeues an entry from the head of the queue.

    @param queue    Pointer to a queue_t that was previously initialized with
                queue_alloc().
    @param entry    Pointer in which to return the dequeued entry if the queue is
                not empty. The pointer is not touched if the queue is empty or
                if an error occurs.

    @result 0 on success. Other values indicate an error.
*/
int dequeue(queue_t *queue, int *entry) {
    int r;

    if (queue == NULL || queue->queue_arr == NULL || entry == NULL) {
        assert(0);
        return 1;
    }

    r = queue_is_empty(queue);

    if (r != 0 && r != 1) {
        // queue_is_empty() error
        assert(0);
        return 2;
    }

    if (r == 1) {
        // queue is empty, nothing to return
        return 3;
    }

    if (queue->num_entries <= 0) {
        // Invalid / unexpected number of entries
        assert(0);
        return 4;
    }

    *entry = queue->queue_arr[queue->headi];

    queue->queue_arr[queue->headi] = -1; // helpful for debugging

    queue->headi = (queue->headi + 1) % queue->arr_length;

    queue->num_entries--;

    return 0;
}

/*!
    @function queue_contains

    @discussion Tests if the queue contains the given entry.

    @param queue    Pointer to a queue_t that was previously initialized with
                queue_alloc().
    @param entry    The entry to search for.

    @result Returns 1 if the entry is in the queue, returns 0 of the entry is
    not in the queue or if the queue is empty. All other values indicate an
    error.

*/
int queue_contains(queue_t *queue, int entry) {
    int i = 0;
    int t, r;

    if (queue == NULL || queue->queue_arr == NULL) {
        return -1;
    }

    r = queue_is_empty(queue);

    if(r != 0 && r != 1) {
        // queue_is_empty() error
        assert(0);
        return -2;
    }

    if(r == 1) {
        // Queue is empty
        return 0;
    }

    for(i = 0; i < queue->num_entries; i++) {
        t = (queue->headi + i) % queue->arr_length;
        if(queue->queue_arr[t] == entry)
            return 1;
    }

    return 0;
}
