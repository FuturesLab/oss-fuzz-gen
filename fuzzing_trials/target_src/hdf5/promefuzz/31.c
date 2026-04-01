// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Dflush at H5D.c:2055:1 in H5Dpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <hdf5.h>

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        const char *dummy_content = "This is a dummy file for HDF5 testing.";
        fwrite(dummy_content, 1, strlen(dummy_content), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there is at least some data.

    write_dummy_file();

    hid_t file_id, plist_id, dset_id1, dset_id2;
    herr_t status;
    hid_t space_id, type_id;
    hsize_t dims[1] = {10};
    int data[10] = {0}; // Dummy data buffer

    // Create a new file using default properties.
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Get the file access property list identifier.
    plist_id = H5Fget_access_plist(file_id);
    if (plist_id < 0) goto close_file;

    // Create a simple dataspace.
    space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) goto close_plist;

    // Create a new dataset within the file using defined dataspace and datatype.
    type_id = H5Tcopy(H5T_NATIVE_INT);
    dset_id1 = H5Dcreate2(file_id, "dset1", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id1 < 0) goto close_space;

    // Write the dataset.
    status = H5Dwrite(dset_id1, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    if (status < 0) goto close_dset1_early;

    // Flush the dataset.
    status = H5Dflush(dset_id1);
    if (status < 0) goto close_dset1_early;

    // Create another dataset.
    dset_id2 = H5Dcreate2(file_id, "dset2", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id2 < 0) goto close_dset1_early;

    // Close datasets.
    H5Dclose(dset_id1);
    H5Dclose(dset_id2);

    // Close property lists and spaces.
close_space:
    H5Sclose(space_id);
close_plist:
    H5Pclose(plist_id);
close_file:
    H5Fclose(file_id);

    // Reopen the file and datasets for further testing.
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    dset_id1 = H5Dcreate2(file_id, "dset3", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id1 >= 0) {
        H5Dclose(dset_id1);
    }

    // Close the file.
    H5Fclose(file_id);

    return 0;

close_dset1_early:
    H5Dclose(dset_id1);
    goto close_space;
}