#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include this for malloc and free
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Return if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function under test
    int result = pcap_tstamp_type_name_to_val(null_terminated_data);

    // Free the allocated memory
    free(null_terminated_data);

    return 0;
}