#include <stdint.h>
#include <stddef.h>
#include "/src/libhtp/htp/htp.h" // Ensure this header provides necessary declarations

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    htp_tx_t tx;
    enum htp_method_t method_number; // Use 'enum' to declare htp_method_t

    // Ensure size is sufficient to extract a method number
    if (size < sizeof(enum htp_method_t)) {
        return 0;
    }

    // Initialize method_number from the input data
    method_number = *(enum htp_method_t *)data;

    // Call the function-under-test
    htp_tx_req_set_method_number(&tx, method_number);

    return 0;
}

#ifdef __cplusplus
}
#endif