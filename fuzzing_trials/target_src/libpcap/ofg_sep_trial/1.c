#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for use as a C-string
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int result = pcap_tstamp_type_name_to_val(input_str);

    // Clean up
    free(input_str);

    return 0;
}