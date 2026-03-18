#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Define the callback function separately
void packet_handler_18(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Simple callback that does nothing
}

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    pcap_t *pcap;
    char errbuf[PCAP_ERRBUF_SIZE];
    u_char *user_data;
    int cnt = 10; // Number of packets to process, can be adjusted

    // Initialize pcap with a dummy file
    pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) {
        return 0;
    }

    // Allocate user data
    user_data = (u_char *)malloc(size);
    if (user_data == NULL) {
        pcap_close(pcap);
        return 0;
    }

    // Copy the fuzzing data to user_data
    memcpy(user_data, data, size);

    // Call the function-under-test
    // Check the return value to ensure it is used
    int dispatch_result = pcap_dispatch(pcap, cnt, packet_handler_18, user_data);
    (void)dispatch_result; // Explicitly ignore the result to avoid warnings

    // Clean up
    free(user_data);
    pcap_close(pcap);

    return 0;
}