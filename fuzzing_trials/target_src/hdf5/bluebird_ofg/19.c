#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t loc_id = H5I_INVALID_HID;
    char *name = NULL;

    // Ensure there's enough data to create a valid string
    if (size > 0) {
        // Allocate memory for the name and copy data into it
        name = (char *)malloc(size + 1);
        if (name == NULL) {
            return 0;
        }
        memcpy(name, data, size);
        name[size] = '\0'; // Null-terminate the string

        // Create a HDF5 file in memory to obtain a valid hid_t
        hid_t file_id = H5Fcreate("testfile", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        if (file_id >= 0) {
            loc_id = file_id;
        }
    }

    // Call the function-under-test
    H5Funmount(loc_id, name);

    // Clean up
    if (loc_id != H5I_INVALID_HID) {
        H5Fclose(loc_id);
    }
    free(name);

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

    LLVMFuzzerTestOneInput_19(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
