#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract parameters
    if (size < 10) {
        return 0;
    }

    // Extract parameters from the input data
    const char *device = (const char *)data; // First part of data as device name
    int snaplen = (int)data[0];              // Use first byte for snaplen
    int promisc = (int)data[1];              // Use second byte for promisc
    int to_ms = (int)data[2];                // Use third byte for timeout
    char errbuf[PCAP_ERRBUF_SIZE];           // Error buffer for pcap_open_live

    // Null-terminate the device string
    char device_name[256];
    size_t device_name_length = size < 255 ? size : 255;
    strncpy(device_name, device, device_name_length);
    device_name[device_name_length] = '\0';

    // Call the function-under-test
    pcap_t *handle = pcap_open_live(device_name, snaplen, promisc, to_ms, errbuf);

    // If handle is not NULL, close it
    if (handle != NULL) {
        pcap_close(handle);
    }

    return 0;
}