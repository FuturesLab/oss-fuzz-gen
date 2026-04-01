#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Define and initialize the parameters for pcap_createsrcstr
    char source[PCAP_BUF_SIZE];
    int type = PCAP_SRC_IFLOCAL; // Use a valid type
    const char *host = "localhost"; // Non-NULL host
    const char *port = "8080"; // Non-NULL port
    const char *name = "eth0"; // Non-NULL name
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure data is not empty and size is sufficient
    if (size < 1) {
        return 0;
    }

    // Copy data to source buffer ensuring it doesn't overflow
    size_t copy_size = size < PCAP_BUF_SIZE ? size : PCAP_BUF_SIZE - 1;
    memcpy(source, data, copy_size);
    source[copy_size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int result = pcap_createsrcstr(source, type, host, port, name, errbuf);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}

#ifdef __cplusplus
}
#endif