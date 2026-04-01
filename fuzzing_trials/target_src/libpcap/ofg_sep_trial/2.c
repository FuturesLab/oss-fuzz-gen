#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>  // Include this for the malloc and free functions

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated to safely use it as a string
    char *inputStr = (char *)malloc(size + 1);
    if (inputStr == NULL) {
        return 0; // Exit if memory allocation fails
    }

    memcpy(inputStr, data, size);
    inputStr[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int result = pcap_tstamp_type_name_to_val(inputStr);

    // Free the allocated memory
    free(inputStr);

    return 0;
}