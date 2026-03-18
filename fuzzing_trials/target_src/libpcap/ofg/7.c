#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int datalink_val = *(const int *)data;

    // Call the function-under-test
    const char *name = pcap_datalink_val_to_name(datalink_val);

    // Use the result to prevent optimization out
    if (name != NULL) {
        // Do something with the name, e.g., print it
        // printf("%s\n", name); // Uncomment if needed for debugging
    }

    return 0;
}