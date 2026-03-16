// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dwrite_chunk at H5D.c:1491:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dget_chunk_storage_size at H5D.c:2218:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dread_chunk2 at H5D.c:1181:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Dpublic.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>
#include <H5Spublic.h>
#include <H5Tpublic.h>

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "dummy data");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 3 + sizeof(hsize_t) + sizeof(size_t)) return 0;

    // Prepare environment
    write_dummy_file();

    hid_t loc_id = *((hid_t *)Data);
    hid_t type_id = *((hid_t *)(Data + sizeof(hid_t)));
    hid_t space_id = *((hid_t *)(Data + 2 * sizeof(hid_t)));
    hsize_t offset[] = { *((hsize_t *)(Data + 3 * sizeof(hid_t))) };
    size_t data_size = *((size_t *)(Data + 3 * sizeof(hid_t) + sizeof(hsize_t)));

    // Create dataset
    hid_t dset_id = H5Dcreate2(loc_id, "dataset", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) return 0;

    // Write chunk
    herr_t status = H5Dwrite_chunk(dset_id, H5P_DEFAULT, 0, offset, data_size, Data);
    if (status < 0) {
        H5Dclose(dset_id);
        return 0;
    }

    // Flush file
    status = H5Fflush(loc_id, H5F_SCOPE_GLOBAL);
    if (status < 0) {
        H5Dclose(dset_id);
        return 0;
    }

    // Close dataset
    status = H5Dclose(dset_id);
    if (status < 0) return 0;

    // Re-open dataset
    dset_id = H5Dopen2(loc_id, "dataset", H5P_DEFAULT);
    if (dset_id < 0) return 0;

    // Read dataset
    void *buf = malloc(data_size);
    if (!buf) {
        H5Dclose(dset_id);
        return 0;
    }
    status = H5Dread(dset_id, type_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
    free(buf);
    if (status < 0) {
        H5Dclose(dset_id);
        return 0;
    }

    // Get chunk storage size
    hsize_t chunk_bytes;
    status = H5Dget_chunk_storage_size(dset_id, offset, &chunk_bytes);
    if (status < 0) {
        H5Dclose(dset_id);
        return 0;
    }

    // Read chunk multiple times
    size_t buf_size = data_size;
    uint32_t filters = 0;
    for (int i = 0; i < 4; i++) {
        buf = malloc(buf_size);
        if (!buf) {
            H5Dclose(dset_id);
            return 0;
        }
        status = H5Dread_chunk2(dset_id, H5P_DEFAULT, offset, &filters, buf, &buf_size);
        free(buf);
        if (status < 0) {
            H5Dclose(dset_id);
            return 0;
        }
    }

    // Close dataset
    status = H5Dclose(dset_id);
    if (status < 0) return 0;

    return 0;
}