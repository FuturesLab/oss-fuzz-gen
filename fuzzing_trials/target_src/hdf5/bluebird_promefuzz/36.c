#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include "/src/hdf5/src/H5Dpublic.h"
#include "/src/hdf5/src/H5Apublic.h"
#include "/src/hdf5/src/H5Fpublic.h"

static void initialize_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        // Write dummy content to the file
        const char dummy_content[] = "HDF5 dummy content";
        fwrite(dummy_content, sizeof(char), sizeof(dummy_content), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dread to H5Gcreate1
    hid_t ret_H5Aget_space_bvpmx = H5Aget_space(0);
    hid_t ret_H5Gcreate1_qadcw = H5Gcreate1(ret_H5Aget_space_bvpmx, (const char *)buf, -1);
    // End mutation: Producer.APPEND_MUTATOR
    

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Gcreate1 to H5Fget_intent
    unsigned int afakdwbs = 1;
    herr_t ret_H5Fget_intent_obrtb = H5Fget_intent(ret_H5Gcreate1_qadcw, &afakdwbs);
    // End mutation: Producer.APPEND_MUTATOR
    
    H5Aread(dset_id, mem_type_id, buf);

    // Fuzz H5Fget_metadata_read_retry_info

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aread to H5Fget_name
    hid_t ret_H5Aget_type_anara = H5Aget_type(0);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aget_type to H5Dget_chunk_index_type
    herr_t ret_H5Dget_chunk_index_type_uxxsm = H5Dget_chunk_index_type(ret_H5Aget_type_anara, NULL);
    // End mutation: Producer.APPEND_MUTATOR
    
    ssize_t ret_H5Fget_name_ndiqn = H5Fget_name(ret_H5Aget_type_anara, (char *)buf, 0);
    // End mutation: Producer.APPEND_MUTATOR
    
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_metadata_read_retry_info to H5Aiterate1
    hid_t ret_H5Freopen_jlgni = H5Freopen(0);
    unsigned int qcwjhbrf = 0;
    herr_t ret_H5Aiterate1_wmjvm = H5Aiterate1(ret_H5Freopen_jlgni, &qcwjhbrf, NULL, (void *)&retry_info);
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_36(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
