#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    if (size < sizeof(hid_t)) {
        return 0;
    }
    
    hid_t dataset_id = *((hid_t*)data);

    // Ensure the dataset_id is a valid HDF5 identifier
    if (H5Iis_valid(dataset_id)) {
        hid_t datatype_id = H5Dget_type(dataset_id);

        // If the datatype_id is valid, close it to prevent resource leaks
        if (H5Iis_valid(datatype_id)) {
            H5Tclose(datatype_id);
        }
    }

    return 0;
}