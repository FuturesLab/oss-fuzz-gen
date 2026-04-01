#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    const u_char *packet;
    int packet_size;

    // Open a fake pcap handle for testing
    handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the size is not zero to avoid passing NULL to the function
    if (size == 0) {
        pcap_close(handle);
        return 0;
    }

    // Set the packet to the input data
    packet = data;
    packet_size = (int)size;

    // Call the function-under-test
    pcap_sendpacket(handle, packet, packet_size);

    // Clean up
    pcap_close(handle);

    return 0;
}