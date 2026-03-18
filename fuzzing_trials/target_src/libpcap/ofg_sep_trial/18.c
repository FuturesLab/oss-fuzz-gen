#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Define the callback function separately
void packet_handler_18(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Simple callback function that does nothing
}

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    pcap_t *pcap;
    char errbuf[PCAP_ERRBUF_SIZE];
    int cnt = 10; // Arbitrary non-zero count for packets
    u_char user_data[256]; // Arbitrary non-null user data

    // Initialize user_data with some values
    memset(user_data, 42, sizeof(user_data));

    // Create a pcap_t from the provided data
    pcap = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet link type, max capture length
    if (pcap == NULL) {
        return 0;
    }

    // Create a pcap_pkthdr and u_char buffer to simulate packets
    struct pcap_pkthdr header;
    header.caplen = size;
    header.len = size;
    const u_char *packet_data = data;

    // Call the function-under-test
    int result = pcap_dispatch(pcap, cnt, packet_handler_18, user_data);
    (void)result; // Explicitly ignore the result to avoid warning

    // Clean up
    pcap_close(pcap);

    return 0;
}