// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_mdc_config at H5F.c:1772:1 in H5Fpublic.h
// H5Fset_mdc_config at H5F.c:1814:1 in H5Fpublic.h
// H5Fget_mdc_hit_rate at H5F.c:1853:1 in H5Fpublic.h
// H5Freset_mdc_hit_rate_stats at H5F.c:1947:1 in H5Fpublic.h
// H5Fget_mdc_size at H5F.c:1895:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fdelete at H5F.c:1117:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

static void initialize_cache_config(H5AC_cache_config_t *config) {
    config->version = H5AC__CURR_CACHE_CONFIG_VERSION;
    config->rpt_fcn_enabled = 0;
    config->open_trace_file = 0;
    config->close_trace_file = 0;
    strcpy(config->trace_file_name, "");
    config->evictions_enabled = 1;
    config->set_initial_size = 0;
    config->initial_size = 0;
    config->min_clean_fraction = 0.1;
    config->max_size = 1024 * 1024;
    config->min_size = 512 * 1024;
    config->epoch_length = 10000;
    config->incr_mode = H5C_incr__threshold;
    config->lower_hr_threshold = 0.9;
    config->increment = 2.0;
    config->apply_max_increment = 0;
    config->max_increment = 0;
    config->flash_incr_mode = H5C_flash_incr__off;
    config->flash_multiple = 0.0;
    config->flash_threshold = 0.0;
    config->decr_mode = H5C_decr__threshold;
    config->upper_hr_threshold = 0.999;
    config->decrement = 0.9;
    config->apply_max_decrement = 0;
    config->max_decrement = 0;
    config->epochs_before_eviction = 3;
    config->apply_empty_reserve = 0;
    config->empty_reserve = 0.1;
    config->dirty_bytes_threshold = 256 * 1024;
    config->metadata_write_strategy = H5AC_METADATA_WRITE_STRATEGY__PROCESS_0_ONLY;
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    hid_t file_id;
    herr_t status;
    H5AC_cache_config_t config;
    double hit_rate;
    size_t max_size, min_clean_size, cur_size;
    int cur_num_entries;

    // Create a dummy file
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Initialize cache config
    initialize_cache_config(&config);

    // Repeatedly get and set configurations
    for (int i = 0; i < 4; i++) {
        status = H5Fget_mdc_config(file_id, &config);
        if (status < 0) break;
    }

    for (int i = 0; i < 4; i++) {
        status = H5Fset_mdc_config(file_id, &config);
        if (status < 0) break;
    }

    // Get hit rate
    for (int i = 0; i < 2; i++) {
        status = H5Fget_mdc_hit_rate(file_id, &hit_rate);
        if (status < 0) break;
    }

    // Reset hit rate stats
    for (int i = 0; i < 2; i++) {
        status = H5Freset_mdc_hit_rate_stats(file_id);
        if (status < 0) break;
    }

    // Get MDC size
    for (int i = 0; i < 6; i++) {
        status = H5Fget_mdc_size(file_id, &max_size, &min_clean_size, &cur_size, &cur_num_entries);
        if (status < 0) break;
    }

    // Close and delete the file
    H5Fclose(file_id);
    H5Fdelete("./dummy_file", H5P_DEFAULT);

    return 0;
}