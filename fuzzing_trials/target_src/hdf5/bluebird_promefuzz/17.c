// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
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
// H5Aopen_by_name at H5A.c:657:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aget_type at H5A.c:1128:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
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
#include <hdf5.h>

#define DUMMY_FILE "./dummy_file"
#define DATASET_NAME "dummy_dataset"
#define ATTRIBUTE_NAME "dummy_attribute"
#define OBJECT_NAME "dummy_object"

static void write_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fprintf(file, "Dummy data for HDF5 testing.\n");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id1 = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);
    hid_t file_id2 = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);
    
    hid_t dset_id = H5Dopen2(file_id1, DATASET_NAME, H5P_DEFAULT);
    H5Fclose(file_id1);

    hid_t dtype_id = H5Dget_type(dset_id);
    H5Fclose(file_id2);

    H5Dclose(dset_id);
    H5Fclose(file_id1);

    hid_t new_file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    file_id1 = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);

    dset_id = H5Dopen2(file_id1, DATASET_NAME, H5P_DEFAULT);
    H5Fclose(new_file_id);

    dtype_id = H5Dget_type(dset_id);
    H5Fclose(file_id1);

    H5Dclose(dset_id);
    H5Fclose(file_id1);

    file_id1 = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);
    file_id2 = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);

    hid_t attr_id = H5Aopen_by_name(file_id1, OBJECT_NAME, ATTRIBUTE_NAME, H5P_DEFAULT, H5P_DEFAULT);
    H5Fclose(file_id1);

    hid_t atype_id = H5Aget_type(attr_id);
    H5Fclose(file_id2);

    H5Aclose(attr_id);
    H5Fclose(file_id1);

    new_file_id = H5Fcreate(DUMMY_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    file_id1 = H5Fopen(DUMMY_FILE, H5F_ACC_RDWR, H5P_DEFAULT);

    attr_id = H5Aopen_by_name(file_id1, OBJECT_NAME, ATTRIBUTE_NAME, H5P_DEFAULT, H5P_DEFAULT);
    H5Fclose(new_file_id);

    atype_id = H5Aget_type(attr_id);
    H5Fclose(file_id1);

    H5Aclose(attr_id);
    H5Fclose(file_id1);
    H5Fclose(file_id1);
    H5Fclose(file_id1);
    H5Aclose(attr_id);
    H5Dclose(dset_id);
    H5Fclose(file_id1);
    H5Fclose(file_id1);
    H5Fclose(file_id1);
    H5Fclose(file_id1);
    H5Fclose(file_id1);

    return 0;
}