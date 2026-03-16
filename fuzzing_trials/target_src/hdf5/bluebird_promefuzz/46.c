// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Awrite_async at H5A.c:931:1 in H5Apublic.h
// H5Arename_async at H5A.c:1669:1 in H5Apublic.h
// H5Arename_by_name_async at H5A.c:1781:1 in H5Apublic.h
// H5Aread_async at H5A.c:1037:1 in H5Apublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Aclose_async at H5A.c:2224:1 in H5Apublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "H5Dpublic.h"
#include "H5Apublic.h"

#define DUMMY_FILE "./dummy_file"

static hid_t generate_hid() {
    return (hid_t)(rand() % 1000 + 1);
}

static void write_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fprintf(file, "Dummy data for HDF5 testing.");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    // Extract different parts of data for different API calls
    hid_t attr_id = generate_hid();
    hid_t type_id = generate_hid();
    hid_t es_id = generate_hid();
    const void *buf = Data;
    hid_t loc_id = generate_hid();
    const char *old_name = "old_attr";
    const char *new_name = "new_attr";
    const char *obj_name = "object";
    hid_t lapl_id = generate_hid();
    hid_t dtype_id = generate_hid();
    hid_t dset_id = generate_hid();
    hid_t mem_type_id = generate_hid();
    hid_t mem_space_id = generate_hid();
    hid_t file_space_id = generate_hid();
    hid_t dxpl_id = generate_hid();

    // Call H5Awrite_async
    H5Awrite_async(attr_id, type_id, buf, es_id);

    // Call H5Arename_async
    H5Arename_async(loc_id, old_name, new_name, es_id);

    // Call H5Arename_by_name_async
    H5Arename_by_name_async(loc_id, obj_name, old_name, new_name, lapl_id, es_id);

    // Call H5Aread_async
    H5Aread_async(attr_id, dtype_id, (void *)buf, es_id);

    // Call H5Dread_async
    H5Dread_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, (void *)buf, es_id);

    // Call H5Aclose_async
    H5Aclose_async(attr_id, es_id);

    return 0;
}