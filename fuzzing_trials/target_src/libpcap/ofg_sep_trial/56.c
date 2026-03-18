#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void packet_handler_56(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Example packet handler function
    // Do nothing for now
}

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int packet_count_limit = 10; // Limit to 10 packets for fuzzing
    int timeout_limit = 1000; // Timeout in milliseconds

    // Create a pcap_t handle from the provided data
    handle = pcap_open_offline_with_tstamp_precision((const char *)data, PCAP_TSTAMP_PRECISION_MICRO, errbuf);
    if (handle == NULL) {
        // If pcap_open_offline fails, return 0 to continue fuzzing
        return 0;
    }

    // Allocate a non-NULL user data pointer
    u_char user_data = 0x01; // Example user data

    // Call the function-under-test
    pcap_loop(handle, packet_count_limit, packet_handler_56, &user_data);

    // Close the pcap handle
    pcap_close(handle);

    return 0;
}