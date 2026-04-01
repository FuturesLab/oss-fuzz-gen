#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for creating a valid string
    if (size < 1) {
        return 0;
    }

    // Initialize a pcap_t object
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) {
        return 0;
    }

    // Create a null-terminated string from data
    char *error_message = (char *)malloc(size + 1);
    if (error_message == NULL) {
        pcap_close(pcap);
        return 0;
    }
    memcpy(error_message, data, size);
    error_message[size] = '\0';

    // Call the function-under-test
    pcap_perror(pcap, error_message);

    // Clean up
    free(error_message);
    pcap_close(pcap);

    return 0;
}