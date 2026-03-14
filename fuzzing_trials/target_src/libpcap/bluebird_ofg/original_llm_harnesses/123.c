#include <stdint.h>
#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>

// Remove 'extern "C"' as it is not needed in a C program
int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    FILE *tmpFile;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap;

    // Create a temporary file to write the input data
    tmpFile = tmpfile();
    if (tmpFile == NULL) {
        return 0;
    }

    // Write the data to the temporary file
    if (fwrite(data, 1, size, tmpFile) != size) {
        fclose(tmpFile);
        return 0;
    }

    // Reset the file pointer to the beginning of the file
    rewind(tmpFile);

    // Call the function-under-test
    pcap = pcap_fopen_offline_with_tstamp_precision(tmpFile, PCAP_TSTAMP_PRECISION_MICRO, errbuf);

    // Clean up
    if (pcap != NULL) {
        pcap_close(pcap);
    }
    fclose(tmpFile);

    return 0;
}