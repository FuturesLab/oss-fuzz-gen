#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Cast the first sizeof(int) bytes of data to an int
    int status_code = *(const int*)data;

    // Call the function-under-test
    const char *result = pcap_statustostr(status_code);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // For example, just access the first character
        volatile char first_char = result[0];
    }

    return 0;
}