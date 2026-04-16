#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_name to H5Dread_chunk2
    hid_t ret_H5Fget_create_plist_uypgj = H5Fget_create_plist(0);
    hid_t ret_H5Fget_create_plist_puiub = H5Fget_create_plist(0);
    uint32_t rvcqxfpe = 1;
    size_t ynfowjfh = size;
    herr_t ret_H5Dread_chunk2_qucpt = H5Dread_chunk2(ret_H5Fget_create_plist_uypgj, ret_H5Fget_create_plist_puiub, NULL, &rvcqxfpe, (void *)name_buffer, &ynfowjfh);
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

    LLVMFuzzerTestOneInput_76(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
