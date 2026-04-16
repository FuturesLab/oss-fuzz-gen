#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    hsize_t filesize;
    herr_t status;

    // Create a temporary file for testing
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit early
    }

    // Simulate writing data to the file to ensure it's not empty
    if (size > 0) {
        hid_t dataspace_id = H5Screate_simple(1, &size, NULL);
        hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_UINT8, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        H5Dwrite(dataset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        H5Dclose(dataset_id);
        H5Sclose(dataspace_id);
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fcreate to H5Aiterate2
    hsize_t ret_H5Aget_storage_size_pnrfn = H5Aget_storage_size(file_id);
    herr_t ret_H5Aiterate2_rvfpi = H5Aiterate2(file_id, 0, 0, &ret_H5Aget_storage_size_pnrfn, NULL, (void *)"w");
    // End mutation: Producer.APPEND_MUTATOR
    

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aiterate2 to H5Dvlen_get_buf_size
    hid_t ret_H5Dget_create_plist_dizva = H5Dget_create_plist(file_id);
    hid_t ret_H5Aget_create_plist_abjlm = H5Aget_create_plist(file_id);
    herr_t ret_H5Dvlen_get_buf_size_dkxhk = H5Dvlen_get_buf_size(ret_H5Dget_create_plist_dizva, file_id, ret_H5Aget_create_plist_abjlm, &ret_H5Aget_storage_size_pnrfn);
    // End mutation: Producer.APPEND_MUTATOR
    
    status = H5Fget_filesize(file_id, &filesize);

    // Close the file

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_filesize to H5Aiterate1
    unsigned int woetmocu = 64;
    herr_t ret_H5Aiterate1_wosng = H5Aiterate1(file_id, &woetmocu, NULL, (void *)&filesize);
    // End mutation: Producer.APPEND_MUTATOR
    

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aiterate1 to H5Aexists_by_name
    hid_t ret_H5Dget_create_plist_yfjbe = H5Dget_create_plist(0);
    htri_t ret_H5Aexists_by_name_naeej = H5Aexists_by_name(file_id, (const char *)data, &filesize, ret_H5Dget_create_plist_yfjbe);
    // End mutation: Producer.APPEND_MUTATOR
    
    H5Fclose(file_id);

    // Return success
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

    LLVMFuzzerTestOneInput_6(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
