#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    hid_t attr_id = H5Acreate2(H5S_ALL, "attr", H5T_NATIVE_INT, H5S_ALL, H5P_DEFAULT, H5P_DEFAULT);
    hid_t mem_type_id = H5T_NATIVE_INT;
    int buffer;

    if (size >= sizeof(int)) {
        buffer = *((int *)data);
    } else {
        buffer = 0; // Default value if data size is insufficient
    }

    herr_t status = H5Awrite(attr_id, mem_type_id, &buffer);

    H5Aclose(attr_id);

    return 0;
}