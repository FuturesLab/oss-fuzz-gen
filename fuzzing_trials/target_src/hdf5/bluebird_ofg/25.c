#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with
    if (size < sizeof(hid_t) * 4 + sizeof(size_t)) {
        return 0;
    }

    // Initialize variables
    size_t count = 1; // Number of datasets, set to 1 for simplicity
    hid_t dset_ids[1];
    hid_t mem_types[1];
    hid_t mem_spaces[1];
    hid_t file_spaces[1];
    hid_t dxpl_id = *(hid_t *)(data + sizeof(hid_t) * 4); // Data transfer property list

    // Allocate memory for the data buffer
    const void *buf[1];
    buf[0] = data;

    // Initialize HDF5 library
    H5open();

    // Create a simple HDF5 dataset for testing
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hid_t space_id = H5Screate(H5S_SCALAR);
    hid_t dset_id = H5Dcreate(file_id, "dset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Assign dataset and space IDs
    dset_ids[0] = dset_id;
    mem_types[0] = H5T_NATIVE_INT;
    mem_spaces[0] = space_id;
    file_spaces[0] = space_id;

    // Call the function-under-test
    herr_t status = H5Dwrite_multi(count, dset_ids, mem_types, mem_spaces, file_spaces, dxpl_id, buf);

    // Cleanup
    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);
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

    LLVMFuzzerTestOneInput_25(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
