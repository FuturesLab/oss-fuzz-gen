// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aget_num_attrs at H5Adeprec.c:303:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aget_num_attrs at H5Adeprec.c:303:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Aopen_idx at H5Adeprec.c:240:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Aopen_name at H5Adeprec.c:176:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
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
#include <hdf5.h>
#include <H5Dpublic.h>
#include <H5Apublic.h>
#include <H5Fpublic.h>

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "dummy data");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    hid_t file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    herr_t status = H5Fclose(file_id);
    if (status < 0) return 0;

    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t dataset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    int num_attrs = H5Aget_num_attrs(dataset_id);
    if (num_attrs < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    num_attrs = H5Aget_num_attrs(dataset_id);
    if (num_attrs < 0) {
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 0;
    }

    hid_t attr_id = H5Aopen_idx(dataset_id, 0);
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    attr_id = H5Aopen_name(dataset_id, "attribute_name");
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    H5Dclose(dataset_id);
    H5Fclose(file_id);

    return 0;
}