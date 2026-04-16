#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for two null-terminated strings
    if (size < 3) return 0; // At least 3 bytes needed for two 1-char strings and two null terminators

    // Create a file and a group to work with
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

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

    LLVMFuzzerTestOneInput_10(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
