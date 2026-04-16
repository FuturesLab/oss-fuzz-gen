#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "/src/hdf5/src/H5Dpublic.h"
#include "/src/hdf5/src/H5Fpublic.h"
#include "/src/hdf5/src/H5Spublic.h"
#include "/src/hdf5/src/H5Ppublic.h"

static herr_t handle_error(herr_t status, const char *msg) {
    if (status < 0) {
        fprintf(stderr, "%s\n", msg);
    }
    return status;
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 2) {
        return 0;
    }

    // Initialize identifiers
    hid_t file_id = *((hid_t *)Data);
    hid_t dset_id = *((hid_t *)(Data + sizeof(hid_t)));

    // Dummy buffer
    void *buf = malloc(1024);
    if (!buf) {
        return 0;
    }

    // Refresh dataset
    handle_error(H5Drefresh(dset_id), "Failed to refresh dataset");

    // Read dataset
    handle_error(H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf), "Failed to read dataset");

    // Close dataset
    handle_error(H5Dclose(dset_id), "Failed to close dataset");

    // Close file
    handle_error(H5Fclose(file_id), "Failed to close file");

    // Write dataset
    handle_error(H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf), "Failed to write dataset");

    // Close dataset
    handle_error(H5Dclose(dset_id), "Failed to close dataset");

    // Close file
    handle_error(H5Fclose(file_id), "Failed to close file");

    // Start SWMR write
    handle_error(H5Fstart_swmr_write(file_id), "Failed to start SWMR write");

    // Read dataset
    handle_error(H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf), "Failed to read dataset");

    // Close dataset
    handle_error(H5Dclose(dset_id), "Failed to close dataset");

    // Close file
    handle_error(H5Fclose(file_id), "Failed to close file");

    // Close dataset multiple times
    for (int i = 0; i < 4; i++) {
        handle_error(H5Dclose(dset_id), "Failed to close dataset");
    }

    // Close file multiple times
    for (int i = 0; i < 4; i++) {
        handle_error(H5Fclose(file_id), "Failed to close file");
    }

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

    LLVMFuzzerTestOneInput_37(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
