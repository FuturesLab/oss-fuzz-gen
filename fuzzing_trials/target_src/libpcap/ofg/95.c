#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Removed the 'extern "C"' linkage specification, as it is not valid in C code
int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr *header;
    const u_char *packet;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to store the pcap data
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);
    fflush(temp_file);
    fseek(temp_file, 0, SEEK_SET);

    // Open the temporary file as a pcap file
    pcap_handle = pcap_fopen_offline(temp_file, errbuf);
    if (pcap_handle == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Call the function-under-test
    int result = pcap_next_ex(pcap_handle, &header, &packet);

    // Cleanup
    pcap_close(pcap_handle);
    fclose(temp_file);

    return 0;
}