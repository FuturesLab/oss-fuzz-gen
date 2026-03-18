#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Initialize variables
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    const char *device = "lo"; // Loopback interface for testing

    // Open the device for capturing (injection)
    handle = pcap_open_live(device, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        return 0;
    }

    // Allocate memory for the packet data
    void *packet_data = malloc(size);
    if (packet_data == NULL) {
        pcap_close(handle);
        return 0;
    }

    // Copy the input data to the packet data
    memcpy(packet_data, data, size);

    // Call the function-under-test
    pcap_inject(handle, packet_data, size);

    // Clean up
    free(packet_data);
    pcap_close(handle);

    return 0;
}