#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    // Initialize variables
    unsigned int app_line = __LINE__;
    const char *app_file = __FILE__;
    const char *app_func = __func__;
    unsigned int count = 1;
    size_t num_datasets = 1;

    // Allocate memory for hid_t arrays
    hid_t *mem_type_ids = (hid_t *)malloc(num_datasets * sizeof(hid_t));
    hid_t *mem_space_ids = (hid_t *)malloc(num_datasets * sizeof(hid_t));
    hid_t *file_space_ids = (hid_t *)malloc(num_datasets * sizeof(hid_t));
    hid_t *dataset_ids = (hid_t *)malloc(num_datasets * sizeof(hid_t));

    // Initialize hid_t arrays with some values
    for(size_t i = 0; i < num_datasets; i++) {
        mem_type_ids[i] = H5T_NATIVE_INT;
        mem_space_ids[i] = H5Screate(H5S_SCALAR);
        file_space_ids[i] = H5Screate(H5S_SCALAR);
        dataset_ids[i] = H5Dcreate2(H5P_DEFAULT, "dataset", H5T_NATIVE_INT, H5Screate(H5S_SCALAR), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    }

    hid_t dxpl_id = H5P_DEFAULT;
    hid_t es_id = H5EScreate();

    // Prepare data buffer
    const void **bufs = (const void **)malloc(num_datasets * sizeof(void *));
    bufs[0] = (const void *)data;

    // Call the function-under-test
    herr_t result = H5Dwrite_multi_async(count, dataset_ids, mem_type_ids, mem_space_ids, file_space_ids, dxpl_id, bufs, es_id);

    // Clean up
    for(size_t i = 0; i < num_datasets; i++) {
        H5Sclose(mem_space_ids[i]);
        H5Sclose(file_space_ids[i]);
        H5Dclose(dataset_ids[i]);
    }
    free(mem_type_ids);
    free(mem_space_ids);
    free(file_space_ids);
    free(dataset_ids);
    free(bufs);
    H5ESclose(es_id);

    return 0;
}