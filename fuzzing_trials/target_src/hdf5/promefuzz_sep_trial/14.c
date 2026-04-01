// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Dcreate1 at H5Ddeprec.c:98:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen1 at H5Ddeprec.c:166:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Acreate1 at H5Adeprec.c:103:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen1 at H5Ddeprec.c:166:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Acreate1 at H5Adeprec.c:103:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Apublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "This is a dummy HDF5 file content.\n");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    hid_t file_id, dataset_id, attr_id;
    herr_t status;
    hid_t dataspace_id = H5Screate(H5S_SCALAR);
    hid_t datatype_id = H5Tcopy(H5T_NATIVE_INT);

    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    dataset_id = H5Dcreate1(file_id, "dataset", datatype_id, dataspace_id, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    status = H5Fclose(file_id);
    if (status < 0) return 0;

    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    dataset_id = H5Dopen1(file_id, "dataset");
    if (dataset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    attr_id = H5Acreate1(dataset_id, "attribute", datatype_id, dataspace_id, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    status = H5Aclose(attr_id);
    if (status < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    status = H5Dclose(dataset_id);
    if (status < 0) {
        H5Fclose(file_id);
        return 0;
    }

    status = H5Fclose(file_id);
    if (status < 0) return 0;

    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    dataset_id = H5Dopen1(file_id, "dataset");
    if (dataset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    attr_id = H5Acreate1(dataset_id, "attribute2", datatype_id, dataspace_id, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    status = H5Aclose(attr_id);
    if (status < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    status = H5Dclose(dataset_id);
    if (status < 0) {
        H5Fclose(file_id);
        return 0;
    }

    status = H5Fclose(file_id);
    if (status < 0) return 0;

    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    status = H5Fclose(file_id);
    if (status < 0) return 0;

    H5Sclose(dataspace_id);
    H5Tclose(datatype_id);

    return 0;
}