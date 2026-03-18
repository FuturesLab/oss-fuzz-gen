#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to split into two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t filename_len = size / 2;
    size_t errbuf_len = size - filename_len;

    // Allocate memory for the filename and error buffer
    char *filename = (char *)malloc(filename_len + 1);
    char *errbuf = (char *)malloc(errbuf_len + 1);

    // Check for successful memory allocation
    if (filename == NULL || errbuf == NULL) {
        free(filename);
        free(errbuf);
        return 0;
    }

    // Copy data into the filename and error buffer and null-terminate them
    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';

    memcpy(errbuf, data + filename_len, errbuf_len);
    errbuf[errbuf_len] = '\0';

    // Call the function-under-test
    pcap_t *handle = pcap_open_offline(filename, errbuf);

    // Clean up
    if (handle != NULL) {
        pcap_close(handle);
    }

    free(filename);
    free(errbuf);

    return 0;
}