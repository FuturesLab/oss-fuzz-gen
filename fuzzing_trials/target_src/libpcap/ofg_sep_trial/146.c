#include <pcap.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to contain a null-terminated string
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the file name and error buffer
    char *filename = (char *)malloc(size + 1);
    char errbuf[PCAP_ERRBUF_SIZE];

    // Copy the data into the filename buffer and null-terminate it
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    pcap_t *handle = pcap_open_offline(filename, errbuf);

    // If handle is not NULL, close it
    if (handle != NULL) {
        pcap_close(handle);
    }

    // Free the allocated memory
    free(filename);

    return 0;
}