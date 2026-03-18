// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Adelete_by_idx at H5A.c:2134:1 in H5Apublic.h
// H5Adelete_by_idx at H5A.c:2134:1 in H5Apublic.h
// H5Acreate2 at H5A.c:221:1 in H5Apublic.h
// H5Awrite at H5A.c:908:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Adelete_by_idx at H5A.c:2134:1 in H5Apublic.h
// H5Aget_info_by_idx at H5A.c:1501:1 in H5Apublic.h
// H5Aget_name_by_idx at H5A.c:1293:1 in H5Apublic.h
// H5Adelete_by_idx at H5A.c:2134:1 in H5Apublic.h
// H5Aget_info_by_idx at H5A.c:1501:1 in H5Apublic.h
// H5Aget_name_by_idx at H5A.c:1293:1 in H5Apublic.h
// H5Adelete_by_idx at H5A.c:2134:1 in H5Apublic.h
// H5Adelete_by_idx at H5A.c:2134:1 in H5Apublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Apublic.h"
#include "H5Ppublic.h"
#include "H5Spublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

static hid_t create_dummy_file() {
    write_dummy_file();
    return H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
}

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    hid_t file_id = create_dummy_file();
    if (file_id < 0) return 0;

    hid_t loc_id = file_id;
    const char *obj_name = "dummy_object";
    H5_index_t idx_type = H5_INDEX_NAME;
    H5_iter_order_t order = H5_ITER_INC;
    hsize_t n = 0;
    hid_t lapl_id = H5P_DEFAULT;
    herr_t status;

    status = H5Adelete_by_idx(loc_id, obj_name, idx_type, order, n, lapl_id);
    status = H5Adelete_by_idx(loc_id, obj_name, idx_type, order, n, lapl_id);

    hid_t type_id = H5T_NATIVE_INT;
    hid_t space_id = H5Screate(H5S_SCALAR);
    hid_t attr_id = H5Acreate2(loc_id, "attr", type_id, space_id, H5P_DEFAULT, H5P_DEFAULT);

    if (attr_id >= 0) {
        int data = 42;
        status = H5Awrite(attr_id, type_id, &data);
        status = H5Aclose(attr_id);
    }

    status = H5Adelete_by_idx(loc_id, obj_name, idx_type, order, n, lapl_id);

    H5A_info_t ainfo;
    status = H5Aget_info_by_idx(loc_id, obj_name, idx_type, order, n, &ainfo, lapl_id);

    char name[256];
    ssize_t name_size = H5Aget_name_by_idx(loc_id, obj_name, idx_type, order, n, name, sizeof(name), lapl_id);

    status = H5Adelete_by_idx(loc_id, obj_name, idx_type, order, n, lapl_id);
    status = H5Aget_info_by_idx(loc_id, obj_name, idx_type, order, n, &ainfo, lapl_id);

    name_size = H5Aget_name_by_idx(loc_id, obj_name, idx_type, order, n, name, sizeof(name), lapl_id);

    status = H5Adelete_by_idx(loc_id, obj_name, idx_type, order, n, lapl_id);
    status = H5Adelete_by_idx(loc_id, obj_name, idx_type, order, n, lapl_id);

    hid_t dset_id = H5Dopen2(file_id, "dset", H5P_DEFAULT);
    if (dset_id >= 0) {
        status = H5Dclose(dset_id);
        status = H5Dclose(dset_id);
        status = H5Dclose(dset_id);
    }

    status = H5Fclose(file_id);
    return 0;
}