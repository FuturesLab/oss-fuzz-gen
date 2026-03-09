#include "pcap/pcap.h"
#include <stdint.h>
#include <stddef.h>
#include "stdlib.h"
#include "string.h"

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    pcap_t *pcap;
    pcap_dumper_t *dumper;
    char errbuf[PCAP_ERRBUF_SIZE];
    char filename[256];

    // Initialize pcap with a dummy value
    pcap = pcap_open_dead(DLT_RAW, 65535);
    if (pcap == NULL) {
        return 0;
    }

    // Ensure the filename is null-terminated and non-empty
    if (size > 0 && size < sizeof(filename)) {
        memcpy(filename, data, size);
        filename[size] = '\0';
    } else {
        strncpy(filename, "default_filename.pcap", sizeof(filename));
        filename[sizeof(filename) - 1] = '\0';
    }

    // Call the function-under-test
    dumper = pcap_dump_open_append(pcap, filename);

    // Clean up
    if (dumper != NULL) {
        pcap_dump_close(dumper);
    }
    pcap_close(pcap);

    return 0;
}