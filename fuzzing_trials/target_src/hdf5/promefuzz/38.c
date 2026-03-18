// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dget_access_plist at H5D.c:805:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dget_access_plist at H5D.c:805:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
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
#include <H5Dpublic.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static hid_t create_dataset(hid_t file_id, const char *name) {
    hid_t dataspace_id = H5Screate(H5S_SIMPLE);
    hsize_t dims[1] = {10};
    H5Sset_extent_simple(dataspace_id, 1, dims, NULL);
    hid_t dataset_id = H5Dcreate2(file_id, name, H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Sclose(dataspace_id);
    return dataset_id;
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new HDF5 file
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Create a dataset
    hid_t dset_id1 = create_dataset(file_id, "dset1");
    if (dset_id1 < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Get dataset access property list
    hid_t dapl_id1 = H5Dget_access_plist(dset_id1);
    if (dapl_id1 >= 0) H5Pclose(dapl_id1);

    // Close the dataset
    H5Dclose(dset_id1);

    // Open the dataset
    hid_t dset_id2 = H5Dopen2(file_id, "dset1", H5P_DEFAULT);
    if (dset_id2 >= 0) {
        // Get dataset access property list
        hid_t dapl_id2 = H5Dget_access_plist(dset_id2);
        if (dapl_id2 >= 0) H5Pclose(dapl_id2);

        // Close the dataset
        H5Dclose(dset_id2);
    }

    // Create another dataset
    hid_t dset_id3 = create_dataset(file_id, "dset2");
    if (dset_id3 < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Get dataset access property list
    hid_t dapl_id3 = H5Dget_access_plist(dset_id3);
    if (dapl_id3 >= 0) H5Pclose(dapl_id3);

    // Close the dataset
    H5Dclose(dset_id3);

    // Close the file
    H5Fclose(file_id);

    // Reopen the file
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Open the dataset again
    dset_id2 = H5Dopen2(file_id, "dset1", H5P_DEFAULT);
    if (dset_id2 >= 0) {
        // Get dataset access property list
        hid_t dapl_id2 = H5Dget_access_plist(dset_id2);
        if (dapl_id2 >= 0) H5Pclose(dapl_id2);

        // Close the dataset
        H5Dclose(dset_id2);
    }

    // Open the second dataset
    dset_id3 = H5Dopen2(file_id, "dset2", H5P_DEFAULT);
    if (dset_id3 >= 0) {
        // Get dataset access property list
        hid_t dapl_id3 = H5Dget_access_plist(dset_id3);
        if (dapl_id3 >= 0) H5Pclose(dapl_id3);

        // Close the dataset
        H5Dclose(dset_id3);
    }

    // Close the file
    H5Fclose(file_id);

    return 0;
}