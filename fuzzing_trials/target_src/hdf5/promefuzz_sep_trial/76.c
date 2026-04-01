// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dread_multi_async at H5D.c:1139:1 in H5Dpublic.h
// H5Dwrite_multi_async at H5D.c:1449:1 in H5Dpublic.h
// H5Dwrite_async at H5D.c:1376:1 in H5Dpublic.h
// H5Dset_extent_async at H5D.c:2015:1 in H5Dpublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Awrite_async at H5A.c:931:1 in H5Apublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Apublic.h"

#define DUMMY_FILE "./dummy_file"

static void prepare_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fprintf(file, "dummy data");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 4 + sizeof(hsize_t)) {
        return 0;
    }

    prepare_dummy_file();

    size_t count = Size % 10 + 1; // Ensure at least one dataset
    hid_t dset_id[count];
    hid_t mem_type_id[count];
    hid_t mem_space_id[count];
    hid_t file_space_id[count];
    void *buf[count];
    hid_t dxpl_id = 0;
    hid_t es_id = 0;
    hsize_t size[1] = {Size % 1024 + 1};

    for (size_t i = 0; i < count; i++) {
        dset_id[i] = ((hid_t *)Data)[i % (Size / sizeof(hid_t))];
        mem_type_id[i] = ((hid_t *)Data)[(i + 1) % (Size / sizeof(hid_t))];
        mem_space_id[i] = ((hid_t *)Data)[(i + 2) % (Size / sizeof(hid_t))];
        file_space_id[i] = ((hid_t *)Data)[(i + 3) % (Size / sizeof(hid_t))];
        buf[i] = malloc(Size);
        if (buf[i]) {
            memcpy(buf[i], Data, Size);
        }
    }

    // Fuzz H5Dread_multi_async
    H5Dread_multi_async(count, dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);

    // Fuzz H5Dwrite_multi_async
    H5Dwrite_multi_async(count, dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, (const void **)buf, es_id);

    // Fuzz H5Dwrite_async
    H5Dwrite_async(dset_id[0], mem_type_id[0], mem_space_id[0], file_space_id[0], dxpl_id, buf[0], es_id);

    // Fuzz H5Dset_extent_async
    H5Dset_extent_async(dset_id[0], size, es_id);

    // Fuzz H5Dread_async
    H5Dread_async(dset_id[0], mem_type_id[0], mem_space_id[0], file_space_id[0], dxpl_id, buf[0], es_id);

    // Fuzz H5Awrite_async
    H5Awrite_async(dset_id[0], mem_type_id[0], buf[0], es_id);

    for (size_t i = 0; i < count; i++) {
        free(buf[i]);
    }

    return 0;
}