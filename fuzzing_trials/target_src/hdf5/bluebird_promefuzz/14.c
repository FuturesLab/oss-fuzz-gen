#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "/src/hdf5/src/H5Dpublic.h"
#include "/src/hdf5/src/H5Apublic.h"
#include "/src/hdf5/src/H5Fpublic.h"

static void prepare_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

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
    if (!buf) {
        return 0;
    }

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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dcreate_async to H5Fget_mdc_logging_status
    _Bool yjkbvhwx;
    memset(&yjkbvhwx, 0, sizeof(yjkbvhwx));
    herr_t ret_H5Fget_mdc_logging_status_somor = H5Fget_mdc_logging_status(dataset, &yjkbvhwx, NULL);
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_14(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
