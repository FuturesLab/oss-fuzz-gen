#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include this for mkstemp, close, and unlink functions
#include <fcntl.h>  // Include this for write function

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    FILE *file = NULL;

    // Ensure the data is not empty and has a reasonable size
    if (size == 0 || size > 65535) {
        return 0;
    }

    // Create a temporary file to hold the pcap data
    char tmp_filename[] = "/tmp/fuzz_pcap_XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmp_filename);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file with pcap
    pcap_handle = pcap_open_offline(tmp_filename, errbuf);
    if (pcap_handle == NULL) {
        unlink(tmp_filename);
        return 0;
    }

    // Call the function-under-test
    file = pcap_file(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);
    unlink(tmp_filename);

    return 0;
}