// a simple recursive version of quick sort

#include <stdio.h>

// byte wise swap two elements
#define SWAP(a, b, size)       \
    do {                       \
        size_t tsize = size;   \
        char *pa = a, *pb = b; \
        do {                   \
            char tmp = *pa;    \
            *pa++ = *pb;       \
            *pb++ = tmp;       \
        } while (--tsize > 0); \
    } while (0);

typedef int cmp_t(const void *, const void *);

// in-place partition
char *partition(char *lo, char *hi, char *pivot, size_t size, cmp_t cmp) {
    SWAP(pivot, hi, size);
    char *index = lo;
    for (char *itr = lo; itr != hi; itr += size) {
        if (cmp(itr, (void *)hi) < 0) {
            SWAP(index, itr, size);
            index += size;
        }
    }
    SWAP(hi, index, size);
    return index;
}

void quick_sort(void *const pbase, size_t tot_elem, size_t size, cmp_t cmp) {
    if (tot_elem <= 0) return;
    char *base_ptr = (char *)pbase;
    char *lo = base_ptr;
    char *hi = &lo[(tot_elem - 1) * size];
    char *pivot = lo + size * (((hi - lo) / size) >> 1);
    char *new_pivot = partition(lo, hi, pivot, size, cmp);
    quick_sort(base_ptr, (new_pivot - lo) / size, size, cmp);
    quick_sort(new_pivot + size, (hi - new_pivot) / size, size, cmp);
}