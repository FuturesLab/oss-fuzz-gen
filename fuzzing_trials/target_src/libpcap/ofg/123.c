#include <stdio.h>
#include <stdint.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    FILE *file = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    u_int precision = PCAP_TSTAMP_PRECISION_MICRO; // Default precision

    // Ensure the data is non-empty and can be written to a file
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to write the input data
    file = tmpfile();
    if (file == NULL) {
        return 0;
    }

    // Write the data to the temporary file
    if (fwrite(data, 1, size, file) != size) {
        fclose(file);
        return 0;
    }

    // Rewind the file to the beginning for reading
    rewind(file);

    // Call the function-under-test
    pcap_t *pcap_handle = pcap_fopen_offline_with_tstamp_precision(file, precision, errbuf);

    // Clean up
    if (pcap_handle != NULL) {
        pcap_close(pcap_handle);
    }
    fclose(file);

    return 0;
}