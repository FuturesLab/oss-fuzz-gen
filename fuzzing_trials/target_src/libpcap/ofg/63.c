#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    pcap_t *handle;
    struct bpf_program fp;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Initialize the pcap_t handle
    handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (handle == NULL) {
        return 0;
    }

    // Ensure that the data is null-terminated before using it as a filter expression
    char *filter_exp = (char *)malloc(size + 1);
    if (filter_exp == NULL) {
        pcap_close(handle);
        return 0;
    }
    memcpy(filter_exp, data, size);
    filter_exp[size] = '\0';

    // Initialize the bpf_program structure with the fuzzed filter expression
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        free(filter_exp);
        pcap_close(handle);
        return 0;
    }

    // Call the function-under-test
    int result = pcap_setfilter(handle, &fp);

    // Cleanup
    pcap_freecode(&fp);
    pcap_close(handle);
    free(filter_exp);

    return result;
}