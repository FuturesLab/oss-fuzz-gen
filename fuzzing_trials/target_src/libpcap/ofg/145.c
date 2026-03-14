#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Initialize variables
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure the data is not empty
    if (size == 0) return 0;

    // Create a pcap_t handle using pcap_open_offline with a temporary file
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) return 0;

    // Write the data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Use pcap_fopen_offline to open the file as a pcap handle
    pcap_handle = pcap_fopen_offline(temp_file, errbuf);
    if (pcap_handle == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Call the function-under-test
    int major_version = pcap_major_version(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);
    fclose(temp_file);

    return 0;
}