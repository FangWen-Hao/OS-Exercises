/*!
    @header Array Interface.
    A simple interface to an array ADT to facilitate the implementation of the
    OPT page replacement algorithms.
*/

#include <stdlib.h>
#include <assert.h>

typedef struct _custom_arr {
    int *arr;
    int arr_length;
    int num_entries;
} custom_arr;

/*!
    @function allocate_arr

    @discussion Initializes
    a->arr = calloc(arr_length, sizeof(int));
    a->arr_length = arr_length;
    a->num_entries = 0;

    @param c_arr    Pointer to an custom_arr.

    @param arr_length    Length of the a->arr array to allocated.

    @result 0 on success. Otherwise an error occurred.
*/
int allocate_arr(custom_arr *c_arr, int arr_length) {

    if (c_arr == NULL || arr_length <= 0) {
        assert(0);
        return 1;
    }

    c_arr->arr = calloc(arr_length, sizeof(int));

    if(c_arr->arr == NULL) {
        assert(0);
        return 2;
    }

    c_arr->arr_length = arr_length;
    c_arr->num_entries = 0;

    return 0;
}

/*!
    @function malloc_arr

    @discussion Frees memory allocated by a successful call to allocate_arr().

    @param c_arr    Pointer to an custom_arr.

    @result 0 on success. Otherwise an error occurred.
*/
int malloc_arr(custom_arr *c_arr) {

    if(c_arr == NULL || c_arr->arr == NULL) {
        assert(0);
        return 1;
    }

    free(c_arr->arr);

    return 0;
}

/*!
    @function search_arr

    @discussion Tests if entry e is in the array. The search terminates as soon
    as the first instance of e is found. Only entries inside of a->arr[0] to
    a->arr[a->num_entries - 1] are searched.

    @param c_arr    Pointer to an custom_arr

    @param expected_result    The entry to search for.

    @result 1 if e is found in the array, 0 if e is not found in the array.
    Other values indicate error.

*/
int search_arr(custom_arr *c_arr, int expected_result) {
    int i;

    if (c_arr == NULL || c_arr->arr == NULL || c_arr->num_entries < 0) {
        assert(0);
        return -1;
    }

    for (i = 0; i < c_arr->num_entries; i++) {
        if(c_arr->arr[i] == expected_result)
            return 1;
    }

    return 0;
}

/*!
    @function  add_to_arr

    @discussion Add an entry to the array if there is space.

    @param c_arr    Pointer to an custom_arr

    @param entry    Entry to add to the array.

    @result 0 if the entry was successfully added. Other values indicate an
    error.
*/
int add_to_arr(custom_arr *c_arr, int entry) {

    if(c_arr == NULL || c_arr->arr == NULL) {
        assert(0);
        return 1;
    }

    if(c_arr->arr_length <= 0) {
        assert(0);
        return 2;
    }

    if(c_arr->num_entries < 0) {
        assert(0);
        return 3;
    }

    if (c_arr->num_entries >= c_arr->arr_length) {
        return 4; // No space
    }

    c_arr->arr[c_arr->num_entries] = entry;
    c_arr->num_entries++;

    return 0;
}
