// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Arename_async at H5A.c:1669:1 in H5Apublic.h
// H5Dwrite_multi_async at H5D.c:1449:1 in H5Dpublic.h
// H5Dwrite_async at H5D.c:1376:1 in H5Dpublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Dset_extent_async at H5D.c:2015:1 in H5Dpublic.h
// H5Dclose_async at H5D.c:493:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "H5Dpublic.h"
#include "H5Apublic.h"

static void fuzz_H5Arename_async(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    hid_t loc_id = (hid_t)Data[0];
    hid_t es_id = (hid_t)Data[1];
    const char *old_name = "old_attr";
    const char *new_name = "new_attr";

    H5Arename_async(loc_id, old_name, new_name, es_id);
}

static void fuzz_H5Dwrite_multi_async(const uint8_t *Data, size_t Size) {
    if (Size < 5) return;

    size_t count = 1;
    hid_t dset_id[1] = {(hid_t)Data[0]};
    hid_t mem_type_id[1] = {(hid_t)Data[1]};
    hid_t mem_space_id[1] = {(hid_t)Data[2]};
    hid_t file_space_id[1] = {(hid_t)Data[3]};
    hid_t dxpl_id = (hid_t)Data[4];
    const void *buf[1] = {Data + 5};
    hid_t es_id = (hid_t)Data[Size - 1];

    H5Dwrite_multi_async(count, dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
}

static void fuzz_H5Dwrite_async(const uint8_t *Data, size_t Size) {
    if (Size < 6) return;

    hid_t dset_id = (hid_t)Data[0];
    hid_t mem_type_id = (hid_t)Data[1];
    hid_t mem_space_id = (hid_t)Data[2];
    hid_t file_space_id = (hid_t)Data[3];
    hid_t dxpl_id = (hid_t)Data[4];
    const void *buf = Data + 5;
    hid_t es_id = (hid_t)Data[Size - 1];

    H5Dwrite_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
}

static void fuzz_H5Dread_async(const uint8_t *Data, size_t Size) {
    if (Size < 6) return;

    hid_t dset_id = (hid_t)Data[0];
    hid_t mem_type_id = (hid_t)Data[1];
    hid_t mem_space_id = (hid_t)Data[2];
    hid_t file_space_id = (hid_t)Data[3];
    hid_t dxpl_id = (hid_t)Data[4];
    void *buf = malloc(Size - 5);
    hid_t es_id = (hid_t)Data[Size - 1];

    H5Dread_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
    free(buf);
}

static void fuzz_H5Dset_extent_async(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    hid_t dset_id = (hid_t)Data[0];
    hsize_t size[1] = {(hsize_t)Data[1]};
    hid_t es_id = (hid_t)Data[Size - 1];

    H5Dset_extent_async(dset_id, size, es_id);
}

static void fuzz_H5Dclose_async(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    hid_t dset_id = (hid_t)Data[0];
    hid_t es_id = (hid_t)Data[Size - 1];

    H5Dclose_async(dset_id, es_id);
}

int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size) {
    fuzz_H5Arename_async(Data, Size);
    fuzz_H5Dwrite_multi_async(Data, Size);
    fuzz_H5Dwrite_async(Data, Size);
    fuzz_H5Dread_async(Data, Size);
    fuzz_H5Dset_extent_async(Data, Size);
    fuzz_H5Dclose_async(Data, Size);
    return 0;
}