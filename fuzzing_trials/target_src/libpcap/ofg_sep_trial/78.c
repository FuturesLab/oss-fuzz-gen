#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // Include for FILE operations

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Initialize variables
    pcap_t *pcap_handle;
    struct pcap_pkthdr header;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to store the input data
    char filename[] = "/tmp/fuzz_input.pcap";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the pcap file
    pcap_handle = pcap_open_offline(filename, errbuf);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    const u_char *packet = pcap_next(pcap_handle, &header);

    // Clean up
    pcap_close(pcap_handle);
    remove(filename);

    return 0;
}