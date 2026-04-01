#include <stdint.h>
#include <pcap/pcap.h>
#include <stdlib.h>
#include <string.h>

// Remove 'extern "C"' as it is not needed in C code
int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = NULL;
    char *device = NULL;

    // Ensure the data is not empty and can be used as a device name
    if (size > 0) {
        // Allocate memory for the device name and ensure it is null-terminated
        device = (char *)malloc(size + 1);
        if (device == NULL) {
            return 0;
        }
        memcpy(device, data, size);
        device[size] = '\0';

        // Open the device for live capture
        handle = pcap_open_live(device, BUFSIZ, 1, 1000, errbuf);
        free(device);

        if (handle != NULL) {
            // Call the function-under-test
            int fd = pcap_fileno(handle);

            // Close the handle after use
            pcap_close(handle);
        }
    }

    return 0;
}