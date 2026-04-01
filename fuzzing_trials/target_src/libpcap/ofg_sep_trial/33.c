#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    pcap_t *pcap;
    pcap_dumper_t *dumper;
    char errbuf[PCAP_ERRBUF_SIZE];
    FILE *file;

    // Initialize pcap with a dummy file and linktype
    pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) {
        return 0;
    }

    // Use a temporary file for dumping
    file = tmpfile();
    if (file == NULL) {
        pcap_close(pcap);
        return 0;
    }

    // Initialize the dumper
    dumper = pcap_dump_fopen(pcap, file);
    if (dumper == NULL) {
        fclose(file);
        pcap_close(pcap);
        return 0;
    }

    // Write the input data to the dumper
    struct pcap_pkthdr header;
    header.ts.tv_sec = 0;
    header.ts.tv_usec = 0;
    header.caplen = size < 65535 ? size : 65535;
    header.len = size < 65535 ? size : 65535;
    pcap_dump((u_char *)dumper, &header, data);

    // Call the function-under-test
    FILE *result_file = pcap_dump_file(dumper);

    // Clean up
    pcap_dump_close(dumper);
    fclose(file);
    pcap_close(pcap);

    return 0;
}