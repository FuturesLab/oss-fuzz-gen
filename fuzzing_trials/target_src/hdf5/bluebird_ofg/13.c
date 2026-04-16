#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    hsize_t filesize;
    herr_t status;

    // Create a temporary file for testing
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit early
    }

    // Simulate writing data to the file to ensure it's not empty
    if (size > 0) {
        hid_t dataspace_id = H5Screate_simple(1, &size, NULL);
        hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_UINT8, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        H5Dwrite(dataset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Dclose with H5Dflush
        H5Dflush(dataset_id);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
        H5Sclose(dataspace_id);
    }

    // Call the function-under-test
    status = H5Fget_filesize(file_id, &filesize);

    // Close the file
    H5Fclose(file_id);

    // Return success
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

    LLVMFuzzerTestOneInput_13(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
