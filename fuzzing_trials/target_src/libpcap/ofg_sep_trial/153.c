#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for a null-terminated string
    if (size < 1) return 0;

    // Allocate memory for the device name and ensure it's null-terminated
    char device[size + 1];
    memcpy(device, data, size);
    device[size] = '\0';

    // Initialize variables for network and mask
    bpf_u_int32 net = 0;
    bpf_u_int32 mask = 0;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Call the function-under-test
    pcap_lookupnet(device, &net, &mask, errbuf);

    return 0;
}