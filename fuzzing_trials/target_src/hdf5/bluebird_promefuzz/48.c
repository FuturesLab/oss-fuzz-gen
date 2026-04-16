#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "/src/hdf5/src/H5Dpublic.h"
#include "/src/hdf5/src/H5Fpublic.h"
#include "/src/hdf5/src/H5Ppublic.h"
#include "/src/hdf5/src/H5Spublic.h"

static herr_t dummy_chunk_iter_cb(const hsize_t *offset, unsigned filter_mask, haddr_t addr, hsize_t size, void *op_data) {
    // Dummy callback function for H5Dchunk_iter
    return 0;
}

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a dummy file for testing
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    hid_t file_id1 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    hid_t file_id2 = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Fget_mdc_size
    size_t loqmaddg = Size;
    size_t bcxpdksm = 64;
    size_t zyzcoygn = 1;
    int qncwrrvp = 1;
    herr_t ret_H5Fget_mdc_size_nbcfl = H5Fget_mdc_size(file_id1, &loqmaddg, &bcxpdksm, &zyzcoygn, &qncwrrvp);
    // End mutation: Producer.APPEND_MUTATOR
    
    hid_t dset_id1 = H5Dopen2(file_id1, "dataset1", H5P_DEFAULT);
    hid_t dset_id2 = H5Dopen2(file_id2, "dataset2", H5P_DEFAULT);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dopen2 to H5Fget_obj_ids
    ssize_t ret_H5Fget_obj_ids_marfs = H5Fget_obj_ids(file_id2, (unsigned int )zyzcoygn, zyzcoygn, &dset_id2);
    // End mutation: Producer.APPEND_MUTATOR
    
    hsize_t nchunks;
    H5Dget_num_chunks(dset_id1, H5S_ALL, &nchunks);
    H5Dget_num_chunks(dset_id2, H5S_ALL, &nchunks);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dget_num_chunks to H5Dset_extent
    hid_t ret_H5Aget_space_ncnpd = H5Aget_space(dset_id1);
    herr_t ret_H5Dset_extent_sinry = H5Dset_extent(ret_H5Aget_space_ncnpd, &nchunks);
    // End mutation: Producer.APPEND_MUTATOR
    
    hsize_t offset[1] = {0};
    unsigned filter_mask;
    haddr_t addr;
    hsize_t size;

    H5Dget_chunk_info(dset_id1, H5S_ALL, 0, offset, &filter_mask, &addr, &size);
    H5Dget_chunk_info(dset_id2, H5S_ALL, 0, offset, &filter_mask, &addr, &size);

    H5Dget_chunk_info_by_coord(dset_id1, offset, &filter_mask, &addr, &size);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dget_chunk_info_by_coord to H5Aopen_by_name_async
    hid_t ret_H5Dget_type_doxiq = H5Dget_type(0);
    hid_t ret_H5Freopen_bwqfb = H5Freopen(dset_id2);
    hid_t ret_H5Freopen_gglrn = H5Freopen(ret_H5Aget_space_ncnpd);
    hid_t ret_H5Dget_space_zidrn = H5Dget_space(0);
    hid_t ret_H5Aopen_by_name_async_edwfq = H5Aopen_by_name_async((const char *)"w", (const char *)"w", filter_mask, ret_H5Dget_type_doxiq, (const char *)"r", (const char *)Data, ret_H5Freopen_bwqfb, ret_H5Freopen_gglrn, ret_H5Dget_space_zidrn);
    // End mutation: Producer.APPEND_MUTATOR
    
    H5Dget_chunk_info_by_coord(dset_id2, offset, &filter_mask, &addr, &size);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dget_chunk_info_by_coord to H5Fget_free_sections
    hid_t ret_H5Aget_create_plist_vegsw = H5Aget_create_plist(0);
    ssize_t ret_H5Fget_free_sections_obxsd = H5Fget_free_sections(ret_H5Aget_create_plist_vegsw, H5FD_MEM_SUPER, (size_t )filter_mask, NULL);
    // End mutation: Producer.APPEND_MUTATOR
    
    H5Dchunk_iter(dset_id1, H5P_DEFAULT, dummy_chunk_iter_cb, NULL);
    H5Dchunk_iter(dset_id2, H5P_DEFAULT, dummy_chunk_iter_cb, NULL);

    H5Dclose(dset_id1);
    H5Dclose(dset_id2);

    H5Fclose(file_id1);
    H5Fclose(file_id2);

    H5Fdelete("./dummy_file", H5P_DEFAULT);
    H5Fdelete("./dummy_file", H5P_DEFAULT);

    H5Dclose(dset_id1);
    H5Dclose(dset_id2);

    H5Fclose(file_id1);
    H5Fclose(file_id2);

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

    LLVMFuzzerTestOneInput_48(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
