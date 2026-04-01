#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an int from the input data
    int datalink_value = *(const int *)data;

    // Call the function-under-test
    const char *result = pcap_datalink_val_to_name(datalink_value);

    // Use the result in some way to avoid compiler optimizations
    if (result != NULL) {
        // Do something trivial with the result
        volatile size_t length = strlen(result);
        (void)length; // Prevent unused variable warning
    }

    return 0;
}