// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fset_dset_no_attrs_hint at H5F.c:2722:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fset_dset_no_attrs_hint at H5F.c:2722:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fset_dset_no_attrs_hint at H5F.c:2722:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("This is a dummy file for HDF5 testing.", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    hid_t file_id;
    herr_t status;
    bool minimize;

    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    status = H5Fget_dset_no_attrs_hint(file_id, &minimize);
    status = H5Fset_dset_no_attrs_hint(file_id, Data[0] % 2);
    status = H5Fget_dset_no_attrs_hint(file_id, &minimize);

    status = H5Fclose(file_id);
    if (status < 0) return 0;

    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    status = H5Fget_dset_no_attrs_hint(file_id, &minimize);
    status = H5Fset_dset_no_attrs_hint(file_id, Data[0] % 2);
    status = H5Fget_dset_no_attrs_hint(file_id, &minimize);
    status = H5Fget_dset_no_attrs_hint(file_id, &minimize);
    status = H5Fset_dset_no_attrs_hint(file_id, Data[0] % 2);
    status = H5Fget_dset_no_attrs_hint(file_id, &minimize);
    status = H5Fget_dset_no_attrs_hint(file_id, &minimize);

    status = H5Fclose(file_id);
    status = H5Fclose(file_id);

    return 0;
}