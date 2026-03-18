// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fget_freespace at H5F.c:1617:1 in H5Fpublic.h
// H5Fget_free_sections at H5F.c:2147:1 in H5Fpublic.h
// H5Fget_free_sections at H5F.c:2147:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        const char *data = "dummy data";
        fwrite(data, sizeof(char), strlen(data), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    H5Fclose(file_id);

    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t space_id = H5Screate(H5S_SCALAR);
    hid_t type_id = H5Tcopy(H5T_NATIVE_INT);

    hid_t dset_id = H5Dcreate2(file_id, "dset1", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id >= 0) {
        H5Dclose(dset_id);
    }

    dset_id = H5Dcreate2(file_id, "dset2", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id >= 0) {
        H5Dclose(dset_id);
    }

    H5Sclose(space_id);
    H5Tclose(type_id);

    hssize_t free_space = H5Fget_freespace(file_id);
    (void)free_space;

    size_t nsects = 0;
    H5Fget_free_sections(file_id, H5FD_MEM_DEFAULT, 0, NULL);

    H5F_sect_info_t *sect_info = (H5F_sect_info_t *)malloc(nsects * sizeof(H5F_sect_info_t));
    if (sect_info) {
        H5Fget_free_sections(file_id, H5FD_MEM_DEFAULT, nsects, sect_info);
        free(sect_info);
    }

    H5Fclose(file_id);
    return 0;
}