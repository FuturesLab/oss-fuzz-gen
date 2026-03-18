#include <pcap/pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for our needs
    if (size < 10) {
        return 0;
    }

    // Prepare the parameters for pcap_open_live
    char dev[6];
    int snaplen = (int)data[0];
    int promisc = (int)data[1];
    int to_ms = (int)data[2];
    char errbuf[PCAP_ERRBUF_SIZE];

    // Copy the device name from the data
    memcpy(dev, data + 3, 5);
    dev[5] = '\0'; // Null-terminate the device name

    // Call the function-under-test
    pcap_t *handle = pcap_open_live(dev, snaplen, promisc, to_ms, errbuf);

    // If the handle is valid, close it
    if (handle != NULL) {
        pcap_close(handle);
    }

    return 0;
}