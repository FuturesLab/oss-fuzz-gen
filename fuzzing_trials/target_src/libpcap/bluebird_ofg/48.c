#include "pcap/pcap.h"
#include <stdint.h>
#include <stddef.h>
#include "string.h"

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for the device name and error buffer
    if (size < 2) {
        return 0;
    }

    // Initialize device name from input data
    char device[256];
    size_t device_len = size < 255 ? size : 255;
    memcpy(device, data, device_len);
    device[device_len] = '\0'; // Null-terminate the device name

    // Initialize variables for network and netmask
    bpf_u_int32 net = 0;
    bpf_u_int32 netmask = 0;

    // Initialize error buffer
    char errbuf[PCAP_ERRBUF_SIZE];
    memset(errbuf, 0, sizeof(errbuf));

    // Call the function-under-test
    pcap_lookupnet(device, &net, &netmask, errbuf);

    return 0;
}