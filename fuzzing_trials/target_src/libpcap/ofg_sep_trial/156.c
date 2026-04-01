#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated
    char *datalink_name = (char *)malloc(size + 1);
    if (datalink_name == NULL) {
        return 0; // If malloc fails, return immediately
    }
    memcpy(datalink_name, data, size);
    datalink_name[size] = '\0';

    // Call the function-under-test
    int result = pcap_datalink_name_to_val(datalink_name);

    // Clean up
    free(datalink_name);

    return 0;
}