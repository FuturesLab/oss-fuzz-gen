// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dread_multi_async at H5D.c:1139:1 in H5Dpublic.h
// H5Dwrite_multi_async at H5D.c:1449:1 in H5Dpublic.h
// H5Dwrite_async at H5D.c:1376:1 in H5Dpublic.h
// H5Dset_extent_async at H5D.c:2015:1 in H5Dpublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Dclose_async at H5D.c:493:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"

static void initialize_hid_t_array(hid_t *array, size_t count) {
    for (size_t i = 0; i < count; i++) {
        array[i] = (hid_t)(i + 1); // Simple initialization
    }
}

static void initialize_buffer_array(void **buf, size_t count, size_t buf_size) {
    for (size_t i = 0; i < count; i++) {
        buf[i] = malloc(buf_size);
        if (buf[i]) {
            memset(buf[i], 0, buf_size); // Zero-initialize buffer
        }
    }
}

static void free_buffer_array(void **buf, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(buf[i]);
    }
}

int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    size_t count = Data[0] % 5 + 1; // Limit count to a small number for simplicity

    hid_t dset_id[count];
    hid_t mem_type_id[count];
    hid_t mem_space_id[count];
    hid_t file_space_id[count];
    hid_t dxpl_id = 0;
    hid_t es_id = 0;
    void *buf[count];

    initialize_hid_t_array(dset_id, count);
    initialize_hid_t_array(mem_type_id, count);
    initialize_hid_t_array(mem_space_id, count);
    initialize_hid_t_array(file_space_id, count);
    initialize_buffer_array(buf, count, 256);

    herr_t status;

    // Fuzz H5Dread_multi_async
    status = H5Dread_multi_async(count, dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
    if (status < 0) {
        fprintf(stderr, "H5Dread_multi_async failed\n");
    }

    // Fuzz H5Dwrite_multi_async
    status = H5Dwrite_multi_async(count, dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, (const void **)buf, es_id);
    if (status < 0) {
        fprintf(stderr, "H5Dwrite_multi_async failed\n");
    }

    // Fuzz H5Dwrite_async
    status = H5Dwrite_async(dset_id[0], mem_type_id[0], mem_space_id[0], file_space_id[0], dxpl_id, buf[0], es_id);
    if (status < 0) {
        fprintf(stderr, "H5Dwrite_async failed\n");
    }

    // Fuzz H5Dset_extent_async
    hsize_t size[] = {10, 20, 30}; // Example size
    status = H5Dset_extent_async(dset_id[0], size, es_id);
    if (status < 0) {
        fprintf(stderr, "H5Dset_extent_async failed\n");
    }

    // Fuzz H5Dread_async
    status = H5Dread_async(dset_id[0], mem_type_id[0], mem_space_id[0], file_space_id[0], dxpl_id, buf[0], es_id);
    if (status < 0) {
        fprintf(stderr, "H5Dread_async failed\n");
    }

    // Fuzz H5Dclose_async
    status = H5Dclose_async(dset_id[0], es_id);
    if (status < 0) {
        fprintf(stderr, "H5Dclose_async failed\n");
    }

    free_buffer_array(buf, count);

    return 0;
}