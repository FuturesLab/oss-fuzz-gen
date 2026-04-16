#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Dcreate2 to H5Dget_num_chunks
        hid_t ret_H5Aget_create_plist_tzdmr = H5Aget_create_plist(dataset_id);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Aget_create_plist to H5Dcreate2
        hid_t ret_H5Freopen_evrwp = H5Freopen(file_id);
        hid_t ret_H5Dget_type_vrydd = H5Dget_type(0);
        hid_t ret_H5Freopen_soqek = H5Freopen(file_id);
        hid_t ret_H5Fget_create_plist_weyxj = H5Fget_create_plist(0);
        hid_t ret_H5Dcreate2_eyxap = H5Dcreate2(ret_H5Freopen_evrwp, (const char *)"r", ret_H5Aget_create_plist_tzdmr, file_id, ret_H5Dget_type_vrydd, ret_H5Freopen_soqek, ret_H5Fget_create_plist_weyxj);
        // End mutation: Producer.APPEND_MUTATOR
        
        hsize_t ret_H5Dget_storage_size_flzqn = H5Dget_storage_size(file_id);
        herr_t ret_H5Dget_num_chunks_szrae = H5Dget_num_chunks(dataset_id, ret_H5Aget_create_plist_tzdmr, &ret_H5Dget_storage_size_flzqn);
        // End mutation: Producer.APPEND_MUTATOR
        
        H5Dwrite(dataset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        H5Dclose(dataset_id);
        H5Sclose(dataspace_id);
    }

    // Call the function-under-test
    status = H5Fget_filesize(file_id, &filesize);

    // Close the file
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

    LLVMFuzzerTestOneInput_104(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
