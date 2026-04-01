// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Dset_extent at H5D.c:1991:1 in H5Dpublic.h
// H5Dformat_convert at H5D.c:2139:1 in H5Dpublic.h
// H5Dget_storage_size at H5D.c:848:1 in H5Dpublic.h
// H5Ddebug at H5Ddbg.c:63:1 in H5Dpublic.h
// H5Drefresh at H5D.c:2096:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file(const char *filename, const uint8_t *data, size_t size) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) + sizeof(hsize_t)) {
        return 0;
    }

    // Prepare dummy file
    write_dummy_file("./dummy_file", Data, Size);

    // Initialize variables
    hid_t loc_id = *((hid_t *)Data);
    Data += sizeof(hid_t);
    Size -= sizeof(hid_t);

    hsize_t size[1];
    memcpy(size, Data, sizeof(hsize_t));
    Data += sizeof(hsize_t);
    Size -= sizeof(hsize_t);

    // Create a simple dataspace
    hid_t space_id = H5Screate(H5S_SCALAR);

    // Create a dataset using H5Dcreate2
    hid_t dset_id = H5Dcreate2(loc_id, "./dummy_file", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id >= 0) {
        // Fuzz H5Dset_extent
        H5Dset_extent(dset_id, size);

        // Fuzz H5Dformat_convert
        H5Dformat_convert(dset_id);

        // Fuzz H5Dget_storage_size
        H5Dget_storage_size(dset_id);

        // Fuzz H5Ddebug
        H5Ddebug(dset_id);

        // Fuzz H5Drefresh
        H5Drefresh(dset_id);

        // Clean up
        H5Dclose(dset_id);
    }

    // Clean up dataspace
    H5Sclose(space_id);

    return 0;
}