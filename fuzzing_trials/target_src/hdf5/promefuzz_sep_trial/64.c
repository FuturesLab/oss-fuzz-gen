// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate_async at H5F.c:673:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dget_space_async at H5D.c:625:1 in H5Dpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dopen_async at H5D.c:418:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Dpublic.h>
#include <H5Fpublic.h>
#include <H5Apublic.h>
#include <H5Ppublic.h>
#include <H5Spublic.h>
#include <H5Tpublic.h>

static hid_t create_dummy_file() {
    hid_t file_id = H5Fcreate_async("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT, 0);
    return file_id;
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    hid_t file_id = create_dummy_file();
    if (file_id < 0) return 0;

    hid_t dset_id = H5Dcreate_async(file_id, "dummy_dataset", H5T_NATIVE_INT, H5S_SCALAR, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT, 0);
    if (dset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Fuzzing H5Dget_space_async
    hid_t space_id = H5Dget_space_async(dset_id, 0);
    if (space_id >= 0) {
        H5Sclose(space_id);
    }

    // Fuzzing H5Acreate_async
    hid_t attr_id = H5Acreate_async(dset_id, "dummy_attribute", H5T_NATIVE_INT, H5S_SCALAR, H5P_DEFAULT, H5P_DEFAULT, 0);
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    // Fuzzing H5Dopen_async
    hid_t open_dset_id = H5Dopen_async(file_id, "dummy_dataset", H5P_DEFAULT, 0);
    if (open_dset_id >= 0) {
        H5Dclose(open_dset_id);
    }

    // Fuzzing H5Dread_async
    int buf;
    herr_t status = H5Dread_async(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, &buf, 0);

    // Cleanup
    H5Dclose(dset_id);
    H5Fclose(file_id);

    return 0;
}