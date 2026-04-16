#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id;
    hid_t group_id;
    char *group_name;

    // Ensure data is not empty and size is sufficient
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to work with HDF5
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Allocate memory for group_name and ensure it's null-terminated
    group_name = (char *)malloc(size + 1);
    if (group_name == NULL) {
        H5Fclose(file_id);
        return 0;
    }
    memcpy(group_name, data, size);
    group_name[size] = '\0';

    // Create a group to ensure it exists
    group_id = H5Gcreate1(file_id, group_name, 0);
    if (group_id >= 0) {
        H5Gclose(group_id);
    }

    // Call the function-under-test
    group_id = H5Gopen1(file_id, group_name);

    // Clean up
    if (group_id >= 0) {
        H5Gclose(group_id);
    }
    H5Fclose(file_id);
    free(group_name);

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

    LLVMFuzzerTestOneInput_23(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
