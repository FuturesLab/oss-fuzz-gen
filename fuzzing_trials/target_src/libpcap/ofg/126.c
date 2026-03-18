#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = NULL;
    u_char *packet = NULL;
    int packet_size = 0;

    // Open a fake pcap handle for testing purposes
    handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the packet size is non-zero and within a reasonable limit
    if (size > 0 && size <= 65535) {
        packet_size = (int)size;
        packet = (u_char *)malloc(packet_size);
        if (packet != NULL) {
            memcpy(packet, data, packet_size);
            // Call the function-under-test
            pcap_sendpacket(handle, packet, packet_size);
            free(packet);
        }
    }

    // Close the pcap handle
    pcap_close(handle);

    return 0;
}