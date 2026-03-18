#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    // Check if size is sufficient to proceed
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to obtain a valid file_id
    hid_t file_id = H5Fcreate("temp.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create a file, return early
    }

    // Initialize the parameters for H5Fget_mdc_config
    H5AC_cache_config_t config;

    // Ensure the config version is set correctly
    config.version = H5AC__CURR_CACHE_CONFIG_VERSION;

    // Call the function-under-test
    herr_t result = H5Fget_mdc_config(file_id, &config);

    // Close the file to clean up
    H5Fclose(file_id);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}