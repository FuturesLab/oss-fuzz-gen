// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dwrite_chunk at H5D.c:1491:1 in H5Dpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dget_chunk_storage_size at H5D.c:2218:1 in H5Dpublic.h
// H5Dread_chunk2 at H5D.c:1181:1 in H5Dpublic.h
// H5Dread_chunk2 at H5D.c:1181:1 in H5Dpublic.h
// H5Dread_chunk2 at H5D.c:1181:1 in H5Dpublic.h
// H5Dread_chunk2 at H5D.c:1181:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <hdf5.h>

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite("dummy data", 1, 10, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hsize_t) * 4 + sizeof(uint32_t) + sizeof(size_t)) {
        return 0;
    }

    write_dummy_file();

    hid_t file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t space_id = H5Screate_simple(1, (const hsize_t[]){10}, NULL);
    hid_t dset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    const hsize_t *offset = (const hsize_t *)Data;
    uint32_t filters = *(const uint32_t *)(Data + sizeof(hsize_t) * 4);
    size_t data_size = *(const size_t *)(Data + sizeof(hsize_t) * 4 + sizeof(uint32_t));
    const void *buf = Data + sizeof(hsize_t) * 4 + sizeof(uint32_t) + sizeof(size_t);

    H5Dwrite_chunk(dset_id, H5P_DEFAULT, filters, offset, data_size, buf);
    H5Fflush(file_id, H5F_SCOPE_LOCAL);
    H5Dclose(dset_id);

    dset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    int read_buf[10];
    H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, read_buf);

    hsize_t chunk_size;
    H5Dget_chunk_storage_size(dset_id, offset, &chunk_size);

    size_t buf_size = 10 * sizeof(int);
    uint32_t read_filters;
    H5Dread_chunk2(dset_id, H5P_DEFAULT, offset, &read_filters, read_buf, &buf_size);
    H5Dread_chunk2(dset_id, H5P_DEFAULT, offset, &read_filters, read_buf, &buf_size);
    H5Dread_chunk2(dset_id, H5P_DEFAULT, offset, &read_filters, read_buf, &buf_size);
    H5Dread_chunk2(dset_id, H5P_DEFAULT, offset, &read_filters, read_buf, &buf_size);

    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    return 0;
}