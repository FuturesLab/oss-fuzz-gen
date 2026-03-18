#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <sys/time.h> // Include this for the timeval structure

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Initialize variables
    u_char *user_data = (u_char *)data;
    struct pcap_pkthdr pkthdr;
    const u_char *packet_data = data;

    // Ensure size is large enough to fill pcap_pkthdr
    if (size < sizeof(struct pcap_pkthdr)) {
        return 0;
    }

    // Initialize pcap_pkthdr with data
    pkthdr.ts.tv_sec = (long)data[0];
    pkthdr.ts.tv_usec = (long)data[1];
    pkthdr.caplen = size;
    pkthdr.len = size;

    // Call the function-under-test
    pcap_dump(user_data, &pkthdr, packet_data);

    return 0;
}