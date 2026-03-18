#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Define a simple callback function outside of LLVMFuzzerTestOneInput
void packet_handler_17(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Do nothing, just a placeholder for the callback
}

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    u_char *user_data;
    int cnt = 10; // Number of packets to process, arbitrary non-negative value

    // Initialize pcap_handle with a live capture or a saved file
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max snaplen
    if (pcap_handle == NULL) {
        return 0;
    }

    // Allocate memory for user_data and copy data into it
    user_data = (u_char *)malloc(size);
    if (user_data == NULL) {
        pcap_close(pcap_handle);
        return 0;
    }
    memcpy(user_data, data, size);

    // Call the function-under-test
    int result = pcap_dispatch(pcap_handle, cnt, packet_handler_17, user_data);

    // Clean up
    free(user_data);
    pcap_close(pcap_handle);

    // Return result to ensure the function's return value is used
    return result;
}