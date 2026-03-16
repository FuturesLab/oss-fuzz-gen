#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for two null-terminated strings
    if (size < 3) {
        return 0;
    } // At least 3 bytes needed for two 1-char strings and two null terminators

    // Create a file and a group to work with
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fcreate to H5Fget_mdc_size
    size_t arbcnvgm = -1;
    size_t szesuunv = 0;
    size_t cuhjnpey = 0;
    int upphqmcq = 64;


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fcreate to H5Gset_comment

    herr_t ret_H5Gset_comment_aerqo = H5Gset_comment(file_id, NULL, (const char *)data);

    // End mutation: Producer.APPEND_MUTATOR

    herr_t ret_H5Fget_mdc_size_kwvrw = H5Fget_mdc_size(file_id, &arbcnvgm, &szesuunv, &cuhjnpey, &upphqmcq);

    // End mutation: Producer.APPEND_MUTATOR

    hid_t group_id = H5Gcreate2(file_id, "/group1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Split the input data into two strings
    size_t middle = size / 2;
    char *src_name = (char *)malloc(middle + 1);
    char *dst_name = (char *)malloc(size - middle + 1);

    if (!src_name || !dst_name) {
        free(src_name);
        free(dst_name);
        H5Gclose(group_id);
        H5Fclose(file_id);
        return 0;
    }

    memcpy(src_name, data, middle);
    src_name[middle] = '\0';

    memcpy(dst_name, data + middle, size - middle);
    dst_name[size - middle] = '\0';

    // Call the function-under-test
    herr_t status = H5Gmove(group_id, src_name, dst_name);

    // Clean up
    free(src_name);
    free(dst_name);
    H5Gclose(group_id);
    H5Fclose(file_id);

    return 0;
}