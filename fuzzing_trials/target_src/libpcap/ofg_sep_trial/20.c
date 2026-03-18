#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Initialize pcap_t and dummy file name
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Create a dummy file name from the input data
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        pcap_close(pcap_handle);
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0'; // Ensure null-termination

    // Call the function under test
    pcap_dumper_t *dumper = pcap_dump_open_append(pcap_handle, filename);

    // Clean up
    if (dumper != NULL) {
        pcap_dump_close(dumper);
    }
    pcap_close(pcap_handle);
    free(filename);

    return 0;
}