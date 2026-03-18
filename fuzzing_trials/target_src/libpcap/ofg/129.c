#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int tstamp_type = *(const int *)data;

    // Call the function-under-test
    const char *result = pcap_tstamp_type_val_to_name(tstamp_type);

    // Use the result in some way (e.g., check if it's not NULL)
    if (result != NULL) {
        // Do something with the result, like print it (commented out for fuzzing)
        // printf("Timestamp type name: %s\n", result);
    }

    return 0;
}