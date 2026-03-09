#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the parameters
    if (size < 6) {
        return 0;
    }

    // Allocate and initialize parameters
    char source[256];
    int type = (int)data[0];  // Use the first byte for the type
    const char *host = (const char *)&data[1];  // Use the second byte onward for host
    const char *port = (const char *)&data[2];  // Use the third byte onward for port
    const char *name = (const char *)&data[3];  // Use the fourth byte onward for name
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure null-termination for strings
    size_t host_len = strnlen(host, size - 1);
    size_t port_len = strnlen(port, size - 2);
    size_t name_len = strnlen(name, size - 3);

    if (host_len < size - 1) {
        ((char *)host)[host_len] = '\0';
    }
    if (port_len < size - 2) {
        ((char *)port)[port_len] = '\0';
    }
    if (name_len < size - 3) {
        ((char *)name)[name_len] = '\0';
    }

    // Call the function-under-test
    pcap_createsrcstr(source, type, host, port, name, errbuf);

    return 0;
}