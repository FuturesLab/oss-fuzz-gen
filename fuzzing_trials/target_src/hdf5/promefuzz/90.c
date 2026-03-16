// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dset_extent at H5D.c:1991:1 in H5Dpublic.h
// H5Dformat_convert at H5D.c:2139:1 in H5Dpublic.h
// H5Dget_storage_size at H5D.c:848:1 in H5Dpublic.h
// H5Ddebug at H5Ddbg.c:63:1 in H5Dpublic.h
// H5Drefresh at H5D.c:2096:1 in H5Dpublic.h
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
#include <H5Dpublic.h>
#include <H5Spublic.h>
#include <H5Tpublic.h>
#include <H5Ppublic.h>
#include <H5Fpublic.h>
#include <H5public.h>

static hid_t create_dummy_file() {
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    return file_id;
}

static hid_t create_dataspace(hsize_t *dims, int rank) {
    return H5Screate_simple(rank, dims, NULL);
}

static hid_t create_datatype() {
    return H5Tcopy(H5T_NATIVE_INT);
}

static hid_t create_dataset(hid_t file_id, const char *name, hid_t space_id, hid_t type_id) {
    return H5Dcreate2(file_id, name, type_id, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
}

int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hsize_t) * 2) return 0;

    hsize_t dims[2];
    memcpy(dims, Data, sizeof(hsize_t) * 2);

    hid_t file_id = create_dummy_file();
    if (file_id < 0) return 0;

    hid_t space_id = create_dataspace(dims, 2);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t type_id = create_datatype();
    if (type_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    hid_t dset_id = create_dataset(file_id, "dataset", space_id, type_id);
    if (dset_id < 0) {
        H5Tclose(type_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Fuzz H5Dset_extent
    if (Size >= sizeof(hsize_t) * 4) {
        hsize_t new_dims[2];
        memcpy(new_dims, Data + sizeof(hsize_t) * 2, sizeof(hsize_t) * 2);
        H5Dset_extent(dset_id, new_dims);
    }

    // Fuzz H5Dformat_convert
    H5Dformat_convert(dset_id);

    // Fuzz H5Dget_storage_size
    H5Dget_storage_size(dset_id);

    // Fuzz H5Ddebug
    H5Ddebug(dset_id);

    // Fuzz H5Drefresh
    H5Drefresh(dset_id);

    H5Dclose(dset_id);
    H5Tclose(type_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    return 0;
}