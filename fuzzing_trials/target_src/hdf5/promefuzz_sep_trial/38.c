// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dget_access_plist at H5D.c:805:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dget_access_plist at H5D.c:805:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dget_access_plist at H5D.c:805:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dget_access_plist at H5D.c:805:1 in H5Dpublic.h
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
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Ppublic.h"
#include "H5Tpublic.h"
#include "H5Spublic.h"

static void write_dummy_data(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "Dummy data for HDF5 file.\n");
        fclose(file);
    }
}

static hid_t create_dataspace() {
    hsize_t dims[1] = {10};
    return H5Screate_simple(1, dims, NULL);
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const char *filename = "./dummy_file.h5";
    write_dummy_data(filename);

    hid_t file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t space_id = create_dataspace();
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t dset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id >= 0) {
        hid_t dapl_id = H5Dget_access_plist(dset_id);
        if (dapl_id >= 0) {
            H5Pclose(dapl_id);
        }
        H5Dclose(dset_id);
    }

    dset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
    if (dset_id >= 0) {
        hid_t dapl_id = H5Dget_access_plist(dset_id);
        if (dapl_id >= 0) {
            H5Pclose(dapl_id);
        }
        H5Dclose(dset_id);
    }

    H5Fclose(file_id);

    file_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id >= 0) {
        dset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
        if (dset_id >= 0) {
            hid_t dapl_id = H5Dget_access_plist(dset_id);
            if (dapl_id >= 0) {
                H5Pclose(dapl_id);
            }
            H5Dclose(dset_id);
        }

        dset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
        if (dset_id >= 0) {
            hid_t dapl_id = H5Dget_access_plist(dset_id);
            if (dapl_id >= 0) {
                H5Pclose(dapl_id);
            }
            H5Dclose(dset_id);
        }

        H5Fclose(file_id);
    }

    H5Sclose(space_id);
    return 0;
}