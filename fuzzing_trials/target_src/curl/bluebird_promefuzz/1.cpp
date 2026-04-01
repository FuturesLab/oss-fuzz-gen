#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "curl/curl.h"
#include "/src/curl/include/curl/easy.h"
#include "/src/curl/include/curl/websockets.h"
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>

static void* custom_malloc(size_t size) {
    return malloc(size);
}

static void custom_free(void* ptr) {
    free(ptr);
}

static void* custom_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}

static char* custom_strdup(const char* str) {
    return strdup(str);
}

static void* custom_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize libcurl with custom memory functions
    CURLcode res = curl_global_init_mem(CURL_GLOBAL_ALL, custom_malloc, custom_free, custom_realloc, custom_strdup, custom_calloc);
    if (res != CURLE_OK) return 0;

    // Create a CURL handle
    CURL *curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Perform a basic curl operation
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 2L);
    res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        // Prepare data for WebSocket
        char buffer[1024];
        snprintf(buffer, sizeof(buffer), "%.*s", static_cast<int>(Size), Data);
        size_t sent;
        curl_ws_send(curl, buffer, Size, &sent, 0, 0);

        // Start a WebSocket frame
        curl_ws_start_frame(curl, 0, Size);

        // Perform upkeep
        curl_easy_upkeep(curl);
    }

    // Cleanup
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}