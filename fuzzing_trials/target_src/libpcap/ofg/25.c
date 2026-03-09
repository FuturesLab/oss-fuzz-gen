#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    pcap_t *pcap;
    pcap_dumper_t *dumper;
    char errbuf[PCAP_ERRBUF_SIZE];
    FILE *tempfile;

    // Create a temporary file to use with the dumper
    tempfile = tmpfile();
    if (tempfile == NULL) {
        return 0;
    }

    // Open a pcap handle on the provided data
    pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) {
        fclose(tempfile);
        return 0;
    }

    // Open a dumper using the temporary file
    dumper = pcap_dump_fopen(pcap, tempfile);
    if (dumper == NULL) {
        pcap_close(pcap);
        fclose(tempfile);
        return 0;
    }

    // Write the input data to the dumper
    struct pcap_pkthdr header;
    header.ts.tv_sec = 0;
    header.ts.tv_usec = 0;
    header.caplen = size;
    header.len = size;
    pcap_dump((u_char *)dumper, &header, data);

    // Call the function-under-test
    int64_t offset = pcap_dump_ftell64(dumper);

    // Clean up
    pcap_dump_close(dumper);
    pcap_close(pcap);
    fclose(tempfile);

    return 0;
}