#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for testing
    if (size < sizeof(hid_t) + 1) {
        return 0;
    }

    // Extract a valid hid_t from the input data
    hid_t file_id = *((hid_t *)data);

    // Allocate a buffer for the file name
    size_t name_size = size - sizeof(hid_t);
    char *name_buffer = (char *)malloc(name_size);
    if (name_buffer == NULL) {
        return 0;
    }

    // Call the function-under-test
    ssize_t result = H5Fget_name(file_id, name_buffer, name_size);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_name to H5Aget_info_by_idx
    hid_t ret_H5Dget_access_plist_psauu = H5Dget_access_plist(0);
    hsize_t ret_H5Dget_storage_size_rvidz = H5Dget_storage_size(0);
    H5A_info_t htkmwbjs;
    memset(&htkmwbjs, 0, sizeof(htkmwbjs));
    herr_t ret_H5Aget_info_by_idx_rsxmn = H5Aget_info_by_idx(ret_H5Dget_access_plist_psauu, name_buffer, 0, 0, ret_H5Dget_storage_size_rvidz, &htkmwbjs, 0);
    // End mutation: Producer.APPEND_MUTATOR
    
    free(name_buffer);

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

    LLVMFuzzerTestOneInput_61(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
