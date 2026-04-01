#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    u_char *user;
    struct pcap_pkthdr header;
    const u_char *packet_data;

    // Ensure size is large enough to split into meaningful parts
    if (size < sizeof(struct pcap_pkthdr) + 1) {
        return 0;
    }

    // Allocate memory for user data and packet data
    user = (u_char *)malloc(size);
    if (user == NULL) {
        return 0;
    }
    memcpy(user, data, size);

    // Initialize the pcap_pkthdr structure
    memcpy(&header, data, sizeof(struct pcap_pkthdr));

    // Point packet_data to the remaining part of data
    packet_data = data + sizeof(struct pcap_pkthdr);

    // Call the function-under-test
    pcap_dump(user, &header, packet_data);

    // Clean up
    free(user);

    return 0;
}