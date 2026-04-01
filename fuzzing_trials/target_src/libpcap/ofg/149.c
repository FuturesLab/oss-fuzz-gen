#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Remove the 'extern "C"' linkage specification for C++ as this code is intended to be compiled as C
int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    u_char *user;
    struct pcap_pkthdr pkthdr;
    const u_char *packet_data;

    // Ensure size is sufficient to populate pcap_pkthdr and packet_data
    if (size < sizeof(struct pcap_pkthdr) + 1) {
        return 0;
    }

    // Allocate memory for user and packet_data
    user = (u_char *)malloc(size);
    if (user == NULL) {
        return 0;
    }
    memcpy(user, data, size);

    // Initialize pkthdr with some values
    pkthdr.ts.tv_sec = 0;
    pkthdr.ts.tv_usec = 0;
    pkthdr.caplen = size - sizeof(struct pcap_pkthdr);
    pkthdr.len = pkthdr.caplen;

    // Point packet_data to the correct location in the data buffer
    packet_data = data + sizeof(struct pcap_pkthdr);

    // Call the function-under-test
    pcap_dump(user, &pkthdr, packet_data);

    // Free allocated memory
    free(user);

    return 0;
}