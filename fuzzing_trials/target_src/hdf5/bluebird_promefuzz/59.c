// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Awrite_async at H5A.c:931:1 in H5Apublic.h
// H5Arename_async at H5A.c:1669:1 in H5Apublic.h
// H5Aread_async at H5A.c:1037:1 in H5Apublic.h
// H5Arename_by_name_async at H5A.c:1781:1 in H5Apublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Aclose_async at H5A.c:2224:1 in H5Apublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Apublic.h"

static void fuzz_H5Awrite_async(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 3) return;

    hid_t attr_id = *((hid_t *)Data);
    hid_t type_id = *((hid_t *)(Data + sizeof(hid_t)));
    hid_t es_id = *((hid_t *)(Data + sizeof(hid_t) * 2));
    const void *buf = Data + sizeof(hid_t) * 3;

    H5Awrite_async(attr_id, type_id, buf, es_id);
}

static void fuzz_H5Arename_async(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) + 2) return;

    hid_t loc_id = *((hid_t *)Data);
    const char *old_name = (const char *)(Data + sizeof(hid_t));
    size_t old_name_len = strnlen(old_name, Size - sizeof(hid_t));
    const char *new_name = old_name + old_name_len + 1;

    if (new_name >= (const char *)(Data + Size)) return;

    size_t new_name_len = strnlen(new_name, Size - sizeof(hid_t) - old_name_len - 1);
    if (new_name + new_name_len >= (const char *)(Data + Size)) return;

    H5Arename_async(loc_id, old_name, new_name, loc_id);
}

static void fuzz_H5Aread_async(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 3) return;

    hid_t attr_id = *((hid_t *)Data);
    hid_t dtype_id = *((hid_t *)(Data + sizeof(hid_t)));
    hid_t es_id = *((hid_t *)(Data + sizeof(hid_t) * 2));
    void *buf = (void *)(Data + sizeof(hid_t) * 3);

    H5Aread_async(attr_id, dtype_id, buf, es_id);
}

static void fuzz_H5Arename_by_name_async(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) + 3) return;

    hid_t loc_id = *((hid_t *)Data);
    const char *obj_name = (const char *)(Data + sizeof(hid_t));
    size_t obj_name_len = strnlen(obj_name, Size - sizeof(hid_t));
    const char *old_attr_name = obj_name + obj_name_len + 1;

    if (old_attr_name >= (const char *)(Data + Size)) return;

    size_t old_attr_name_len = strnlen(old_attr_name, Size - sizeof(hid_t) - obj_name_len - 1);
    const char *new_attr_name = old_attr_name + old_attr_name_len + 1;

    if (new_attr_name >= (const char *)(Data + Size)) return;

    size_t new_attr_name_len = strnlen(new_attr_name, Size - sizeof(hid_t) - obj_name_len - old_attr_name_len - 2);
    if (new_attr_name + new_attr_name_len >= (const char *)(Data + Size)) return;

    H5Arename_by_name_async(loc_id, obj_name, old_attr_name, new_attr_name, loc_id, loc_id);
}

static void fuzz_H5Dread_async(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 6) return;

    hid_t dset_id = *((hid_t *)Data);
    hid_t mem_type_id = *((hid_t *)(Data + sizeof(hid_t)));
    hid_t mem_space_id = *((hid_t *)(Data + sizeof(hid_t) * 2));
    hid_t file_space_id = *((hid_t *)(Data + sizeof(hid_t) * 3));
    hid_t dxpl_id = *((hid_t *)(Data + sizeof(hid_t) * 4));
    hid_t es_id = *((hid_t *)(Data + sizeof(hid_t) * 5));
    void *buf = (void *)(Data + sizeof(hid_t) * 6);

    H5Dread_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
}

static void fuzz_H5Aclose_async(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 2) return;

    hid_t attr_id = *((hid_t *)Data);
    hid_t es_id = *((hid_t *)(Data + sizeof(hid_t)));

    H5Aclose_async(attr_id, es_id);
}

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    fuzz_H5Awrite_async(Data, Size);
    fuzz_H5Arename_async(Data, Size);
    fuzz_H5Aread_async(Data, Size);
    fuzz_H5Arename_by_name_async(Data, Size);
    fuzz_H5Dread_async(Data, Size);
    fuzz_H5Aclose_async(Data, Size);

    return 0;
}