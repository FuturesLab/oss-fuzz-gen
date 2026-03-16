// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dextend at H5Ddeprec.c:220:1 in H5Dpublic.h
// H5Dget_space at H5D.c:597:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dget_space at H5D.c:597:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
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

#define FILE_NAME "./dummy_file"
#define DATASET_NAME "fuzz_dataset"
#define DIM0 4
#define DIM1 6

static void write_dummy_file() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file) {
        fputs("HDF5 dummy content", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    write_dummy_file();

    hid_t file_id, dset_id, space_id, mem_space_id, type_id;
    herr_t status;
    hsize_t dims[2] = {DIM0, DIM1};
    int buf[DIM0][DIM1];

    file_id = H5Fopen(FILE_NAME, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    space_id = H5Screate_simple(2, dims, NULL);
    if (space_id < 0) goto close_file;

    type_id = H5Tcopy(H5T_NATIVE_INT);
    if (type_id < 0) goto close_space;

    dset_id = H5Dcreate2(file_id, DATASET_NAME, type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) goto close_type;

    hsize_t new_dims[2] = {DIM0 + 1, DIM1 + 1};
    status = H5Dextend(dset_id, new_dims);
    if (status < 0) goto close_dset;

    hid_t space_id_copy = H5Dget_space(dset_id);
    if (space_id_copy < 0) goto close_dset;

    mem_space_id = H5Screate_simple(2, dims, NULL);
    if (mem_space_id < 0) goto close_space_copy;

    status = H5Dwrite(dset_id, type_id, mem_space_id, space_id_copy, H5P_DEFAULT, buf);
    if (status < 0) goto close_mem_space;

    hid_t space_id_copy2 = H5Dget_space(dset_id);
    if (space_id_copy2 < 0) goto close_mem_space;

    status = H5Dread(dset_id, type_id, mem_space_id, space_id_copy2, H5P_DEFAULT, buf);
    
    H5Sclose(space_id_copy2);
close_mem_space:
    H5Sclose(mem_space_id);
close_space_copy:
    H5Sclose(space_id_copy);
close_dset:
    H5Dclose(dset_id);
close_type:
    H5Tclose(type_id);
close_space:
    H5Sclose(space_id);
close_file:
    H5Fclose(file_id);

    return 0;
}