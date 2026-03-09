#include <stdint.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    FILE *temp_file;
    char temp_filename[] = "temp_pcap_file";
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a temporary file to write the input data
    temp_file = fopen(temp_filename, "wb");
    if (temp_file == NULL) {
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, temp_file);
    fclose(temp_file);

    // Reopen the file for reading
    temp_file = fopen(temp_filename, "rb");
    if (temp_file == NULL) {
        return 0;
    }

    // Call the function-under-test
    pcap_handle = pcap_fopen_offline(temp_file, errbuf);

    // Clean up
    if (pcap_handle != NULL) {
        pcap_close(pcap_handle);
    }
    fclose(temp_file);
    remove(temp_filename);

    return 0;
}