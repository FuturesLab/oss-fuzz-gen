#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ares.h> // Include the ares header for necessary declarations

// The following line is removed as extern "C" is not needed in C code
// extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize the ares channel
    ares_channel channel; // Changed from ares_channel_t to ares_channel
    int status = ares_init(&channel);
    if (status != ARES_SUCCESS) {
        return 0; // Initialization failed
    }

    // Create a CSV string from the input data
    // Ensure that we create a null-terminated string
    size_t csv_size = (size < 1024) ? size : 1023; // Limit size to avoid buffer overflow
    char csv[1024]; // Buffer for CSV string
    memcpy(csv, data, csv_size);
    csv[csv_size] = '\0'; // Null-terminate the string

    // Call the function under test
    ares_set_servers_ports_csv(channel, csv);

    // Clean up the ares channel

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ares_destroy to ares_gethostbyname
    char ret_ares_get_servers_csv_rcjcm = ares_get_servers_csv(channel);
    char ret_ares_dns_rcode_tostr_zemos = ares_dns_rcode_tostr(0);

    ares_gethostbyname(channel, &ret_ares_dns_rcode_tostr_zemos, ARES_AI_IDN_ALLOW_UNASSIGNED, NULL, (void *)channel);

    // End mutation: Producer.APPEND_MUTATOR

    ares_destroy(channel);

    return 0;
}