#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    pcap_t *handle;
    int *dlt_list = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a fake pcap handle using pcap_open_dead
    handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max snaplen

    if (handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = pcap_list_datalinks(handle, &dlt_list);

    // Clean up
    if (dlt_list != NULL) {
        pcap_free_datalinks(dlt_list);
    }
    pcap_close(handle);

    return 0;
}