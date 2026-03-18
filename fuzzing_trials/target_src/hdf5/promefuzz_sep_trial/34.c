// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Awrite at H5A.c:908:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Aget_info_by_name at H5A.c:1445:1 in H5Apublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
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
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Apublic.h"
#include "H5Tpublic.h"
#include "H5Spublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id, dset_id1, dset_id2, dset_id3, attr_id;
    herr_t status;
    H5A_info_t ainfo;
    char obj_name[] = "dummy_object";
    char attr_name[] = "dummy_attr";
    hid_t type_id = H5T_NATIVE_INT;
    hid_t space_id = H5Screate(H5S_SCALAR);
    int dummy_data = 42;

    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    attr_id = H5Acreate2(file_id, attr_name, type_id, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id >= 0) {
        status = H5Awrite(attr_id, type_id, &dummy_data);
        status = H5Aclose(attr_id);
    }

    status = H5Fclose(file_id);

    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    dset_id1 = H5Dopen2(file_id, obj_name, H5P_DEFAULT);
    dset_id2 = H5Dopen2(file_id, obj_name, H5P_DEFAULT);
    dset_id3 = H5Dopen2(file_id, obj_name, H5P_DEFAULT);

    if (dset_id1 >= 0 && dset_id2 >= 0 && dset_id3 >= 0) {
        status = H5Aget_info_by_name(file_id, obj_name, attr_name, &ainfo, H5P_DEFAULT);
    }

    status = H5Dclose(dset_id1);
    status = H5Dclose(dset_id2);
    status = H5Dclose(dset_id3);
    status = H5Fclose(file_id);

    H5Sclose(space_id);

    return 0;
}