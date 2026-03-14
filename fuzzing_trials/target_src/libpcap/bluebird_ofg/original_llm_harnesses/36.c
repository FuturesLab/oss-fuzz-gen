#include <stdio.h>
#include <stdint.h>
#include <pcap.h>

// Define the fuzzer test function
int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = NULL;
    FILE *file_handle = NULL;

    // Ensure that the data size is sufficient for a minimum valid pcap file header
    if (size < 24) { // 24 bytes for a typical pcap file header
        return 0;
    }

    // Create a temporary file to simulate a pcap file
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Open the temporary file as a pcap file
    pcap_handle = pcap_fopen_offline(temp_file, errbuf);
    if (pcap_handle == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Call the function-under-test
    file_handle = pcap_file(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);
    fclose(temp_file);

    return 0;
}