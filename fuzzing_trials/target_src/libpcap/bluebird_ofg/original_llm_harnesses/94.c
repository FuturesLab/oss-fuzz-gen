#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    struct pcap_pkthdr *header;
    const u_char *packet_data;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Initialize pcap with a dummy file
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Create a pcap file from the input data
    pcap_dumper_t *dumper = pcap_dump_open(pcap_handle, "dummy.pcap");
    if (dumper == NULL) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Write the input data to the pcap file
    struct pcap_pkthdr pkt_header;
    pkt_header.caplen = size;
    pkt_header.len = size;
    pkt_header.ts.tv_sec = 0;
    pkt_header.ts.tv_usec = 0;
    pcap_dump((u_char *)dumper, &pkt_header, data);
    pcap_dump_close(dumper);

    // Reopen the pcap file for reading
    pcap_t *pcap_handle_read = pcap_open_offline("dummy.pcap", errbuf);
    if (pcap_handle_read == NULL) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Call the function-under-test
    int result = pcap_next_ex(pcap_handle_read, &header, &packet_data);

    // Cleanup
    pcap_close(pcap_handle_read);
    pcap_close(pcap_handle);

    return 0;
}