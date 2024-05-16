/* Arena memory allocator and utilities
 * See https://nullprogram.com/blog/2023/09/27/
 *
 * Usage:
 * Common to create scratch and also permenant arena based on different
 * lifetimes. Pass by reference if want to keep results. Pass by copy if
 * want to clear arena when fn returns (does not copy contents).
 * see examples.
 */

#pragma once

#include <stddef.h>

#define sizeof(x)    (ptrdiff_t)sizeof(x)
#define countof(a)   (sizeof(a) / sizeof(*(a)))

typedef struct Arena {
    char* beg;
    char* end;
} Arena;

Arena ar_create(ptrdiff_t cap); // Create and return new arena

/*
 * Allocate memory in arena for a specific type and count
 * usage: ar_new(&Arena, type, optional count)
 */
#define ar_new(...)            ar_newx(__VA_ARGS__,ar_new4,ar_new3,ar_new2)(__VA_ARGS__)
#define ar_newx(a,b,c,d,e,...) e
#define ar_new2(a, t)          (t *)alloc(a, sizeof(t), alignof(t), 1)
#define ar_new3(a, t, n)       (t *)alloc(a, sizeof(t), alignof(t), n)

char* ar_alloc(Arena* a, size_t size); // general allocator like malloc
void* ar_copy(Arena* a, void* src, size_t size); // copy memory into arena
char* ar_str_copy(Arena* a, char* c); // copy null terminated string into arena

// Implementation
void* alloc(Arena* a, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count);
