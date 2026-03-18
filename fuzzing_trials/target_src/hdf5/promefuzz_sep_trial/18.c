// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Aopen_by_name at H5A.c:657:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aget_type at H5A.c:1128:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dget_type at H5D.c:706:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dget_type at H5D.c:706:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Aopen_by_name at H5A.c:657:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aget_type at H5A.c:1128:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Apublic.h"

#define H5P_DEFAULT 0 // Assuming H5P_DEFAULT is typically defined as 0

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "This is a dummy HDF5 file content.");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    // Prepare the environment
    write_dummy_file();

    // Open the file
    hid_t file_id1 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    hid_t file_id2 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);

    // Open a dataset
    hid_t dset_id = H5Dopen2(file_id1, "dataset", H5P_DEFAULT);

    // Close the file
    H5Fclose(file_id1);

    // Get dataset type
    hid_t dtype_id = H5Dget_type(dset_id);

    // Close the file
    H5Fclose(file_id2);

    // Close dataset
    H5Dclose(dset_id);

    // Close the file
    H5Fclose(file_id1);

    // Create a new file
    hid_t file_id3 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Open the file again
    hid_t file_id4 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);

    // Open the dataset again
    dset_id = H5Dopen2(file_id4, "dataset", H5P_DEFAULT);

    // Close the file
    H5Fclose(file_id3);

    // Get dataset type
    dtype_id = H5Dget_type(dset_id);

    // Close the file
    H5Fclose(file_id4);

    // Close dataset
    H5Dclose(dset_id);

    // Close the file
    H5Fclose(file_id3);

    // Open the file multiple times
    hid_t file_id5 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    hid_t file_id6 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);

    // Open an attribute by name
    hid_t attr_id = H5Aopen_by_name(file_id5, "object", "attribute", H5P_DEFAULT, H5P_DEFAULT);

    // Close the file
    H5Fclose(file_id5);

    // Get attribute type
    hid_t atype_id = H5Aget_type(attr_id);

    // Close the file
    H5Fclose(file_id6);

    // Close attribute
    H5Aclose(attr_id);

    // Close the file
    H5Fclose(file_id5);

    // Create a new file again
    hid_t file_id7 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Open the file again
    hid_t file_id8 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);

    // Open an attribute by name again
    attr_id = H5Aopen_by_name(file_id8, "object", "attribute", H5P_DEFAULT, H5P_DEFAULT);

    // Close the file
    H5Fclose(file_id7);

    // Get attribute type again
    atype_id = H5Aget_type(attr_id);

    // Close the file
    H5Fclose(file_id8);

    // Close attribute
    H5Aclose(attr_id);

    // Close the file
    H5Fclose(file_id7);

    // Final cleanup
    H5Aclose(attr_id);
    H5Dclose(dset_id);
    H5Fclose(file_id8);
    H5Fclose(file_id7);
    H5Fclose(file_id6);
    H5Fclose(file_id5);

    return 0;
}