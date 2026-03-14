#include <stdint.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    pcap_if_t *devs = NULL;
    pcap_if_t *current = NULL;
    pcap_if_t *previous = NULL;

    // Allocate memory for devices
    for (size_t i = 0; i < size; ++i) {
        current = (pcap_if_t *)malloc(sizeof(pcap_if_t));
        if (current == NULL) {
            break;
        }
        current->next = NULL;
        current->name = (char *)data;  // Use input data as name
        current->description = (char *)data;  // Use input data as description
        current->addresses = NULL;
        current->flags = 0;

        if (previous != NULL) {
            previous->next = current;
        } else {
            devs = current;
        }
        previous = current;
    }

    // Call the function-under-test
    pcap_freealldevs(devs);

    return 0;
}