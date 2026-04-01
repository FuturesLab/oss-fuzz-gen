#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "/src/libhtp/htp/htp.h" // Correct path to the header file

// Remove the 'extern "C"' linkage specification for C++ compatibility
int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract meaningful inputs
    if (size < 10) {
        return 0;
    }

    // Initialize the htp_tx_t structure
    htp_tx_t tx;
    memset(&tx, 0, sizeof(htp_tx_t));

    // Define and initialize header name and value
    const char *header_name = (const char *)data;
    size_t header_name_len = size / 4; // Use a quarter of the data for the header name

    const char *header_value = (const char *)(data + header_name_len);
    size_t header_value_len = size / 4; // Use another quarter of the data for the header value

    // Ensure null termination for strings
    char name_buffer[256];
    char value_buffer[256];
    memcpy(name_buffer, header_name, header_name_len < 255 ? header_name_len : 255);
    name_buffer[header_name_len < 255 ? header_name_len : 255] = '\0';

    memcpy(value_buffer, header_value, header_value_len < 255 ? header_value_len : 255);
    value_buffer[header_value_len < 255 ? header_value_len : 255] = '\0';

    // Define and initialize the allocation strategy
    enum htp_alloc_strategy_t alloc_strategy = HTP_ALLOC_REUSE;

    // Call the function-under-test
    htp_status_t status = htp_tx_res_set_header(&tx, name_buffer, header_name_len, value_buffer, header_value_len, alloc_strategy);

    // Return 0 as required by LLVMFuzzerTestOneInput
    return 0;
}