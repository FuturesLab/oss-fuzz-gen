#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include this header for strlen and memcpy

extern "C" {

// Custom memory allocation callbacks
void* custom_malloc_60(size_t size) {
    return malloc(size);
}

void custom_free_60(void* ptr) {
    free(ptr);
}

void* custom_realloc_60(void* ptr, size_t size) {
    return realloc(ptr, size);
}

char* custom_strdup_60(const char* str) {
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

void* custom_calloc_60(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Convert data to a long value for the first parameter
    long flags = 0;
    if (size >= sizeof(long)) {
        flags = *(const long*)data;
    }

    // Call the function-under-test
    CURLcode result = curl_global_init_mem(flags, custom_malloc_60, custom_free_60, custom_realloc_60, custom_strdup_60, custom_calloc_60);

    // Cleanup if necessary
    if (result == CURLE_OK) {
        curl_global_cleanup();
    }

    return 0;
}

}