#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function-under-test
    hid_t file_id;
    haddr_t eoa_address;

    // Ensure that the size of the data is sufficient to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Use the data to create a valid hid_t
    file_id = *((hid_t *)data);

    // Call the function-under-test
    herr_t result = H5Fget_eoa(file_id, &eoa_address);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}