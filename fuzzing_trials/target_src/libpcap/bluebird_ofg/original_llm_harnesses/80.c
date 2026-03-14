#include <stdio.h>
#include <stdint.h>
#include <pcap.h>

// Function to be used by the fuzzer
int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    FILE *file;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle;

    // Create a temporary file to write the input data
    file = tmpfile();
    if (file == NULL) {
        return 0;
    }

    // Write the data to the file
    if (fwrite(data, 1, size, file) != size) {
        fclose(file);
        return 0;
    }

    // Reset the file pointer to the beginning of the file
    rewind(file);

    // Call the function-under-test
    pcap_handle = pcap_fopen_offline(file, errbuf);

    // Clean up
    if (pcap_handle != NULL) {
        pcap_close(pcap_handle);
    }
    fclose(file);

    return 0;
}