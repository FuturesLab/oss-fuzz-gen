#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the function parameters
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for the two string parameters
    size_t first_len = size / 2;
    size_t second_len = size - first_len;

    // Allocate memory for the strings and ensure they are null-terminated
    char *first_param = (char *)malloc(first_len + 1);
    char *second_param = (char *)malloc(second_len + 1);

    if (first_param == NULL || second_param == NULL) {
        free(first_param);
        free(second_param);
        return 0;
    }

    memcpy(first_param, data, first_len);
    first_param[first_len] = '\0';

    memcpy(second_param, data + first_len, second_len);
    second_param[second_len] = '\0';

    // Call the function-under-test
    pcap_t *handle = pcap_create(first_param, second_param);

    // Clean up
    free(first_param);
    free(second_param);

    // If a handle was created, close it
    if (handle != NULL) {
        pcap_close(handle);
    }

    return 0;
}