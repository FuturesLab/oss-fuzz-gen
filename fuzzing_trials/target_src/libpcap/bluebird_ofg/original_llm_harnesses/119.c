#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Initialize variables
    pcap_t *pcap_handle = NULL;
    pcap_dumper_t *dumper = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    char filename[256];

    // Ensure data is large enough to extract a filename
    if (size < 1) {
        return 0;
    }

    // Create a dummy pcap_t handle using pcap_open_dead
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Extract a filename from the input data
    size_t filename_len = size < 255 ? size : 255;
    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';  // Null-terminate the filename

    // Call the function-under-test
    dumper = pcap_dump_open(pcap_handle, filename);

    // Clean up
    if (dumper != NULL) {
        pcap_dump_close(dumper);
    }
    pcap_close(pcap_handle);

    return 0;
}