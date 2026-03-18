// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dflush at H5D.c:2055:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dwrite_multi at H5D.c:1419:1 in H5Dpublic.h
// H5Dscatter at H5D.c:1547:1 in H5Dpublic.h
// H5Dset_extent at H5D.c:1991:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

static hid_t create_dummy_file() {
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Error creating dummy file.\n");
        exit(EXIT_FAILURE);
    }
    return file_id;
}

static hid_t create_dummy_dataset(hid_t file_id) {
    hsize_t dims[2] = {10, 10};
    hid_t dataspace_id = H5Screate_simple(2, dims, NULL);
    hid_t dataset_id = H5Dcreate2(file_id, "/dset", H5T_NATIVE_INT, dataspace_id, 
                                  H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Sclose(dataspace_id);
    if (dataset_id < 0) {
        fprintf(stderr, "Error creating dummy dataset.\n");
        exit(EXIT_FAILURE);
    }
    return dataset_id;
}

static void write_dummy_data(hid_t dataset_id) {
    int data[10][10];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            data[i][j] = i * 10 + j;
    if (H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data) < 0) {
        fprintf(stderr, "Error writing dummy data.\n");
        exit(EXIT_FAILURE);
    }
}

int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    hid_t file_id = create_dummy_file();
    hid_t dataset_id = create_dummy_dataset(file_id);
    write_dummy_data(dataset_id);

    // Prepare buffers and identifiers
    hid_t mem_type_id = H5T_NATIVE_INT;
    hid_t mem_space_id = H5S_ALL;
    hid_t file_space_id = H5S_ALL;
    hid_t dxpl_id = H5P_DEFAULT;
    int buf[10][10];
    
    // Fuzz H5Dread
    H5Dread(dataset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);

    // Fuzz H5Dflush
    H5Dflush(dataset_id);

    // Fuzz H5Dwrite
    H5Dwrite(dataset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);

    // Fuzz H5Dwrite_multi
    hid_t dset_ids[] = {dataset_id};
    hid_t mem_type_ids[] = {mem_type_id};
    hid_t mem_space_ids[] = {mem_space_id};
    hid_t file_space_ids[] = {file_space_id};
    const void *bufs[] = {buf};
    H5Dwrite_multi(1, dset_ids, mem_type_ids, mem_space_ids, file_space_ids, dxpl_id, bufs);

    // Fuzz H5Dscatter
    H5D_scatter_func_t op = NULL; // No-op for fuzzing
    void *op_data = NULL;
    H5Dscatter(op, op_data, mem_type_id, mem_space_id, buf);

    // Fuzz H5Dset_extent
    hsize_t new_size[2] = {5, 5};
    H5Dset_extent(dataset_id, new_size);

    // Cleanup
    H5Dclose(dataset_id);
    H5Fclose(file_id);

    return 0;
}