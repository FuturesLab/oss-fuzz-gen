#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pcap.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a temporary file to store the input data
    char filename[] = "/tmp/fuzz_pcap_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the pcap file
    pcap_handle = pcap_open_offline(filename, errbuf);
    if (pcap_handle == NULL) {
        // Cleanup the temporary file
        remove(filename);
        return 0;
    }

    // Call the function-under-test
    int minor_version = pcap_minor_version(pcap_handle);

    // Cleanup
    pcap_close(pcap_handle);
    remove(filename);

    return 0;
}