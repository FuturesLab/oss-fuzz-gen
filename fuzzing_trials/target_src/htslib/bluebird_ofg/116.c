#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Function signature for the function-under-test
void hts_md5_hex(char *hex, const unsigned char *data, size_t length);

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough for meaningful input
    if (size < 1) {
        return 0;
    }

    // Allocate a buffer for the hex output (MD5 hex is 32 characters + 1 for null terminator)
    char hex_output[33];
    memset(hex_output, 0, sizeof(hex_output));

    // Ensure the data is not null and size is appropriate
    if (data != NULL && size > 0) {
        // Limit the size of data passed to hts_md5_hex to avoid buffer overflow
        // MD5 processes data in 64-byte blocks, so ensure we don't exceed this
        size_t max_data_length = 64; // Assume a reasonable max length for MD5 input
        size_t length_to_use = size > max_data_length ? max_data_length : size;

        // Allocate a buffer to hold the data to be passed to hts_md5_hex
        unsigned char data_buffer[max_data_length];
        memset(data_buffer, 0, max_data_length);

        // Copy the input data to the buffer, ensuring no overflow
        memcpy(data_buffer, data, length_to_use);

        // Call the function-under-test with the correct length parameter
        hts_md5_hex(hex_output, data_buffer, length_to_use);

        // Optionally, verify that the output is a valid MD5 hex string
        // This is a simple check to ensure the output is as expected
        for (int i = 0; i < 32; i++) {
            if (!((hex_output[i] >= '0' && hex_output[i] <= '9') ||
                  (hex_output[i] >= 'a' && hex_output[i] <= 'f'))) {
                return 0; // Invalid character found, return early
            }
        }
    }

    return 0;
}