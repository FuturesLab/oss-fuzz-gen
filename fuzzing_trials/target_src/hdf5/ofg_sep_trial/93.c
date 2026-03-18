#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < sizeof(hid_t) * 4 + sizeof(size_t)) {
        return 0;
    }

    // Extract the number of datasets from the data
    size_t num_datasets = (size_t)data[0] % 5 + 1; // Limit to a small number for simplicity

    // Allocate memory for the arrays of hid_t
    hid_t *dset_id = (hid_t *)malloc(num_datasets * sizeof(hid_t));
    hid_t *mem_type_id = (hid_t *)malloc(num_datasets * sizeof(hid_t));
    hid_t *mem_space_id = (hid_t *)malloc(num_datasets * sizeof(hid_t));
    hid_t *file_space_id = (hid_t *)malloc(num_datasets * sizeof(hid_t));

    // Initialize the arrays with non-NULL values
    for (size_t i = 0; i < num_datasets; ++i) {
        dset_id[i] = (hid_t)(data[i % size] + 1); // Ensure non-zero
        mem_type_id[i] = (hid_t)(data[(i + 1) % size] + 1); // Ensure non-zero
        mem_space_id[i] = (hid_t)(data[(i + 2) % size] + 1); // Ensure non-zero
        file_space_id[i] = (hid_t)(data[(i + 3) % size] + 1); // Ensure non-zero
    }

    // Extract the plist_id from the data
    hid_t plist_id = (hid_t)(data[4 % size] + 1); // Ensure non-zero

    // Prepare the buffer for the data
    const void **buf = (const void **)malloc(num_datasets * sizeof(void *));
    for (size_t i = 0; i < num_datasets; ++i) {
        buf[i] = (const void *)(data + i);
    }

    // Call the function-under-test
    herr_t result = H5Dwrite_multi(num_datasets, dset_id, mem_type_id, mem_space_id, file_space_id, plist_id, buf);

    // Free the allocated memory
    free(dset_id);
    free(mem_type_id);
    free(mem_space_id);
    free(file_space_id);
    free(buf);

    return 0;
}