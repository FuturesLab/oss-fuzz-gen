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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Fpublic.h"
#include "H5Ppublic.h"

static void initialize_cache_config(H5AC_cache_config_t *config) {
    config->version = H5AC__CURR_CACHE_CONFIG_VERSION;
    config->rpt_fcn_enabled = 0;
    config->open_trace_file = 0;
    config->close_trace_file = 0;
    strcpy(config->trace_file_name, "");
    config->evictions_enabled = 1;
    config->set_initial_size = 0;
    config->initial_size = 1024 * 1024;
    config->min_clean_fraction = 0.5;
    config->max_size = 16 * 1024 * 1024;
    config->min_size = 512 * 1024;
    config->epoch_length = 50000;
    config->incr_mode = H5C_incr__threshold;
    config->lower_hr_threshold = 0.9;
    config->increment = 2.0;
    config->apply_max_increment = 1;
    config->max_increment = 4 * 1024 * 1024;
    config->flash_incr_mode = H5C_flash_incr__add_space;
    config->flash_multiple = 1.0;
    config->flash_threshold = 0.25;
    config->decr_mode = H5C_decr__age_out_with_threshold;
    config->upper_hr_threshold = 0.999;
    config->decrement = 0.9;
    config->apply_max_decrement = 1;
    config->max_decrement = 1 * 1024 * 1024;
    config->epochs_before_eviction = 3;
    config->apply_empty_reserve = 1;
    config->empty_reserve = 0.1;
    config->dirty_bytes_threshold = 256 * 1024;
    config->metadata_write_strategy = H5AC_METADATA_WRITE_STRATEGY__PROCESS_0_ONLY;
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    H5AC_cache_config_t config;
    initialize_cache_config(&config);

    for (int i = 0; i < 4; i++) {
        H5Fget_mdc_config(file_id, &config);
    }

    for (int i = 0; i < 4; i++) {
        H5Fset_mdc_config(file_id, &config);
    }

    double hit_rate;
    for (int i = 0; i < 2; i++) {
        H5Fget_mdc_hit_rate(file_id, &hit_rate);
    }

    for (int i = 0; i < 2; i++) {
        H5Freset_mdc_hit_rate_stats(file_id);
    }

    size_t max_size, min_clean_size, cur_size;
    int cur_num_entries;
    for (int i = 0; i < 6; i++) {
        H5Fget_mdc_size(file_id, &max_size, &min_clean_size, &cur_size, &cur_num_entries);
    }

    H5Fclose(file_id);
    H5Fdelete("./dummy_file", H5P_DEFAULT);

    return 0;
}