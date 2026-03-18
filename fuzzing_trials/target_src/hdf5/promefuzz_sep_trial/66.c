// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Aexists_async at H5A.c:2392:1 in H5Apublic.h
// H5Arename_by_name_async at H5A.c:1781:1 in H5Apublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Aclose_async at H5A.c:2224:1 in H5Apublic.h
// H5Aexists_by_name_async at H5A.c:2502:1 in H5Apublic.h
// H5Aread_async at H5A.c:1037:1 in H5Apublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "H5Dpublic.h"
#include "H5Apublic.h"

static hid_t generate_hid() {
    return (hid_t)(rand() % 1000);
}

int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char *dummy_file = "./dummy_file";
    FILE *file = fopen(dummy_file, "w");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    hid_t obj_id = generate_hid();
    hid_t loc_id = generate_hid();
    hid_t dset_id = generate_hid();
    hid_t attr_id = generate_hid();
    hid_t dtype_id = generate_hid();
    hid_t mem_type_id = generate_hid();
    hid_t mem_space_id = generate_hid();
    hid_t file_space_id = generate_hid();
    hid_t dxpl_id = generate_hid();
    hid_t lapl_id = generate_hid();
    hid_t es_id = generate_hid();

    bool attr_exists;
    char attr_name[256] = {0};
    char obj_name[256] = {0};
    char old_attr_name[256] = {0};
    char new_attr_name[256] = {0};
    void *buf = malloc(Size);

    if (buf == NULL) return 0;

    size_t copy_size = Size < 255 ? Size : 255;

    memcpy(attr_name, Data, copy_size);
    memcpy(obj_name, Data, copy_size);
    memcpy(old_attr_name, Data, copy_size);
    memcpy(new_attr_name, Data, copy_size);

    H5Aexists_async(obj_id, attr_name, &attr_exists, es_id);
    H5Arename_by_name_async(loc_id, obj_name, old_attr_name, new_attr_name, lapl_id, es_id);
    H5Dread_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
    H5Aclose_async(attr_id, es_id);
    H5Aexists_by_name_async(loc_id, obj_name, attr_name, &attr_exists, lapl_id, es_id);
    H5Aread_async(attr_id, dtype_id, buf, es_id);

    free(buf);
    return 0;
}