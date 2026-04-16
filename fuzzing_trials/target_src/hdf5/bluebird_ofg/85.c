#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a copy of the data to ensure it is null-terminated
    char *group_name = (char *)malloc(size + 1);
    if (group_name == NULL) {
        return 0;
    }
    memcpy(group_name, data, size);
    group_name[size] = '\0';

    // Initialize a valid HDF5 file and obtain a file identifier
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        free(group_name);
        return 0;
    }

    // Create a group in the file to ensure H5Gopen1 has something to open
    hid_t group_id = H5Gcreate1(file_id, "testgroup", 0);
    if (group_id >= 0) {
        H5Gclose(group_id);
    }

    // Call the function-under-test
    hid_t result = H5Gopen1(file_id, group_name);

    // Cleanup
    if (result >= 0) {
        H5Gclose(result);
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

    LLVMFuzzerTestOneInput_85(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
