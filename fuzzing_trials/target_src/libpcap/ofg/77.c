#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Remove the 'extern "C"' as it is not compatible with C
int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Initialize pcap_t and pcap_pkthdr
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max packet size
    struct pcap_pkthdr header;

    // Ensure that data is not NULL and has a reasonable size
    if (data == NULL || size == 0) {
        pcap_close(handle);
        return 0;
    }

    // Create a temporary file to store the input data
    FILE *tempfile = tmpfile();
    if (tempfile == NULL) {
        pcap_close(handle);
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempfile);
    rewind(tempfile);

    // Open the temporary file as a pcap file
    pcap_t *pcap = pcap_fopen_offline(tempfile, errbuf);
    if (pcap == NULL) {
        fclose(tempfile);
        pcap_close(handle);
        return 0;
    }

    // Call the function-under-test
    const u_char *packet = pcap_next(pcap, &header);

    // Clean up
    pcap_close(pcap);
    fclose(tempfile);
    pcap_close(handle);

    return 0;
}