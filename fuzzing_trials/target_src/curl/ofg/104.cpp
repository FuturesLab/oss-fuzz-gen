#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    // Initialize a curl_slist pointer to NULL
    struct curl_slist *list = NULL;

    // Convert the input data to a null-terminated string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    list = curl_slist_append(list, inputString);

    // Free the allocated memory for the input string
    free(inputString);

    // Free the curl_slist if it was successfully created
    if (list != NULL) {
        curl_slist_free_all(list);
    }

    return 0;
}