// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Aexists_by_name_async at H5A.c:2502:1 in H5Apublic.h
// H5Aread_async at H5A.c:1037:1 in H5Apublic.h
// H5Arename_by_name_async at H5A.c:1781:1 in H5Apublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Aclose_async at H5A.c:2224:1 in H5Apublic.h
// H5Aexists_async at H5A.c:2392:1 in H5Apublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <H5Dpublic.h>
#include <H5Apublic.h>
#include <H5Ppublic.h>
#include <H5ESpublic.h>

static herr_t fuzz_H5Aexists_by_name_async(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0;
    hid_t loc_id = (hid_t)Data[0];
    const char *obj_name = (const char *)&Data[1];
    const char *attr_name = (const char *)&Data[2];
    bool exists;
    hid_t lapl_id = H5P_DEFAULT;
    hid_t es_id = H5ES_NONE;

    return H5Aexists_by_name_async(loc_id, obj_name, attr_name, &exists, lapl_id, es_id);
}

static herr_t fuzz_H5Aread_async(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;
    hid_t attr_id = (hid_t)Data[0];
    hid_t dtype_id = (hid_t)Data[1];
    void *buf = malloc(1024); // Allocate buffer for reading
    hid_t es_id = H5ES_NONE;

    herr_t ret = H5Aread_async(attr_id, dtype_id, buf, es_id);
    free(buf);
    return ret;
}

static herr_t fuzz_H5Arename_by_name_async(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0;
    hid_t loc_id = (hid_t)Data[0];
    const char *obj_name = (const char *)&Data[1];
    const char *old_attr_name = (const char *)&Data[2];
    const char *new_attr_name = "new_attr_name";
    hid_t lapl_id = H5P_DEFAULT;
    hid_t es_id = H5ES_NONE;

    return H5Arename_by_name_async(loc_id, obj_name, old_attr_name, new_attr_name, lapl_id, es_id);
}

static herr_t fuzz_H5Dread_async(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0;
    hid_t dset_id = (hid_t)Data[0];
    hid_t mem_type_id = (hid_t)Data[1];
    hid_t mem_space_id = (hid_t)Data[2];
    hid_t file_space_id = (hid_t)Data[3];
    hid_t dxpl_id = (hid_t)Data[4];
    void *buf = malloc(1024); // Allocate buffer for reading
    hid_t es_id = H5ES_NONE;

    herr_t ret = H5Dread_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
    free(buf);
    return ret;
}

static herr_t fuzz_H5Aclose_async(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;
    hid_t attr_id = (hid_t)Data[0];
    hid_t es_id = H5ES_NONE;

    return H5Aclose_async(attr_id, es_id);
}

static herr_t fuzz_H5Aexists_async(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;
    hid_t obj_id = (hid_t)Data[0];
    const char *attr_name = (const char *)&Data[1];
    bool exists;
    hid_t es_id = H5ES_NONE;

    return H5Aexists_async(obj_id, attr_name, &exists, es_id);
}

int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    fuzz_H5Aexists_by_name_async(Data, Size);
    fuzz_H5Aread_async(Data, Size);
    fuzz_H5Arename_by_name_async(Data, Size);
    fuzz_H5Dread_async(Data, Size);
    fuzz_H5Aclose_async(Data, Size);
    fuzz_H5Aexists_async(Data, Size);

    return 0;
}