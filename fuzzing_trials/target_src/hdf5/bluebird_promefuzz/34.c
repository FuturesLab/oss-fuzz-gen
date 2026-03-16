// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Awrite at H5A.c:908:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Aget_info_by_name at H5A.c:1445:1 in H5Apublic.h
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
#include "H5Apublic.h"
#include "H5Fpublic.h"
#include "H5Ppublic.h"
#include "H5Tpublic.h"
#include "H5Spublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        // Write some dummy data to the file
        const char dummy_data[] = "This is a dummy HDF5 file.";
        fwrite(dummy_data, sizeof(dummy_data), 1, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    hid_t file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    hid_t space_id = H5Screate(H5S_SCALAR);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t attr_id = H5Acreate2(file_id, "attr", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    int value = 42;
    H5Awrite(attr_id, H5T_NATIVE_INT, &value);

    H5Aclose(attr_id);
    H5Sclose(space_id);

    hid_t dset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
    if (dset_id >= 0) {
        H5Dclose(dset_id);
    }

    H5Fclose(file_id);

    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    dset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
    if (dset_id >= 0) {
        H5Dclose(dset_id);
    }

    H5A_info_t ainfo;
    H5Aget_info_by_name(file_id, ".", "attr", &ainfo, H5P_DEFAULT);

    H5Fclose(file_id);

    return 0;
}