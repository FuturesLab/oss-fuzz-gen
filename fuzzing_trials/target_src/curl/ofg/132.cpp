#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Allocate memory for the curl_slist structure
    struct curl_slist *slist = NULL;
    struct curl_slist *current = NULL;

    // Create a simple linked list with the input data
    size_t i = 0;
    while (i < size) {
        // Find the length of the next string in the input data
        size_t len = 0;
        while (i + len < size && data[i + len] != '\0') {
            len++;
        }

        // Allocate memory for the new string and copy it from the input data
        char *str = (char *)malloc(len + 1);
        if (str == NULL) {
            curl_slist_free_all(slist);
            return 0;
        }
        memcpy(str, data + i, len);
        str[len] = '\0';

        // Add the string to the curl_slist
        struct curl_slist *new_node = curl_slist_append(NULL, str);
        if (new_node == NULL) {
            free(str);
            curl_slist_free_all(slist);
            return 0;
        }

        if (slist == NULL) {
            slist = new_node;
        } else {
            current->next = new_node;
        }
        current = new_node;

        // Move to the next string in the input data
        i += len + 1;
    }

    // Call the function under test
    curl_slist_free_all(slist);

    return 0;
}