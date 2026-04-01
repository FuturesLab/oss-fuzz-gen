#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    struct pcap_pkthdr *header;
    const u_char *packet_data;
    char errbuf[PCAP_ERRBUF_SIZE];
    
    // Create a temporary file to write the data
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }
    
    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Open the temporary file as a pcap file
    pcap_handle = pcap_fopen_offline(temp_file, errbuf);
    if (pcap_handle == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Call the function-under-test
    int result = pcap_next_ex(pcap_handle, &header, &packet_data);

    // Clean up
    pcap_close(pcap_handle);
    fclose(temp_file);

    return 0;
}