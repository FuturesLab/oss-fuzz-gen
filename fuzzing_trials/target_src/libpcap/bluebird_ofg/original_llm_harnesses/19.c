#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    pcap_dumper_t *dumper;
    char errbuf[PCAP_ERRBUF_SIZE];
    char filename[256];

    // Ensure the data size is sufficient for the filename
    if (size < 1) {
        return 0;
    }

    // Initialize pcap handle with a dummy value
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Copy a portion of data to use as a filename, ensuring null-termination
    size_t filename_size = size < sizeof(filename) ? size : sizeof(filename) - 1;
    memcpy(filename, data, filename_size);
    filename[filename_size] = '\0';

    // Call the function-under-test
    dumper = pcap_dump_open_append(pcap_handle, filename);

    // Clean up
    if (dumper != NULL) {
        pcap_dump_close(dumper);
    }
    pcap_close(pcap_handle);

    return 0;
}