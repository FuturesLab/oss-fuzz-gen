#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" {
    // Declare the function-under-test
    char * curl_getenv(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely convert to a C-style string
    if (size == 0) return 0;

    // Allocate memory for a null-terminated string
    char *env_var = (char *)malloc(size + 1);
    if (env_var == NULL) return 0;

    // Copy the input data to the allocated memory and null-terminate it
    memcpy(env_var, data, size);
    env_var[size] = '\0';

    // Call the function-under-test
    char *result = curl_getenv(env_var);

    // Free the result if it's non-NULL
    if (result != NULL) {
        free(result);
    }

    // Free the allocated memory for the environment variable name
    free(env_var);

    return 0;
}