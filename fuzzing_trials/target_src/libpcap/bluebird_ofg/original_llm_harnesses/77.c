#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>
#include <unistd.h> // For close() and unlink()
#include <fcntl.h>  // For mkstemp()
#include <sys/types.h> // For ssize_t

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Initialize variables
    pcap_t *pcap_handle;
    struct pcap_pkthdr header;
    char errbuf[PCAP_ERRBUF_SIZE];
    const u_char *packet;

    // Create a temporary file to store the input data
    char tmp_filename[] = "/tmp/fuzz_pcap_XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmp_filename);
        return 0;
    }
    close(fd);

    // Open the temporary file as a pcap file
    pcap_handle = pcap_open_offline(tmp_filename, errbuf);
    if (pcap_handle == NULL) {
        unlink(tmp_filename);
        return 0;
    }

    // Call the function-under-test
    packet = pcap_next(pcap_handle, &header);

    // Clean up
    pcap_close(pcap_handle);
    unlink(tmp_filename);

    return 0;
}