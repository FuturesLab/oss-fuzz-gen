// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dget_space_async at H5D.c:625:1 in H5Dpublic.h
// H5Fcreate_async at H5F.c:673:1 in H5Fpublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Dcreate_async at H5D.c:206:1 in H5Dpublic.h
// H5Acreate_async at H5A.c:247:1 in H5Apublic.h
// H5Dopen_async at H5D.c:418:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Dpublic.h>
#include <H5Apublic.h>
#include <H5Fpublic.h>

static void prepare_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    prepare_dummy_file();

    const char *app_file = "fuzz_test.c";
    const char *app_func = "LLVMFuzzerTestOneInput";
    unsigned app_line = __LINE__;

    hid_t dset_id = (hid_t)Data[0];
    hid_t es_id = (hid_t)(Size > 1 ? Data[1] : 0);

    hid_t mem_type_id = (hid_t)(Size > 2 ? Data[2] : 0);
    hid_t mem_space_id = (hid_t)(Size > 3 ? Data[3] : 0);
    hid_t file_space_id = (hid_t)(Size > 4 ? Data[4] : 0);
    hid_t dxpl_id = (hid_t)(Size > 5 ? Data[5] : 0);

    hid_t fcpl_id = (hid_t)(Size > 6 ? Data[6] : 0);
    hid_t fapl_id = (hid_t)(Size > 7 ? Data[7] : 0);

    hid_t loc_id = (hid_t)(Size > 8 ? Data[8] : 0);
    hid_t type_id = (hid_t)(Size > 9 ? Data[9] : 0);
    hid_t space_id = (hid_t)(Size > 10 ? Data[10] : 0);
    hid_t lcpl_id = (hid_t)(Size > 11 ? Data[11] : 0);
    hid_t dcpl_id = (hid_t)(Size > 12 ? Data[12] : 0);
    hid_t dapl_id = (hid_t)(Size > 13 ? Data[13] : 0);
    hid_t acpl_id = (hid_t)(Size > 14 ? Data[14] : 0);
    hid_t aapl_id = (hid_t)(Size > 15 ? Data[15] : 0);

    void *buf = malloc(1024);
    if (!buf) return 0;

    // Test H5Dget_space_async
    hid_t space = H5Dget_space_async(dset_id, es_id);
    if (space >= 0) {
        // Normally you would use the space here
    }

    // Test H5Fcreate_async
    hid_t file = H5Fcreate_async("./dummy_file", 0, fcpl_id, fapl_id, es_id);
    if (file >= 0) {
        // Normally you would use the file here
    }

    // Test H5Dread_async
    herr_t read_status = H5Dread_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
    if (read_status >= 0) {
        // Normally you would process the read data here
    }

    // Test H5Dcreate_async
    hid_t dataset = H5Dcreate_async(loc_id, "dataset", type_id, space_id, lcpl_id, dcpl_id, dapl_id, es_id);
    if (dataset >= 0) {
        // Normally you would use the dataset here
    }

    // Test H5Acreate_async
    hid_t attribute = H5Acreate_async(loc_id, "attribute", type_id, space_id, acpl_id, aapl_id, es_id);
    if (attribute >= 0) {
        // Normally you would use the attribute here
    }

    // Test H5Dopen_async
    hid_t opened_dataset = H5Dopen_async(loc_id, "dataset", dapl_id, es_id);
    if (opened_dataset >= 0) {
        // Normally you would use the opened dataset here
    }

    free(buf);
    return 0;
}