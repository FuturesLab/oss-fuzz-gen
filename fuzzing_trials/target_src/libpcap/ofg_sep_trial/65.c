#include <pcap.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Fuzzer entry point
int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    FILE *file;

    // Initialize a pcap_t handle
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Create a temporary file to use with pcap_dump_fopen
    file = tmpfile();
    if (file == NULL) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Write the data to the temporary file to simulate input
    fwrite(data, 1, size, file);
    rewind(file);

    // Call the function-under-test
    pcap_dumper_t *dumper = pcap_dump_fopen(pcap_handle, file);

    // Clean up
    if (dumper != NULL) {
        pcap_dump_close(dumper);
    }
    fclose(file);
    pcap_close(pcap_handle);

    return 0;
}