#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the file name string
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0;
    }

    // Copy data into filename and null-terminate it
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Use a valid hid_t for fapl_id, H5P_DEFAULT is often used for default property lists
    hid_t fapl_id = H5P_DEFAULT;

    // Call the function-under-test
    htri_t result = H5Fis_accessible(filename, fapl_id);

    // Free allocated memory
    free(filename);

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

    LLVMFuzzerTestOneInput_57(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
