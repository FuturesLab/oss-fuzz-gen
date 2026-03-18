#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <pcap/bpf.h> // Include the header for pcap_file_header definition

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    pcap_t *pcap;
    pcap_dumper_t *dumper;
    char errbuf[PCAP_ERRBUF_SIZE];
    FILE *file;

    if (size < sizeof(struct pcap_file_header)) {
        return 0; // Not enough data to form a valid pcap header
    }

    // Create a temporary file to use with pcap_dump_open
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file as a pcap_t
    pcap = pcap_fopen_offline(tempFile, errbuf);
    if (pcap == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Open a dumper for the pcap
    dumper = pcap_dump_open(pcap, "dummy_output.pcap");
    if (dumper == NULL) {
        pcap_close(pcap);
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    file = pcap_dump_file(dumper);

    // Clean up
    pcap_dump_close(dumper);
    pcap_close(pcap);
    fclose(tempFile);

    return 0;
}