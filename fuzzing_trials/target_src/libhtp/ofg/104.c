#include <stdint.h>
#include <stddef.h>
#include "/src/libhtp/htp/htp.h"  // Correct path for the htp.h file

// Replace the incorrect include with the correct one
#include "/src/libhtp/htp/htp_transaction.c"

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a method number
    if (size < sizeof(enum htp_method_t)) {
        return 0;
    }

    // Initialize htp_tx_t object
    htp_tx_t tx;
    // Initialize method number from input data
    enum htp_method_t method_number = *(enum htp_method_t *)data;

    // Call the function-under-test
    htp_tx_req_set_method_number(&tx, method_number);

    return 0;
}