#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Initialize pcap_t structure
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    
    // Ensure pcap_handle is not NULL
    if (pcap_handle == NULL) {
        return 0;
    }

    // Prepare a non-NULL string for the error message
    const char *error_message = "Sample error message";

    // Call the function-under-test
    pcap_perror(pcap_handle, error_message);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}