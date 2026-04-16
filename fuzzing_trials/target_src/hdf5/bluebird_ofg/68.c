#include <stdint.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id = H5I_INVALID_HID; // Initialize with an invalid ID
    double hit_rate = 0.0;
    herr_t status;

    // Check if size is sufficient to create a valid file_id
    if (size >= sizeof(hid_t)) {
        // Use the data to create a valid file_id
        file_id = *((hid_t *)data);
    }

    // Call the function-under-test
    status = H5Fget_mdc_hit_rate(file_id, &hit_rate);

    // Ensure file_id is closed if it was opened
    if (file_id != H5I_INVALID_HID) {
        H5Fclose(file_id);
    }

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

    LLVMFuzzerTestOneInput_68(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
