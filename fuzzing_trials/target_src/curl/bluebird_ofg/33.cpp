#include <stdint.h>
#include <stddef.h>
#include <string.h> // For strlen, memcpy
#include <stdlib.h> // For malloc, free, realloc, calloc
#include "curl/curl.h"

extern "C" {

// Custom memory allocation functions
void* my_malloc(size_t size) {
    return malloc(size);
}

void my_free(void* ptr) {
    free(ptr);
}

void* my_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}

char* my_strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

void* my_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    long flags = (size > 0) ? data[0] : 0; // Use the first byte as flags if available

    // Call the function-under-test
    CURLcode result = curl_global_init_mem(flags, my_malloc, my_free, my_realloc, my_strdup, my_calloc);

    // Check the result (not necessary for fuzzing, but good practice)
    if (result == CURLE_OK) {
        // Cleanup after successful initialization
        curl_global_cleanup();
    }

    return 0;
}

}