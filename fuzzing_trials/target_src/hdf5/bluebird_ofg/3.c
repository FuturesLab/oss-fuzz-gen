#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for the fuzzer
    if (size < 2) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a file and a group to ensure we have a valid hid_t
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }
    
    hid_t group_id = H5Gcreate2(file_id, "/test_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Close the group to prepare for unlinking
    H5Gclose(group_id);

    // Prepare the group name from the input data
    size_t name_len = size - 1;
    char *group_name = (char *)malloc(name_len + 1);
    if (group_name == NULL) {
        H5Fclose(file_id);
        return 0;
    }
    memcpy(group_name, data, name_len);
    group_name[name_len] = '\0';

    // Call the function-under-test
    H5Gunlink(file_id, group_name);

    // Clean up
    free(group_name);
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

    LLVMFuzzerTestOneInput_3(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
