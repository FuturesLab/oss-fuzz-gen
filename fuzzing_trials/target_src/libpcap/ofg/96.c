#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // Include for FILE and tmpfile

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle = NULL;
    struct pcap_pkthdr *header = NULL;
    const u_char *packet_data = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Initialize a pcap_t handle using pcap_open_dead
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Create a temporary file to simulate a pcap file
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Associate the pcap handle with the temporary file
    pcap_t *offline_handle = pcap_fopen_offline(temp_file, errbuf);
    if (offline_handle == NULL) {
        pcap_close(pcap_handle);
        fclose(temp_file);
        return 0;
    }

    // Call the function-under-test
    int result = pcap_next_ex(offline_handle, &header, &packet_data);

    // Cleanup
    pcap_close(offline_handle);
    pcap_close(pcap_handle);
    fclose(temp_file);

    return 0;
}