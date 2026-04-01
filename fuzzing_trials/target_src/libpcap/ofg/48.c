#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure the input data is non-null and size is non-zero
    if (data == NULL || size == 0) {
        return 0;
    }

    // Create a temporary file to write the input data
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write data to the temporary file
    fwrite(data, 1, size, temp_file);
    fflush(temp_file);

    // Rewind the file to the beginning for reading
    rewind(temp_file);

    // Open the temporary file as a pcap file
    pcap_handle = pcap_fopen_offline(temp_file, errbuf);
    if (pcap_handle == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Call the function under test
    int result = pcap_datalink_ext(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);
    fclose(temp_file);

    return 0;
}