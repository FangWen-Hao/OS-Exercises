/*!
    @header Page Replacement Algorithms
    Functions that implement the LRU, FIFO and OPT page replacement.
*/
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "arr.h"
#include "queue.h"

/*!
    @function lruAlgorithm

    @discussion Returns the number of page faults that would occur with the LRU
    page replacement algorithm applied to the given reference string rs and npf
    number of page frames.

    @param len_rs    The length of the reference string rs.

    @param rs    The reference string to use.

    @param npf    The number of page frames to use.

    @result Greater than 0 if successful. Otherwise an error occurred.
    Note that 0 is not a valid number of page faults, all algorithms
    must page fault to fill their empty page frames.
*/

int lruAlgorithm(const int len_rs, const int * const rs, const int npf) {
    int n_free_pf = npf;
    int i = 0;
    int page_num;
    int num_page_faults = 0;
    list_t l;
    list_node_t *n = NULL;

    alloc_list(&l, 0);

    while (i < len_rs) {
        page_num = rs[i];
        i++;

        if(contained_by_list(&l, page_num) == 1) {
            // Page in memory - update MRU page.
            if(remove_node_from_list(&l, page_num, &n) == 1)
                assert(add_tail_to_list(&l, n) == 0);
            else
                assert(0); // Should be in list - we just checked.
        } else {
            // Page not in memory - page fault
            num_page_faults++;

            if(n_free_pf-- > 0) {
                // Place page in a free frame - make it the MRU
                n = calloc(1, sizeof(list_node_t));
                assert(n != NULL);
                n->iteration = page_num;
                assert(add_tail_to_list(&l, n) == 0);
            } else {
                // Replace LRU page with page just referenced.

                assert(l.length > 0); // We should have a least one page frame

                if(remove_node_from_list(&l, l.head->iteration, &n) == 1) { // Remove head = LRU page.
                    n->iteration = page_num;
                    assert(add_tail_to_list(&l, n) == 0);
                } else
                    assert(0);
            }

        }
    }

    free_list2(&l);

    return num_page_faults;
}

/*!
    @function optAlgorithmHelper

    @discussion Replaces one of the pages in the page_frames array with the new
    page being brought into memory, which is page_num. rs is the remaining part
    of the reference string, excluding page_num, len_rs is the length of rs. If
    successful, one of the pages in page_frames will have been replaced
    (overwritten) with page_num.

    @field page_frames    The array of page frames representing the pages that
                          are currently in memory.

    @field rs    The remaining unprocessed part of the reference string,
                 excluding page_num. A reference string represents the memory
                 accesses against which a page replacement algorithm is tested.

    @field len_rs    The length of the rs array.

    @field page_num  The page number which caused the most recent page fault and
                     is being brought into memory via page replacement.

    @result 0 if successful. Other values indicate error.
*/
static int optAlgorithmHelper(custom_arr *page_frames, const int * const rs, const int len_rs, const int page_num) {
    /* ffnr = furthest future next reference. Current index into
       page_frames->arr of the page to be replaced. */
    int ffnr_i = -1;
    /* ffnr = furthest future next reference. Current index into rs of the page
       to be replaced. This index can be thought of as how far into the future
       page number rs[ffnr_j] will be referenced. */
    int ffnr_j = -1;
    int i, j;

    if (page_frames == NULL || page_frames->arr == NULL || page_frames->num_entries <= 0) {
        assert(0);
        return 1;
    }

    if (rs == NULL || len_rs < 0) {
        assert(0);
        return 2;
    }

    for(i = 0; i < page_frames->num_entries; i++) {
        for(j = 0; j < len_rs; j++) {
            if(page_frames->arr[i] == rs[j])
                break;
        }

        if(j == len_rs) {
            /* Page is never referenced again, we can end the search early and
               replace this page. */
            page_frames->arr[i] = page_num; // Replace
            return 0;
        } else {
            if(j > ffnr_j) {
                /* This page is referenced further into the future, update the
                   candidate replacement page. */
                ffnr_j = j;
                ffnr_i = i;
            }
        }
    }

    // Sanity check - we should always find a page to replace.

    if (ffnr_i < 0 || ffnr_j < 0) {
        assert(0);
        return 3;
    }

    // Replace the page.
    page_frames->arr[ffnr_i] = page_num;

    return 0;
}

/*!
    @function optAlgorithm

    @discussion Returns the number of page faults that would occur with the OPT
    page replacement algorithm applied to the given reference string rs and npf
    number of page frames.

    @param len_rs    The length of the reference string rs.

    @param rs    The reference string to use.

    @param npf    The number of page frames to use.

    @result Greater than 0 if successful. Otherwise an error occurred.
    Note that 0 is not a valid number of page faults, all algorithms
    must page fault to fill their empty page frames.
*/
int optAlgorithm(const int len_rs, const int * const rs, const int npf) {
    int free_npf = npf;
    int i = 0;
    int page_num;
    int num_page_faults = 0;
    custom_arr page_frames;
    int tr;

    if (len_rs <= 0 || rs == NULL || npf <= 0) {
        assert(0);
        return -1;
    }

    tr = allocate_arr(&page_frames, npf);

    if (tr) {
        assert(0);
        return -2;
    }

    while(i < len_rs) {
        page_num = rs[i];
        i++;

        tr = search_arr(&page_frames, page_num);

        if(tr == 1) {
            // Page is in memory
            ;
        } else if (tr == 0) {
            // Page is not in memory
            num_page_faults++;

            if (free_npf-- > 0) {
                // Use free frame to service page fault
                tr = add_to_arr(&page_frames, page_num);
                if(tr) {
                    // add_to_arr() error
                    assert(0);
                    num_page_faults = -5;
                    break;
                }
            } else {
                // Page replacement required
                tr = optAlgorithmHelper(&page_frames, &rs[i], len_rs - i, page_num);

                if (tr) {
                    // optAlgorithmHelper() error
                    assert(0);
                    num_page_faults = -6;
                    break;
                }
            }

        } else {
            // search_arr() error.
            assert(0);
            num_page_faults = -3;
            break;
        }
    }

    tr = malloc_arr(&page_frames);

    if(tr) {
        assert(0);
        num_page_faults = -4;
    }

    return num_page_faults;
}

/*!

    @function fifoAlgorithm

    @discussion Returns the number of page faults that would occur with the FIFO
    page replacement algorithm applied to the given reference string rs and npf
    number of page frames.

    @param len_rs    The length of the reference string rs.

    @param rs    The reference string to use.

    @param npf    The number of page frames to use.

    @result Greater than 0 if successful. Otherwise an error occurred.
    Note that 0 is not a valid number of page faults, all algorithms
    must page fault to fill their empty page frames.

*/
int fifoAlgorithm(const int len_rs, const int * const rs, const int npf) {
    int free_npf = npf;
    int i = 0;
    int page_num;
    int num_page_faults = 0;
    queue_t page_frames;
    int tr;

    if (len_rs <= 0 || rs == NULL || npf <= 0) {
        assert(0);
        return -1;
    }

    tr = queue_alloc(&page_frames, npf);

    if(tr) {
        assert(0);
        return -2;
    }

    while(i < len_rs) {
        page_num = rs[i];
        i++;

        tr = queue_contains(&page_frames, page_num);

        if(tr == 1) {
            // Page is in memory
            ;
        } else if (tr == 0) {
            // Page is not in memory - page fault!
            num_page_faults++;
            if(free_npf-- > 0) {
                // Service page fault with a free frame
                tr = enqueue(&page_frames, page_num);
                if(tr) {
                    // enqueue() error
                    assert(0);
                    num_page_faults = -4;
                    break;
                }
            } else {
                // Replace the page at the front of the queue
                tr = dequeue(&page_frames, &tr);
                if(tr) {
                    assert(0);
                    num_page_faults = -5;
                    break;
                }

                tr = enqueue(&page_frames, page_num);
                if(tr) {
                    assert(0);
                    num_page_faults = -6;
                    break;
                }
            }
        } else {
            // queue_contains error.
            assert(0);
            num_page_faults = -3;
            break;
        }
    }

    tr = queue_free(&page_frames);

    if(tr) {
        assert(0);
        num_page_faults = -7;
    }

    return num_page_faults;
}
