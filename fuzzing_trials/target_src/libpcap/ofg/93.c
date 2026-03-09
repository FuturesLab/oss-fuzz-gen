#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern int pcap_init(unsigned int, char *);

int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    unsigned int init_value;
    char init_string[256];

    // Ensure the size is sufficient for our needs
    if (size < sizeof(unsigned int) + 1) {
        return 0;
    }

    // Copy the first part of data to init_value
    memcpy(&init_value, data, sizeof(unsigned int));

    // Copy the rest of the data to init_string, ensuring null-termination
    size_t string_size = size - sizeof(unsigned int);
    if (string_size > 255) {
        string_size = 255;
    }
    memcpy(init_string, data + sizeof(unsigned int), string_size);
    init_string[string_size] = '\0';

    // Call the function-under-test
    pcap_init(init_value, init_string);

    return 0;
}