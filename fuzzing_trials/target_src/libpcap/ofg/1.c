#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to safely pass it as a C-string
    char *null_terminated_data;

    // Allocate memory for the null-terminated string
    null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Memory allocation failed, exit gracefully
    }

    // Copy the input data and null-terminate it
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    int result = pcap_tstamp_type_name_to_val(null_terminated_data);

    // Free allocated memory
    free(null_terminated_data);

    return 0;
}