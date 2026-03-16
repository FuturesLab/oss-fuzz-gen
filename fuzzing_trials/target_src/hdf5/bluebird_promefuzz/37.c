// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_freespace at H5F.c:1617:1 in H5Fpublic.h
// H5Fget_free_sections at H5F.c:2147:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_free_sections at H5F.c:2147:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id, dset_id;
    hssize_t free_space;
    ssize_t num_sections;
    H5F_sect_info_t *sect_info = NULL;

    // H5Fcreate
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // H5Fclose
    if (H5Fclose(file_id) < 0) return 0;

    // H5Dcreate2
    hid_t space_id = H5Screate(H5S_SCALAR);
    if (space_id < 0) return 0;

    dset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        return 0;
    }

    // H5Dclose
    if (H5Dclose(dset_id) < 0) {
        H5Sclose(space_id);
        return 0;
    }

    // H5Dcreate2 again
    dset_id = H5Dcreate2(file_id, "dataset2", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        return 0;
    }

    // H5Dclose again
    if (H5Dclose(dset_id) < 0) {
        H5Sclose(space_id);
        return 0;
    }

    H5Sclose(space_id);

    // H5Fclose again
    if (H5Fclose(file_id) < 0) return 0;

    // H5Fopen
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // H5Fget_freespace
    free_space = H5Fget_freespace(file_id);
    if (free_space < 0) return 0;

    // H5Fget_free_sections multiple times
    for (int i = 0; i < 10; i++) {
        num_sections = H5Fget_free_sections(file_id, H5FD_MEM_DEFAULT, 0, NULL);
        if (num_sections > 0) {
            sect_info = (H5F_sect_info_t *)malloc(num_sections * sizeof(H5F_sect_info_t));
            if (sect_info == NULL) {
                H5Fclose(file_id);
                return 0;
            }
            H5Fget_free_sections(file_id, H5FD_MEM_DEFAULT, num_sections, sect_info);
            free(sect_info);
        }
    }

    // Final H5Fclose
    H5Fclose(file_id);

    return 0;
}