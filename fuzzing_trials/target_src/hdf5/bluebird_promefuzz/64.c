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

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Aopen_by_idx_async
    hsize_t ret_H5Dget_storage_size_mpxqk = H5Dget_storage_size(0);
    hid_t ret_H5Fget_create_plist_taktk = H5Fget_create_plist(0);
    hid_t ret_H5Aopen_by_idx_async_ibgra = H5Aopen_by_idx_async((const char *)"r", (const char *)"w", -1, file_id2, (const char *)"r", 0, 0, ret_H5Dget_storage_size_mpxqk, 0, ret_H5Fget_create_plist_taktk, file_id1);
    // End mutation: Producer.APPEND_MUTATOR
    
    hid_t dset_id1 = H5Dopen2(file_id1, "dataset1", H5P_DEFAULT);
    hid_t dset_id2 = H5Dopen2(file_id2, "dataset2", H5P_DEFAULT);

    hsize_t nchunks;
    H5Dget_num_chunks(dset_id1, H5S_ALL, &nchunks);
    H5Dget_num_chunks(dset_id2, H5S_ALL, &nchunks);

    hsize_t offset[1] = {0};
    unsigned filter_mask;
    haddr_t addr;
    hsize_t size;

    H5Dget_chunk_info(dset_id1, H5S_ALL, 0, offset, &filter_mask, &addr, &size);
    H5Dget_chunk_info(dset_id2, H5S_ALL, 0, offset, &filter_mask, &addr, &size);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dget_chunk_info to H5Dwrite_multi
    hid_t ret_H5Dget_space_ezokz = H5Dget_space(dset_id1);
    hid_t ret_H5Aget_space_gzzsk = H5Aget_space(0);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aget_space to H5Aiterate_by_name
    hid_t ret_H5Freopen_akxjq = H5Freopen(ret_H5Dget_space_ezokz);
    herr_t ret_H5Aiterate_by_name_oeipq = H5Aiterate_by_name(ret_H5Freopen_akxjq, (const char *)"r", 0, 0, &size, NULL, (void *)&nchunks, ret_H5Aget_space_gzzsk);
    // End mutation: Producer.APPEND_MUTATOR
    
    hid_t ret_H5Aget_space_rwkuk = H5Aget_space(file_id1);
    hid_t ret_H5Dget_create_plist_znpzu = H5Dget_create_plist(file_id1);
    herr_t ret_H5Dwrite_multi_ayxmn = H5Dwrite_multi(Size, &ret_H5Dget_space_ezokz, NULL, &ret_H5Aget_space_gzzsk, &ret_H5Aget_space_rwkuk, ret_H5Dget_create_plist_znpzu, (const void **)&offset);
    // End mutation: Producer.APPEND_MUTATOR
    
    H5Dget_chunk_info_by_coord(dset_id1, offset, &filter_mask, &addr, &size);
    H5Dget_chunk_info_by_coord(dset_id2, offset, &filter_mask, &addr, &size);

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

    LLVMFuzzerTestOneInput_64(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
