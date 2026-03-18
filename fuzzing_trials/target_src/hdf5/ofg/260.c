#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <H5ACpublic.h>

int LLVMFuzzerTestOneInput_260(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id;
    H5AC_cache_config_t cache_config;

    // Ensure the size is sufficient for our needs
    if (size < sizeof(H5AC_cache_config_t)) {
        return 0;
    }

    // Initialize the cache_config structure with some default values
    cache_config.version = H5AC__CURR_CACHE_CONFIG_VERSION;
    cache_config.rpt_fcn_enabled = 1;
    cache_config.open_trace_file = 0;
    cache_config.close_trace_file = 0;
    cache_config.trace_file_name[0] = '\0';
    cache_config.evictions_enabled = 1;
    cache_config.set_initial_size = 0;
    cache_config.initial_size = 1024 * 1024;
    cache_config.min_clean_fraction = 0.5;
    cache_config.max_size = 16 * 1024 * 1024;
    cache_config.min_size = 1 * 1024 * 1024;
    cache_config.epoch_length = 50000;

    // Create a new HDF5 file to get a valid hid_t
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function under test
    H5Fset_mdc_config(file_id, &cache_config);

    // Close the file
    H5Fclose(file_id);

    return 0;
}