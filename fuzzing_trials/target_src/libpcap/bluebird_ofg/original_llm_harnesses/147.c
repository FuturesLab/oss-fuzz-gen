#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a null-terminated string
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the file name and error buffer
    char filename[size + 1];
    char errbuf[PCAP_ERRBUF_SIZE];

    // Copy data into filename and null-terminate it
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    pcap_t *handle = pcap_open_offline(filename, errbuf);

    // If handle is not NULL, close it
    if (handle != NULL) {
        pcap_close(handle);
    }

    return 0;
}