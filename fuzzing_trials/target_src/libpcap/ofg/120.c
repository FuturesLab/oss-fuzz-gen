#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Initialize variables
    pcap_t *pcap_handle = NULL;
    pcap_dumper_t *dumper = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    char filename[256];

    // Ensure the data size is sufficient for a filename
    if (size < 2) {
        return 0;
    }

    // Create a valid filename from the input data
    size_t filename_length = (size < sizeof(filename) - 1) ? size : sizeof(filename) - 1;
    memcpy(filename, data, filename_length);
    filename[filename_length] = '\0';

    // Open a pcap handle with a dummy device
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    dumper = pcap_dump_open(pcap_handle, filename);

    // Clean up
    if (dumper != NULL) {
        pcap_dump_close(dumper);
    }
    pcap_close(pcap_handle);

    return 0;
}