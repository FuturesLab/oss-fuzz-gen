#include <stdint.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    int datalink_type;

    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first 4 bytes of the input data as an integer
    datalink_type = *(const int *)data;

    // Call the function-under-test
    const char *description = pcap_datalink_val_to_description(datalink_type);

    // Optionally, you can do something with the description, like printing it
    // but for fuzzing purposes, it's enough to just call the function.
    (void)description; // Suppress unused variable warning

    return 0;
}