// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Aread at H5A.c:1014:1 in H5Apublic.h
// H5Fget_metadata_read_retry_info at H5F.c:2104:1 in H5Fpublic.h
// H5Fset_dset_no_attrs_hint at H5F.c:2722:1 in H5Fpublic.h
// H5Fget_dset_no_attrs_hint at H5F.c:2683:1 in H5Fpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Apublic.h"
#include "H5Fpublic.h"

static void initialize_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        // Write dummy content to the file
        const char dummy_content[] = "HDF5 dummy content";
        fwrite(dummy_content, sizeof(char), sizeof(dummy_content), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 5 + sizeof(bool)) {
        return 0;
    }

    initialize_dummy_file();

    hid_t dset_id = *(hid_t *)Data;
    hid_t mem_type_id = *(hid_t *)(Data + sizeof(hid_t));
    hid_t mem_space_id = *(hid_t *)(Data + 2 * sizeof(hid_t));
    hid_t file_space_id = *(hid_t *)(Data + 3 * sizeof(hid_t));
    hid_t dxpl_id = *(hid_t *)(Data + 4 * sizeof(hid_t));
    bool minimize = *(bool *)(Data + 5 * sizeof(hid_t));

    // Allocate a buffer for reading
    void *buf = malloc(Size);
    if (!buf) {
        return 0;
    }

    // Fuzz H5Dread
    H5Dread(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);

    // Fuzz H5Aread
    H5Aread(dset_id, mem_type_id, buf);

    // Fuzz H5Fget_metadata_read_retry_info
    H5F_retry_info_t retry_info = {0};
    if (H5Fget_metadata_read_retry_info(dset_id, &retry_info) >= 0) {
        // Free any allocated memory for retries
        for (unsigned i = 0; i < H5F_NUM_METADATA_READ_RETRY_TYPES; ++i) {
            if (retry_info.retries[i]) {
                free(retry_info.retries[i]);
            }
        }
    }

    // Fuzz H5Fset_dset_no_attrs_hint
    H5Fset_dset_no_attrs_hint(dset_id, minimize);

    // Fuzz H5Fget_dset_no_attrs_hint
    bool retrieved_minimize;
    H5Fget_dset_no_attrs_hint(dset_id, &retrieved_minimize);

    // Fuzz H5Fflush
    H5Fflush(dset_id, H5F_SCOPE_LOCAL);
    H5Fflush(dset_id, H5F_SCOPE_GLOBAL);

    free(buf);
    return 0;
}