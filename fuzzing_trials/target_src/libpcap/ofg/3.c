#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    
    // Ensure the size is large enough to contain a valid device name
    if (size < 1) {
        return 0;
    }

    // Copy the data to a null-terminated string to simulate a device name
    char *device = (char *)malloc(size + 1);
    if (device == NULL) {
        return 0;
    }
    memcpy(device, data, size);
    device[size] = '\0';

    // Open the device for capturing
    handle = pcap_create(device, errbuf);
    free(device);

    if (handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = pcap_activate(handle);

    // Clean up
    pcap_close(handle);

    return 0;
}