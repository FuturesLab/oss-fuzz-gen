#include <stdint.h>
#include <stddef.h>
#include "stdio.h"
#include "pcap/pcap.h"

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = pcap_lib_version();

    // Print the version to ensure the function is called
    if (version != NULL) {
        printf("PCAP Library Version: %s\n", version);
    }

    // Utilize the input data
    if (data != NULL && size > 0) {
        // Example of utilizing the input data
        printf("First byte of input data: %02x\n", data[0]);
    }

    return 0;
}