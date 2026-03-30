#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include this header for strlen and memcpy

extern "C" {

// Custom memory allocation callbacks
void* custom_malloc(size_t size) {
    return malloc(size);
}

void custom_free(void* ptr) {
    free(ptr);
}

void* custom_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}

char* custom_strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

void* custom_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Convert data to a long value for the first parameter
    long flags = 0;
    if (size >= sizeof(long)) {
        flags = *(const long*)data;
    }

    // Call the function-under-test
    CURLcode result = curl_global_init_mem(flags, custom_malloc, custom_free, custom_realloc, custom_strdup, custom_calloc);

    // Cleanup if necessary
    if (result == CURLE_OK) {
        curl_global_cleanup();
    }

    return 0;
}

}