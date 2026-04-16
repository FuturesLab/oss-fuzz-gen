#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include "/src/hdf5/src/H5Dpublic.h"
#include "/src/hdf5/src/H5Apublic.h"
#include "/src/hdf5/src/H5Ppublic.h"
#include "/src/hdf5/src/H5ESpublic.h"

static herr_t fuzz_H5Aexists_by_name_async(const uint8_t *Data, size_t Size) {
    if (Size < 3) {
        return 0;
    }
    hid_t loc_id = (hid_t)Data[0];
    const char *obj_name = (const char *)&Data[1];
    const char *attr_name = (const char *)&Data[2];
    bool exists;
    hid_t lapl_id = H5P_DEFAULT;
    hid_t es_id = H5ES_NONE;

    return H5Aexists_by_name_async(loc_id, obj_name, attr_name, &exists, lapl_id, es_id);
}

static herr_t fuzz_H5Aread_async(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }
    hid_t attr_id = (hid_t)Data[0];
    hid_t dtype_id = (hid_t)Data[1];
    void *buf = malloc(1024); // Allocate buffer for reading
    hid_t es_id = H5ES_NONE;

    herr_t ret = H5Aread_async(attr_id, dtype_id, buf, es_id);
    free(buf);
    return ret;
}

static herr_t fuzz_H5Arename_by_name_async(const uint8_t *Data, size_t Size) {
    if (Size < 3) {
        return 0;
    }
    hid_t loc_id = (hid_t)Data[0];
    const char *obj_name = (const char *)&Data[1];
    const char *old_attr_name = (const char *)&Data[2];
    const char *new_attr_name = "new_attr_name";
    hid_t lapl_id = H5P_DEFAULT;
    hid_t es_id = H5ES_NONE;

    return H5Arename_by_name_async(loc_id, obj_name, old_attr_name, new_attr_name, lapl_id, es_id);
}

static herr_t fuzz_H5Dread_async(const uint8_t *Data, size_t Size) {
    if (Size < 5) {
        return 0;
    }
    hid_t dset_id = (hid_t)Data[0];
    hid_t mem_type_id = (hid_t)Data[1];
    hid_t mem_space_id = (hid_t)Data[2];
    hid_t file_space_id = (hid_t)Data[3];
    hid_t dxpl_id = (hid_t)Data[4];
    void *buf = malloc(1024); // Allocate buffer for reading
    hid_t es_id = H5ES_NONE;

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Dread_async with H5Dset_extent_async
    herr_t ret = H5Dset_extent_async(dset_id, mem_type_id, mem_space_id);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR
    free(buf);
    return ret;
}

static herr_t fuzz_H5Aclose_async(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }
    hid_t attr_id = (hid_t)Data[0];
    hid_t es_id = H5ES_NONE;

    return H5Aclose_async(attr_id, es_id);
}

static herr_t fuzz_H5Aexists_async(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }
    hid_t obj_id = (hid_t)Data[0];
    const char *attr_name = (const char *)&Data[1];
    bool exists;
    hid_t es_id = H5ES_NONE;

    return H5Aexists_async(obj_id, attr_name, &exists, es_id);
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    fuzz_H5Aexists_by_name_async(Data, Size);
    fuzz_H5Aread_async(Data, Size);
    fuzz_H5Arename_by_name_async(Data, Size);
    fuzz_H5Dread_async(Data, Size);
    fuzz_H5Aclose_async(Data, Size);
    fuzz_H5Aexists_async(Data, Size);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_13(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
