// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fset_mdc_config at H5F.c:1814:1 in H5Fpublic.h
// H5Freset_mdc_hit_rate_stats at H5F.c:1947:1 in H5Fpublic.h
// H5Fget_mdc_size at H5F.c:1895:1 in H5Fpublic.h
// H5Fget_mdc_hit_rate at H5F.c:1853:1 in H5Fpublic.h
// H5Fget_mdc_config at H5F.c:1772:1 in H5Fpublic.h
// H5Fget_mdc_image_info at H5F.c:2567:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>
#include <H5ACpublic.h>

static hid_t create_dummy_file() {
    hid_t file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    }
    return file_id;
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(H5AC_cache_config_t)) return 0;

    hid_t file_id = create_dummy_file();
    if (file_id < 0) return 0;

    H5AC_cache_config_t config;
    memcpy(&config, Data, sizeof(H5AC_cache_config_t));
    config.version = H5AC__CURR_CACHE_CONFIG_VERSION;

    H5Fset_mdc_config(file_id, &config);

    H5Freset_mdc_hit_rate_stats(file_id);

    size_t max_size, min_clean_size, cur_size;
    int cur_num_entries;
    H5Fget_mdc_size(file_id, &max_size, &min_clean_size, &cur_size, &cur_num_entries);

    double hit_rate;
    H5Fget_mdc_hit_rate(file_id, &hit_rate);

    H5Fget_mdc_config(file_id, &config);

    haddr_t image_addr;
    hsize_t image_size;
    H5Fget_mdc_image_info(file_id, &image_addr, &image_size);

    H5Fclose(file_id);
    return 0;
}