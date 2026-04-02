#include <cstdint>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <cstdlib>  // Include for malloc and free

extern "C" {
    #include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *date_str = static_cast<char*>(malloc(size + 1));
    if (date_str == nullptr) return 0;
    memcpy(date_str, data, size);
    date_str[size] = '\0';

    // Initialize a non-null time_t value
    time_t now = time(NULL);

    // Call the function-under-test
    time_t result = curl_getdate(date_str, &now);

    // Print the result (optional, for debugging purposes)
    printf("Parsed time: %ld\n", result);

    // Clean up
    free(date_str);

    return 0;
}