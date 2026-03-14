#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a null-terminated string
    if (size < 1) return 0;

    // Allocate memory for the device name and ensure it is null-terminated
    char device[size + 1];
    memcpy(device, data, size);
    device[size] = '\0';

    // Initialize variables for network and netmask
    bpf_u_int32 net, mask;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Call the function-under-test
    pcap_lookupnet(device, &net, &mask, errbuf);

    return 0;
}