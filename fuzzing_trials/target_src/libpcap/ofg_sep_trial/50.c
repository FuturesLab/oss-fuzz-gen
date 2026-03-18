#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    pcap_t *pcap;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure the data size is sufficient to create a pcap file
    if (size < 24) { // Minimum size for a pcap file header
        return 0;
    }

    // Use pcap_open_offline to create a pcap_t structure from the input data
    FILE *temp_file = fmemopen((void *)data, size, "rb");
    if (temp_file == NULL) {
        return 0;
    }

    pcap = pcap_fopen_offline(temp_file, errbuf);
    if (pcap == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Call the function under test
    int result = pcap_datalink(pcap);

    // Clean up
    pcap_close(pcap);
    fclose(temp_file);

    return 0;
}