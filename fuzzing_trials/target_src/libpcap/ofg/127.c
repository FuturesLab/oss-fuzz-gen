#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    const u_char *packet;
    int packet_size;

    // Check if input size is sufficient for a packet
    if (size < 1) {
        return 0;
    }

    // Initialize a pcap handle for a dummy device
    handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max packet size
    if (handle == NULL) {
        return 0;
    }

    // Allocate memory for the packet
    packet = (const u_char *)malloc(size);
    if (packet == NULL) {
        pcap_close(handle);
        return 0;
    }

    // Copy data to the packet
    memcpy((void *)packet, data, size);
    packet_size = (int)size;

    // Call the function-under-test
    pcap_sendpacket(handle, packet, packet_size);

    // Clean up
    free((void *)packet);
    pcap_close(handle);

    return 0;
}