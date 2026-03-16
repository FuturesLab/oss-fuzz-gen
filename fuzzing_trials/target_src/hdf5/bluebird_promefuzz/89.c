#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

#define DUMMY_FILE "./dummy_file"
#define DATASET_NAME "dset"
#define DATASET_SIZE 1024

static void write_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fputs("dummy content", file);
        fclose(file);
    }
}

static herr_t set_mdc_config(hid_t file_id) {
    H5AC_cache_config_t config;
    memset(&config, 0, sizeof(config));
    config.version = H5AC__CURR_CACHE_CONFIG_VERSION;
    config.rpt_fcn_enabled = 0;
    config.open_trace_file = 0;
    config.close_trace_file = 0;
    config.evictions_enabled = 1;
    config.set_initial_size = 1;
    config.initial_size = 1024;
    config.min_clean_fraction = 0.1;
    config.max_size = 2048;
    config.min_size = 512;
    config.epoch_length = 50000;
    config.incr_mode = H5C_incr__threshold;
    config.lower_hr_threshold = 0.8;
    config.increment = 2.0;
    config.apply_max_increment = 1;
    config.max_increment = 512;
    config.flash_incr_mode = H5C_flash_incr__add_space;
    config.flash_multiple = 0.25;
    config.flash_threshold = 0.5;
    config.decr_mode = H5C_decr__age_out_with_threshold;
    config.upper_hr_threshold = 0.999;
    config.decrement = 0.9;
    config.apply_max_decrement = 1;
    config.max_decrement = 256;
    config.epochs_before_eviction = 3;
    config.apply_empty_reserve = 1;
    config.empty_reserve = 0.1;
    config.dirty_bytes_threshold = 256 * 1024;
    config.metadata_write_strategy = H5AC_METADATA_WRITE_STRATEGY__PROCESS_0_ONLY;

    return H5Fset_mdc_config(file_id, &config);
}

int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    if (set_mdc_config(file_id) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hsize_t dims[1] = {DATASET_SIZE};
    hid_t space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t dset_id = H5Dcreate2(file_id, DATASET_NAME, H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    hid_t file_space_id = H5Dget_space(dset_id);
    if (file_space_id < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    int buffer[DATASET_SIZE];
    if (Size >= sizeof(buffer)) {
        memcpy(buffer, Data, sizeof(buffer));
    } else {
        memset(buffer, 0, sizeof(buffer));
    }

    if (H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer) < 0) {
        H5Sclose(file_space_id);
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    if (set_mdc_config(file_id) < 0) {
        H5Sclose(file_space_id);
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    if (H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer) < 0) {
        H5Sclose(file_space_id);
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    H5Dclose(dset_id);

    if (set_mdc_config(file_id) < 0) {
        H5Sclose(file_space_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    dset_id = H5Dcreate2(file_id, DATASET_NAME, H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id >= 0) {
        if (H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer) >= 0) {
            H5Dclose(dset_id);
        }
    }

    H5Sclose(file_space_id);
    H5Sclose(space_id);
    H5Fclose(file_id);
    H5Fdelete(DUMMY_FILE, H5P_DEFAULT);

    return 0;
}