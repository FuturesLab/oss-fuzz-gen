// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_eoa at H5F.c:2606:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fincrement_filesize at H5F.c:2646:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Dpublic.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static void write_dummy_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const char *filename = "./dummy_file";
    write_dummy_file(filename);

    hid_t file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t space_id = H5Screate(H5S_SCALAR); // Simplified for fuzzing
    hid_t type_id = H5Tcopy(H5T_NATIVE_INT); // Simplified for fuzzing
    hid_t lcpl_id = H5P_DEFAULT;
    hid_t dcpl_id = H5P_DEFAULT;
    hid_t dapl_id = H5P_DEFAULT;

    hid_t dset_id = H5Dcreate2(file_id, "dataset", type_id, space_id, lcpl_id, dcpl_id, dapl_id);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Tclose(type_id);
        H5Fclose(file_id);
        return 0;
    }

    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Tclose(type_id);
    H5Fclose(file_id);

    file_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    haddr_t eoa;
    if (H5Fget_eoa(file_id, &eoa) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hsize_t increment = (hsize_t)Data[0];
    if (H5Fincrement_filesize(file_id, increment) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    H5Fclose(file_id);
    return 0;
}