// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Aexists_by_name_async at H5A.c:2502:1 in H5Apublic.h
// H5Dwrite_async at H5D.c:1376:1 in H5Dpublic.h
// H5Fflush_async at H5F.c:982:1 in H5Fpublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Fclose_async at H5F.c:1057:1 in H5Fpublic.h
// H5Dset_extent_async at H5D.c:2015:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "H5Dpublic.h"
#include "H5Apublic.h"
#include "H5Fpublic.h"

static void fuzz_H5Aexists_by_name_async(const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    hid_t loc_id = (hid_t)Data[0];
    const char *obj_name = "dummy_object";
    const char *attr_name = "dummy_attr";
    bool exists;
    hid_t lapl_id = (hid_t)Data[1];
    hid_t es_id = (hid_t)Data[2];

    H5Aexists_by_name_async(loc_id, obj_name, attr_name, &exists, lapl_id, es_id);
}

static void fuzz_H5Dwrite_async(const uint8_t *Data, size_t Size) {
    if (Size < 6) return;
    hid_t dset_id = (hid_t)Data[0];
    hid_t mem_type_id = (hid_t)Data[1];
    hid_t mem_space_id = (hid_t)Data[2];
    hid_t file_space_id = (hid_t)Data[3];
    hid_t dxpl_id = (hid_t)Data[4];
    const void *buf = Data + 6;
    hid_t es_id = (hid_t)Data[5];

    H5Dwrite_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
}

static void fuzz_H5Fflush_async(const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    hid_t object_id = (hid_t)Data[0];
    H5F_scope_t scope = (H5F_scope_t)(Data[1] % 2);
    hid_t es_id = (hid_t)Data[2];

    H5Fflush_async(object_id, scope, es_id);
}

static void fuzz_H5Dread_async(const uint8_t *Data, size_t Size) {
    if (Size < 6) return;
    hid_t dset_id = (hid_t)Data[0];
    hid_t mem_type_id = (hid_t)Data[1];
    hid_t mem_space_id = (hid_t)Data[2];
    hid_t file_space_id = (hid_t)Data[3];
    hid_t dxpl_id = (hid_t)Data[4];
    void *buf = malloc(256); // Allocate buffer for reading
    hid_t es_id = (hid_t)Data[5];

    if (buf) {
        H5Dread_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
        free(buf);
    }
}

static void fuzz_H5Fclose_async(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    hid_t file_id = (hid_t)Data[0];
    hid_t es_id = (hid_t)Data[1];

    H5Fclose_async(file_id, es_id);
}

static void fuzz_H5Dset_extent_async(const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    hid_t dset_id = (hid_t)Data[0];
    hsize_t size[1] = {(hsize_t)Data[1]};
    hid_t es_id = (hid_t)Data[2];

    H5Dset_extent_async(dset_id, size, es_id);
}

int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    fuzz_H5Aexists_by_name_async(Data, Size);
    fuzz_H5Dwrite_async(Data, Size);
    fuzz_H5Fflush_async(Data, Size);
    fuzz_H5Dread_async(Data, Size);
    fuzz_H5Fclose_async(Data, Size);
    fuzz_H5Dset_extent_async(Data, Size);

    return 0;
}