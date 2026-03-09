#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure the data is large enough to be a valid device name
    if (size < 1 || size >= PCAP_ERRBUF_SIZE) {
        return 0;
    }

    // Copy the data into a null-terminated string for the device name
    char device[PCAP_ERRBUF_SIZE];
    memcpy(device, data, size);
    device[size] = '\0';

    // Create a pcap handle with the provided device name
    handle = pcap_create(device, errbuf);
    if (handle == NULL) {
        return 0;
    }

    // Set some options on the handle to ensure it's in a valid state
    pcap_set_snaplen(handle, 65535);
    pcap_set_promisc(handle, 1);
    pcap_set_timeout(handle, 1000);

    // Call the function-under-test
    pcap_activate(handle);

    // Clean up
    pcap_close(handle);

    return 0;
}