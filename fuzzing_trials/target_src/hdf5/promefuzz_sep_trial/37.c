// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Aget_create_plist at H5A.c:1175:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Aopen at H5A.c:531:1 in H5Apublic.h
// H5Aget_create_plist at H5A.c:1175:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Apublic.h"
#include "H5Ppublic.h"
#include "H5Tpublic.h"
#include "H5Spublic.h"

#define DUMMY_FILENAME "./dummy_file"
#define DATASET_NAME "dset"
#define ATTRIBUTE_NAME "attr"

static hid_t create_dataspace() {
    hsize_t dims[1] = {10};
    return H5Screate_simple(1, dims, NULL);
}

static hid_t create_datatype() {
    return H5Tcopy(H5T_NATIVE_INT);
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    hid_t file_id, dataset_id, attr_id, attr_id2, attr_id3, space_id, type_id;
    hid_t plist_id;
    herr_t status;

    // Prepare the environment
    file_id = H5Fcreate(DUMMY_FILENAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    space_id = create_dataspace();
    type_id = create_datatype();
    if (space_id < 0 || type_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // H5Dcreate2
    dataset_id = H5Dcreate2(file_id, DATASET_NAME, type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(space_id);
        H5Tclose(type_id);
        H5Fclose(file_id);
        return 0;
    }

    // H5Acreate2
    attr_id = H5Acreate2(dataset_id, ATTRIBUTE_NAME, type_id, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id >= 0) {
        // H5Aget_create_plist
        plist_id = H5Aget_create_plist(attr_id);
        if (plist_id >= 0) {
            H5Pclose(plist_id);
        }
        H5Aclose(attr_id);
    }

    // H5Acreate2 again
    attr_id2 = H5Acreate2(dataset_id, ATTRIBUTE_NAME, type_id, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id2 >= 0) {
        H5Aclose(attr_id2);
    }

    // H5Aopen
    attr_id3 = H5Aopen(dataset_id, ATTRIBUTE_NAME, H5P_DEFAULT);
    if (attr_id3 >= 0) {
        // H5Aget_create_plist
        plist_id = H5Aget_create_plist(attr_id3);
        if (plist_id >= 0) {
            H5Pclose(plist_id);
        }
        H5Aclose(attr_id3);
    }

    // Cleanup
    H5Dclose(dataset_id);
    H5Sclose(space_id);
    H5Tclose(type_id);
    H5Fclose(file_id);

    return 0;
}