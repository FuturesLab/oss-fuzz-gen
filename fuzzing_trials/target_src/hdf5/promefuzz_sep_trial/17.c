// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Diterate at H5D.c:1842:1 in H5Dpublic.h
// H5Dfill at H5D.c:1758:1 in H5Dpublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <hdf5.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Apublic.h"

static herr_t dummy_op(void *elem, hid_t type_id, hsize_t ndim, hssize_t *point, void *operator_data) {
    return 0; // Dummy operation for H5Diterate
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Create a simple dataspace
    hsize_t dims[1] = {10};
    hid_t space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dataset
    hid_t dset_id = H5Dcreate2(file_id, "dset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Prepare buffer for writing
    int wdata[10] = {0};
    if (Size > 10 * sizeof(int)) {
        memcpy(wdata, Data, 10 * sizeof(int));
    }

    // Write data to the dataset
    H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, wdata);
    H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, wdata);
    H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, wdata);

    // Iterate over dataset
    H5Diterate(wdata, H5T_NATIVE_INT, space_id, dummy_op, NULL);

    // Fill dataset with zeros
    int fill_value = 0;
    H5Dfill(&fill_value, H5T_NATIVE_INT, wdata, H5T_NATIVE_INT, space_id);

    // Create an attribute
    hid_t attr_id = H5Acreate2(dset_id, "attr", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    // Read data from the dataset
    int rdata[10] = {0};
    H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);
    H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);
    H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);

    // Close the dataset and file
    H5Dclose(dset_id);
    H5Fclose(file_id);
    H5Sclose(space_id);

    return 0;
}