#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include for malloc, free, realloc, calloc
#include <string.h>  // Include for strdup
#include <curl/curl.h>

extern "C" {

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
    return strdup(str);
}

void* custom_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Use the first 8 bytes of data as a long parameter for curl_global_init_mem
    long flags = 0;
    if (size >= sizeof(long)) {
        flags = *(reinterpret_cast<const long*>(data));
    }

    // Call the function-under-test with custom memory functions
    CURLcode result = curl_global_init_mem(flags, custom_malloc, custom_free, custom_realloc, custom_strdup, custom_calloc);

    // Clean up after initialization
    if (result == CURLE_OK) {
        curl_global_cleanup();
    }

    return 0;
}

}