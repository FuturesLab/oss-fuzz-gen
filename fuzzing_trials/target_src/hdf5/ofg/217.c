#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_217(const uint8_t *data, size_t size) {
    // Initialize parameters for the function-under-test
    size_t count = 1;
    size_t num_datasets = 1;

    // Allocate and initialize hid_t arrays
    hid_t *mem_type_ids = (hid_t *)malloc(num_datasets * sizeof(hid_t));
    hid_t *mem_space_ids = (hid_t *)malloc(num_datasets * sizeof(hid_t));
    hid_t *file_space_ids = (hid_t *)malloc(num_datasets * sizeof(hid_t));
    hid_t *dset_ids = (hid_t *)malloc(num_datasets * sizeof(hid_t));

    for (size_t i = 0; i < num_datasets; ++i) {
        mem_type_ids[i] = H5T_NATIVE_INT;
        mem_space_ids[i] = H5Screate(H5S_SCALAR);
        file_space_ids[i] = H5Screate(H5S_SCALAR);
        dset_ids[i] = H5Dcreate2(H5P_DEFAULT, "dataset", H5T_NATIVE_INT, mem_space_ids[i], H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    }

    hid_t dxpl_id = H5P_DEFAULT;
    hid_t es_id = H5P_DEFAULT; // Use a default event stack ID

    // Allocate and initialize data buffer
    void **bufs = (void **)malloc(num_datasets * sizeof(void *));
    for (size_t i = 0; i < num_datasets; ++i) {
        bufs[i] = (void *)data; // Use input data as buffer
    }

    // Call the function-under-test
    herr_t result = H5Dwrite_multi_async(count, dset_ids, mem_type_ids, mem_space_ids, file_space_ids, dxpl_id, (const void **)bufs, es_id);

    // Clean up
    for (size_t i = 0; i < num_datasets; ++i) {
        H5Sclose(mem_space_ids[i]);
        H5Sclose(file_space_ids[i]);
        H5Dclose(dset_ids[i]);
    }
    free(mem_type_ids);
    free(mem_space_ids);
    free(file_space_ids);
    free(dset_ids);
    free(bufs);

    return 0;
}