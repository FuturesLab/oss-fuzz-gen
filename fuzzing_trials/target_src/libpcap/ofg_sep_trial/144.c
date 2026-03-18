#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure the data is not empty and has a reasonable size for pcap_open_offline
    if (size == 0 || size > PCAP_ERRBUF_SIZE) {
        return 0;
    }

    // Create a temporary file to store the input data
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Open the temporary file with pcap_open_offline
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