#include <stdint.h>
#include "hdf5.h"
#include <stdio.h>  // Include this for snprintf

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    hid_t file_id = H5I_INVALID_HID;

    // Check if the data size is sufficient to create a valid file name
    if (size > 0 && size < 255) {
        // Create a temporary file name from the input data
        char filename[256];
        snprintf(filename, sizeof(filename), "/tmp/fuzz_hdf5_%.*s.h5", (int)size, data);

        // Create a new HDF5 file using the filename
        file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        if (file_id >= 0) {
            // Call the function-under-test
            H5Fclear_elink_file_cache(file_id);

            // Close the file
            H5Fclose(file_id);
        }
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

    LLVMFuzzerTestOneInput_67(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
