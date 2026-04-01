#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Use a temporary file to simulate a pcap file from the input data
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Open the temporary file as a pcap handle
    pcap_handle = pcap_fopen_offline(temp_file, errbuf);
    if (pcap_handle == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Call the function-under-test
    int fd = pcap_fileno(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);
    fclose(temp_file);

    return 0;
}