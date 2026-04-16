#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"
#include "/src/hdf5/src/H5Fpublic.h"

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to extract parameters
    if (size < 11) {
        return 0;
    }

    // Extract parameters from the data
    const char *file_name = (const char *)data;
    unsigned int create_flags = *(unsigned int *)(data + 2);
    unsigned int access_flags = *(unsigned int *)(data + 7);
    hid_t fcpl_id = (hid_t)data[8];
    hid_t fapl_id = (hid_t)data[9];
    hid_t es_id = (hid_t)data[10];

    // Call the function-under-test with the correct number of arguments
    hid_t file_id = H5Fcreate_async(file_name, create_flags, fcpl_id, fapl_id, es_id);

    // Close the file if it was created successfully
    if (file_id >= 0) {
        H5Fclose(file_id);
    }

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

    LLVMFuzzerTestOneInput_54(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
