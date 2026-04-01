#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_256(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    H5AC_cache_config_t mdc_config;

    // Ensure the size is sufficient for our needs
    if (size < sizeof(H5AC_cache_config_t)) {
        return 0;
    }

    // Open an HDF5 file to get a valid hid_t
    file_id = H5Fopen("testfile.h5", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Unable to open file, exit
    }

    // Initialize the cache configuration structure
    H5AC_cache_config_t *config = (H5AC_cache_config_t *)data;
    config->version = H5AC__CURR_CACHE_CONFIG_VERSION; // Set a valid version

    // Call the function-under-test
    herr_t status = H5Fset_mdc_config(file_id, config);

    // Close the HDF5 file
    H5Fclose(file_id);

    return 0;
}