#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Fuzzing harness for pcap_activate
int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Initialize a pcap_t structure
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);

    if (handle == NULL) {
        return 0;
    }

    // Simulate a pcap file in memory using the input data
    pcap_dumper_t *dumper = pcap_dump_open(handle, "/dev/null");
    if (dumper == NULL) {
        pcap_close(handle);
        return 0;
    }

    struct pcap_pkthdr header;
    header.caplen = size;
    header.len = size;
    header.ts.tv_sec = 0;
    header.ts.tv_usec = 0;

    if (size > 0) {
        pcap_dump((u_char *)dumper, &header, data);
    }

    // Call the function-under-test
    int result = pcap_activate(handle);

    // Clean up
    pcap_dump_close(dumper);
    pcap_close(handle);

    return 0;
}