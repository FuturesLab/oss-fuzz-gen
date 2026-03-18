// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dget_access_plist at H5D.c:805:1 in H5Dpublic.h
// H5Dget_storage_size at H5D.c:848:1 in H5Dpublic.h
// H5Dget_type at H5D.c:706:1 in H5Dpublic.h
// H5Dread_multi at H5D.c:1109:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dgather at H5D.c:1645:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Tpublic.h" // Include this header for H5Tclose
#include "H5Ppublic.h" // Include this header for H5P_DEFAULT

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "dummy data");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t)) {
        return 0;
    }

    write_dummy_file();

    hid_t dset_id = *((hid_t *)Data);
    Data += sizeof(hid_t);
    Size -= sizeof(hid_t);

    // Fuzzing H5Dget_access_plist
    hid_t dapl_id = H5Dget_access_plist(dset_id);
    if (dapl_id >= 0) {
        H5Pclose(dapl_id);
    }

    // Fuzzing H5Dget_storage_size
    hsize_t storage_size = H5Dget_storage_size(dset_id);

    // Fuzzing H5Dget_type
    hid_t dtype_id = H5Dget_type(dset_id);
    if (dtype_id >= 0) {
        H5Tclose(dtype_id);
    }

    // Fuzzing H5Dread_multi
    if (Size >= sizeof(size_t)) {
        size_t count = *((size_t *)Data);
        Data += sizeof(size_t);
        Size -= sizeof(size_t);

        if (Size >= count * sizeof(hid_t) * 4 + sizeof(hid_t)) {
            hid_t *dset_ids = (hid_t *)Data;
            hid_t *mem_type_ids = (hid_t *)(Data + count * sizeof(hid_t));
            hid_t *mem_space_ids = (hid_t *)(Data + count * sizeof(hid_t) * 2);
            hid_t *file_space_ids = (hid_t *)(Data + count * sizeof(hid_t) * 3);
            hid_t dxpl_id = *(hid_t *)(Data + count * sizeof(hid_t) * 4);
            void **bufs = (void **)(Data + count * sizeof(hid_t) * 4 + sizeof(hid_t));

            herr_t status = H5Dread_multi(count, dset_ids, mem_type_ids, mem_space_ids, file_space_ids, dxpl_id, bufs);
            if (status < 0) {
                // Handle error
            }
        }
    }

    // Fuzzing H5Dwrite
    if (Size >= sizeof(hid_t) * 4 + sizeof(hid_t)) {
        hid_t mem_type_id = *((hid_t *)Data);
        hid_t mem_space_id = *((hid_t *)(Data + sizeof(hid_t)));
        hid_t file_space_id = *((hid_t *)(Data + sizeof(hid_t) * 2));
        hid_t dxpl_id = *((hid_t *)(Data + sizeof(hid_t) * 3));
        const void *buf = (const void *)(Data + sizeof(hid_t) * 4);

        herr_t status = H5Dwrite(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);
        if (status < 0) {
            // Handle error
        }
    }

    // Fuzzing H5Dgather
    if (Size >= sizeof(hid_t) * 3 + sizeof(size_t)) {
        hid_t src_space_id = *((hid_t *)Data);
        const void *src_buf = (const void *)(Data + sizeof(hid_t));
        hid_t type_id = *((hid_t *)(Data + sizeof(hid_t) + sizeof(void *)));
        size_t dst_buf_size = *((size_t *)(Data + sizeof(hid_t) * 2 + sizeof(void *)));
        void *dst_buf = malloc(dst_buf_size);

        if (dst_buf) {
            herr_t status = H5Dgather(src_space_id, src_buf, type_id, dst_buf_size, dst_buf, NULL, NULL);
            if (status < 0) {
                // Handle error
            }
            free(dst_buf);
        }
    }

    return 0;
}