#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure the data is not empty and is large enough to be a valid pcap file
    if (size < sizeof(struct pcap_file_header)) {
        return 0;
    }

    // Create a temporary file to store the input data
    char tmp_filename[] = "/tmp/fuzz_pcap_XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmp_filename);
        return 0;
    }
    close(fd);

    // Open the pcap file
    pcap_handle = pcap_open_offline(tmp_filename, errbuf);
    if (pcap_handle == NULL) {
        unlink(tmp_filename);
        return 0;
    }

    // Call the function-under-test
    int major_version = pcap_major_version(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);
    unlink(tmp_filename);

    return 0;
}