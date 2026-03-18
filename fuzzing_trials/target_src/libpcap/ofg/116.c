#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Declare and initialize a pcap_if_t pointer
    pcap_if_t *alldevs = NULL;
    pcap_if_t *dev = NULL;

    // Allocate memory for a single pcap_if_t structure
    dev = (pcap_if_t *)malloc(sizeof(pcap_if_t));
    if (dev == NULL) {
        return 0;
    }

    // Ensure that the name and description are not NULL
    dev->name = (char *)malloc(10);
    dev->description = (char *)malloc(20);
    if (dev->name == NULL || dev->description == NULL) {
        free(dev);
        return 0;
    }

    // Assign some non-NULL values to the name and description
    snprintf(dev->name, 10, "eth0");
    snprintf(dev->description, 20, "Ethernet Interface");

    // Set the next pointer to NULL to indicate the end of the list
    dev->next = NULL;

    // Point alldevs to the allocated device
    alldevs = dev;

    // Call the function under test
    pcap_freealldevs(alldevs);

    // Free allocated memory
    free(dev->name);
    free(dev->description);
    free(dev);

    return 0;
}