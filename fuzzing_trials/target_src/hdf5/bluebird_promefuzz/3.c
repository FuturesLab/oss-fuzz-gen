#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include "/src/hdf5/src/H5Fpublic.h"
#include "/src/hdf5/src/H5Ppublic.h"

static void handle_hid_t(hid_t id) {
    if (id >= 0) {
        H5Pclose(id);
    }
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a dummy file
    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Close the file
    H5Fclose(file_id);

    // Re-create the file
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Get file info
    H5F_info1_t file_info;
    if (H5Fget_info1(file_id, &file_info) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Get file creation property list
    hid_t plist_id = H5Fget_create_plist(file_id);
    handle_hid_t(plist_id);

    // Set latest format
    H5Fset_latest_format(file_id, Data[0] % 2 == 0);

    // Close the file
    H5Fclose(file_id);

    // Re-create the file
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Get file access property list
    plist_id = H5Fget_access_plist(file_id);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_access_plist to H5Dget_chunk_info_by_coord
    hsize_t ret_H5Aget_storage_size_tvrsa = H5Aget_storage_size(0);
    haddr_t ret_H5Dget_offset_wjjte = H5Dget_offset(plist_id);
    hsize_t ret_H5Dget_storage_size_brvya = H5Dget_storage_size(plist_id);
    herr_t ret_H5Dget_chunk_info_by_coord_tdsje = H5Dget_chunk_info_by_coord(plist_id, &ret_H5Aget_storage_size_tvrsa, NULL, &ret_H5Dget_offset_wjjte, &ret_H5Dget_storage_size_brvya);
    // End mutation: Producer.APPEND_MUTATOR
    
    handle_hid_t(plist_id);

    // Get file info again
    if (H5Fget_info1(file_id, &file_info) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Get file creation property list again
    plist_id = H5Fget_create_plist(file_id);
    handle_hid_t(plist_id);

    // Close the file
    H5Fclose(file_id);

    // Open the file
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Get file info
    if (H5Fget_info1(file_id, &file_info) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Get file creation property list

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Aopen_idx
    hid_t ret_H5Aopen_idx_mnreg = H5Aopen_idx(file_id, 0);
    // End mutation: Producer.APPEND_MUTATOR
    
    plist_id = H5Fget_create_plist(file_id);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_create_plist to H5Dgather
    hid_t ret_H5Freopen_xfxzk = H5Freopen(file_id);
    char xtkntkas[1024] = "opcup";
    herr_t ret_H5Dgather_kbryd = H5Dgather(plist_id, xtkntkas, ret_H5Freopen_xfxzk, 1, (void *)"w", NULL, (void *)"w");
    // End mutation: Producer.APPEND_MUTATOR
    
    handle_hid_t(plist_id);

    // Close the file
    H5Fclose(file_id);

    // Re-create the file
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Get file creation property list
    plist_id = H5Fget_create_plist(file_id);
    handle_hid_t(plist_id);

    // Close the file
    H5Fclose(file_id);

    // Open the file
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Get file creation property list
    plist_id = H5Fget_create_plist(file_id);
    handle_hid_t(plist_id);

    // Close the file
    H5Fclose(file_id);

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

    LLVMFuzzerTestOneInput_3(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
