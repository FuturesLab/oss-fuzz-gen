#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure data is large enough to create valid strings
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the device and error buffer strings
    char device[256];
    char errbuf[PCAP_ERRBUF_SIZE];

    // Copy data into device and errbuf ensuring null-termination
    size_t device_len = (size < 255) ? size : 255;
    memcpy(device, data, device_len);
    device[device_len] = '\0';

    // Initialize errbuf with some data to avoid it being NULL
    memset(errbuf, 'E', PCAP_ERRBUF_SIZE - 1);
    errbuf[PCAP_ERRBUF_SIZE - 1] = '\0';

    // Call the function-under-test
    pcap_t *handle = pcap_create(device, errbuf);

    // Clean up if handle is not NULL
    if (handle != NULL) {
        pcap_close(handle);
    }

    return 0;
}