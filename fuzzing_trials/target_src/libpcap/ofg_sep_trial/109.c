#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data
    int status_code = *(const int *)data;

    // Call the function-under-test
    const char *result = pcap_statustostr(status_code);

    // Use the result in some way to avoid compiler optimizations
    if (result != NULL) {
        volatile size_t len = strlen(result);
        (void)len;
    }

    return 0;
}