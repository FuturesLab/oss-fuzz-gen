#include <stdint.h>
#include <stdio.h>
#include <pcap.h>
#include <inttypes.h>  // Include for PRId64

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure that the data is not NULL and has a minimum size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Open a temporary file to use with pcap_dump_open
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_RAW, 65535);  // Open a dummy pcap handle
    if (pcap == NULL) {
        return 0;
    }

    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        pcap_close(pcap);
        return 0;
    }

    pcap_dumper_t *dumper = pcap_dump_fopen(pcap, temp_file);
    if (dumper == NULL) {
        fclose(temp_file);
        pcap_close(pcap);
        return 0;
    }

    // Call the function-under-test
    int64_t result = pcap_dump_ftell64(dumper);

    // Optionally, print the result for debugging purposes
    printf("Result: %" PRId64 "\n", result);

    // Clean up
    pcap_dump_close(dumper);
    fclose(temp_file);
    pcap_close(pcap);

    return 0;
}