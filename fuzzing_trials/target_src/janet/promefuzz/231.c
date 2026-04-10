// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_scalloc at gc.c:725:7 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_scalloc at gc.c:725:7 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_srealloc(const uint8_t *Data, size_t Size) {
    void *mem = janet_scalloc(1, 10); // Allocate initial memory
    if (mem) {
        void *new_mem = janet_srealloc(mem, Size); // Reallocate with fuzz data size
        if (new_mem) {
            janet_srealloc(new_mem, 0); // Free the memory
        } else {
            janet_srealloc(mem, 0); // Free the original memory if reallocation failed
        }
    }
}

static void fuzz_janet_realloc(const uint8_t *Data, size_t Size) {
    void *ptr = janet_calloc(1, 10); // Allocate initial memory
    if (ptr) {
        void *new_ptr = janet_realloc(ptr, Size); // Reallocate with fuzz data size
        if (new_ptr && new_ptr != ptr) {
            janet_realloc(new_ptr, 0); // Free the new memory if reallocation succeeded
        } else if (new_ptr == ptr) {
            janet_realloc(ptr, 0); // Free the memory if reallocation did not move
        }
    }
}

static void fuzz_janet_scalloc(const uint8_t *Data, size_t Size) {
    size_t nmemb = Size > 0 ? Data[0] : 1;
    size_t elem_size = Size > 1 ? Data[1] : 1;
    void *mem = janet_scalloc(nmemb, elem_size);
    if (mem) {
        janet_srealloc(mem, 0); // Free the memory
    }
}

static void fuzz_janet_calloc(const uint8_t *Data, size_t Size) {
    size_t nmemb = Size > 0 ? Data[0] : 1;
    size_t elem_size = Size > 1 ? Data[1] : 1;
    void *mem = janet_calloc(nmemb, elem_size);
    if (mem) {
        janet_realloc(mem, 0); // Free the memory
    }
}

int LLVMFuzzerTestOneInput_231(const uint8_t *Data, size_t Size) {
    fuzz_janet_srealloc(Data, Size);
    fuzz_janet_realloc(Data, Size);
    fuzz_janet_scalloc(Data, Size);
    fuzz_janet_calloc(Data, Size);
    return 0;
}