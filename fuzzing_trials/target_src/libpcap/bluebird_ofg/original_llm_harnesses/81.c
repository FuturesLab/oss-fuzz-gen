#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Ensure size is large enough to create a temporary file
    if (size < 1) {
        return 0;
    }

    // Create a temporary file
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write data to the temporary file
    size_t written = fwrite(data, 1, size, temp_file);
    if (written != size) {
        fclose(temp_file);
        return 0;
    }

    // Rewind the file to the beginning for reading
    rewind(temp_file);

    // Use a non-NULL string for the error buffer
    char errbuf[PCAP_ERRBUF_SIZE] = {0};

    // Call the function-under-test
    pcap_t *pcap = pcap_fopen_offline(temp_file, errbuf);

    // Clean up
    if (pcap != NULL) {
        pcap_close(pcap);
    }
    fclose(temp_file);

    return 0;
}