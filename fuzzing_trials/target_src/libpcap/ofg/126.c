#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    const u_char *packet;
    int packet_size;

    // Ensure the data size is sufficient for a packet
    if (size < 1) {
        return 0;
    }

    // Open a pcap handle for a dummy device
    handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet link type
    if (handle == NULL) {
        return 0;
    }

    // Allocate memory for the packet and copy data into it
    packet_size = (int)size;
    packet = (const u_char *)malloc(packet_size);
    if (packet == NULL) {
        pcap_close(handle);
        return 0;
    }
    memcpy((void *)packet, data, packet_size);

    // Call the function-under-test
    pcap_sendpacket(handle, packet, packet_size);

    // Clean up
    free((void *)packet);
    pcap_close(handle);

    return 0;
}