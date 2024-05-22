/* Arena memory allocator
 * See https://nullprogram.com/blog/2023/09/27/
 *
 * Usage:
 * Common to create scratch and also permenant arena based on different
 * lifetimes. Pass by reference if want to keep results. Pass by copy if
 * want to clear arena when fn returns (does not copy contents).
 * see examples.
 */

#include "arena.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Allocate a new arena of capacity `cap`
 * the returned arena structure is trivial to copy and does not include
 * the data. 
 */
Arena ar_create(ptrdiff_t cap)
{
    Arena a = {0};
    a.beg = malloc(cap);
    a.end = a.beg ? a.beg+cap : 0;
    return a;
}

/*
 * Allocate memory in arena
 */
__attribute((malloc, alloc_size(2, 4), alloc_align(3)))
void* alloc(Arena* a, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count)
{
    ptrdiff_t padding = -(uintptr_t)a->beg & (align - 1);
    ptrdiff_t available = a->end - a->beg - padding;
    if (available < 0 || count > available/size) {
        abort();  // one possible out-of-memory policy
    }
    void* p = a->beg + padding;
    a->beg += padding + count*size;
    return memset(p, 0, count*size);
}

/*
 * General allocation in arena like malloc
 */
char* ar_alloc(Arena* a, size_t size)
{
    return ar_new(a, char, size);
}

/*
 * Copy src to arena
 */
void* ar_copy(Arena* a, void* src, size_t size)
{
    char* s = ar_new(a, char, size);
    memcpy(s, src, size);
    return s;
}

/*
 * Copy null terminated string (char *) into the arena
 */
char* ar_strcopy(Arena* a, char* c)
{
    return ar_copy(a, c, strlen(c) + 1);
}

