#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "/src/libhtp/htp/htp.h"  // Include the necessary header for htp_tx_req_get_param

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Initialize the htp_tx_t structure
    htp_tx_t tx;
    memset(&tx, 0, sizeof(htp_tx_t)); // Zero-initialize the structure

    // Ensure that size is non-zero to avoid passing a NULL pointer for the parameter name
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the parameter name, ensuring it is null-terminated
    char *param_name = (char *)malloc(size + 1);
    if (param_name == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(param_name, data, size);
    param_name[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    htp_param_t *result = htp_tx_req_get_param(&tx, param_name, size);

    // Clean up
    free(param_name);

    // The result is not used further, as we're just checking for memory corruption
    return 0;
}