#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the interface name and error buffer
    if (size < 1) {
        return 0;
    }

    // Prepare the interface name from the input data
    char interface_name[256];
    size_t interface_name_length = size < 255 ? size : 255;
    memcpy(interface_name, data, interface_name_length);
    interface_name[interface_name_length] = '\0'; // Null-terminate the string

    // Prepare variables for network and mask
    bpf_u_int32 net, mask;

    // Prepare an error buffer
    char errbuf[PCAP_ERRBUF_SIZE];

    // Call the function-under-test
    pcap_lookupnet(interface_name, &net, &mask, errbuf);

    return 0;
}