// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Acreate_by_name_async at H5A.c:393:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dwrite_multi_async at H5D.c:1449:1 in H5Dpublic.h
// H5Fopen_async at H5F.c:848:1 in H5Fpublic.h
// H5Fflush_async at H5F.c:982:1 in H5Fpublic.h
// H5Freopen_async at H5F.c:1477:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dopen_async at H5D.c:418:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Apublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    const char *obj_name = "dummy_object";
    const char *attr_name = "dummy_attribute";
    hid_t loc_id = (hid_t)Data[0];
    hid_t type_id = (hid_t)Data[0];
    hid_t space_id = (hid_t)Data[0];
    hid_t acpl_id = (hid_t)Data[0];
    hid_t aapl_id = (hid_t)Data[0];
    hid_t lapl_id = (hid_t)Data[0];
    hid_t es_id = (hid_t)Data[0];

    hid_t attr_id = H5Acreate_by_name_async(loc_id, obj_name, attr_name, type_id, space_id, acpl_id, aapl_id, lapl_id, es_id);
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    size_t count = 1;
    hid_t dset_id[] = {(hid_t)Data[0]};
    hid_t mem_type_id[] = {(hid_t)Data[0]};
    hid_t mem_space_id[] = {(hid_t)Data[0]};
    hid_t file_space_id[] = {(hid_t)Data[0]};
    hid_t dxpl_id = (hid_t)Data[0];
    const void *buf[] = {Data};

    herr_t write_status = H5Dwrite_multi_async(count, dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);

    hid_t file_id = H5Fopen_async("./dummy_file", 0, dxpl_id, es_id);
    if (file_id >= 0) {
        herr_t flush_status = H5Fflush_async(file_id, H5F_SCOPE_LOCAL, es_id);
        if (flush_status >= 0) {
            hid_t reopen_id = H5Freopen_async(file_id, es_id);
            if (reopen_id >= 0) {
                H5Fclose(reopen_id);
            }
        }
        H5Fclose(file_id);
    }

    hid_t dapl_id = (hid_t)Data[0];
    hid_t dset_open_id = H5Dopen_async(loc_id, obj_name, dapl_id, es_id);
    if (dset_open_id >= 0) {
        H5Dclose(dset_open_id);
    }

    return 0;
}