#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid input
    if (size < 1) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Use the input data to create a group name

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fcreate to H5Acreate_by_name
    hid_t ret_H5Dget_access_plist_fbuzs = H5Dget_access_plist(file_id);
    hid_t ret_H5Dget_access_plist_cxyiy = H5Dget_access_plist(file_id);
    hid_t ret_H5Aget_type_ivbkb = H5Aget_type(0);
    hid_t ret_H5Aget_space_ltsqb = H5Aget_space(0);
    hid_t ret_H5Acreate_by_name_ypmhv = H5Acreate_by_name(file_id, (const char *)"w", (const char *)data, ret_H5Dget_access_plist_fbuzs, file_id, ret_H5Dget_access_plist_cxyiy, ret_H5Aget_type_ivbkb, ret_H5Aget_space_ltsqb);
    // End mutation: Producer.APPEND_MUTATOR
    
    char group_name[256];
    size_t name_length = size < 255 ? size : 255;
    for (size_t i = 0; i < name_length; ++i) {
        group_name[i] = data[i] % 26 + 'A'; // Ensure it's a valid character
    }
    group_name[name_length] = '\0';

    // Call the function-under-test
    hid_t group_id = H5Gcreate1(file_id, group_name, name_length);

    // Close the group and file
    if (group_id >= 0) {
        H5Gclose(group_id);
    }
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_5(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
