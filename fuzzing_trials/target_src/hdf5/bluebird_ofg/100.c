#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract parameters.
    if (size < 8) {
        return 0;
    } // Adjust size as needed for your parameters

    // Extract parameters from the data
    const char *file_name = "testfile.h5"; // Static file name for testing
    unsigned int create_mode = (unsigned int)data[0];
    hid_t fcpl_id = (hid_t)(data[1] | (data[2] << 8));
    hid_t fapl_id = (hid_t)(data[3] | (data[4] << 8));
    hid_t es_id = (hid_t)(data[5] | (data[6] << 8));

    // Call the function-under-test
    hid_t file_id = H5Fcreate(file_name, create_mode, fcpl_id, fapl_id);

    // Close the file if it was successfully created
    if (file_id >= 0) {
        H5Fclose(file_id);
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fcreate to H5Dcreate_anon
    hid_t ret_H5Aget_type_ozxvo = H5Aget_type(file_id);
    hid_t ret_H5Dget_access_plist_hzpwm = H5Dget_access_plist(0);
    hid_t ret_H5Dget_type_cgnea = H5Dget_type(0);
    hid_t ret_H5Fget_access_plist_giirv = H5Fget_access_plist(file_id);
    hid_t ret_H5Dcreate_anon_buily = H5Dcreate_anon(ret_H5Aget_type_ozxvo, ret_H5Dget_access_plist_hzpwm, ret_H5Dget_type_cgnea, file_id, ret_H5Fget_access_plist_giirv);
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_100(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
