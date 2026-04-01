#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" {
    #include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated and not empty
    if (size == 0) return 0;

    // Allocate memory for the null-terminated string
    char *env_var = static_cast<char*>(malloc(size + 1));
    if (!env_var) return 0;

    // Copy the input data and null-terminate it
    memcpy(env_var, data, size);
    env_var[size] = '\0';

    // Call the function-under-test
    char *result = curl_getenv(env_var);

    // Free the result if it is not NULL
    if (result) {
        free(result);
    }

    // Free the allocated memory for env_var
    free(env_var);

    return 0;
}