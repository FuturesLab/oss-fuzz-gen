// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Fformat_convert at H5F.c:2447:1 in H5Fpublic.h
// H5Diterate at H5D.c:1842:1 in H5Dpublic.h
// H5Dformat_convert at H5D.c:2139:1 in H5Dpublic.h
// H5Dget_chunk_storage_size at H5D.c:2218:1 in H5Dpublic.h
// H5Dwrite_chunk at H5D.c:1491:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Ppublic.h" // Include this header for H5P_DEFAULT

#define DUMMY_FILE "./dummy_file"

static void write_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fputs("HDF5 dummy content", file);
        fclose(file);
    }
}

static herr_t dummy_callback(void *elem, hid_t type_id, hsize_t ndim, const hsize_t *point, void *operator_data) {
    return 0;
}

int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t)) return 0;

    hid_t file_id = *((hid_t *)Data);
    Data += sizeof(hid_t);
    Size -= sizeof(hid_t);

    // Prepare environment
    write_dummy_file();

    // Fuzz H5Fformat_convert
    herr_t result1 = H5Fformat_convert(file_id);
    if (result1 < 0) {
        // Handle error
    }

    // Fuzz H5Diterate
    if (Size >= sizeof(hid_t) * 2) {
        void *buf = malloc(Size);
        if (!buf) return 0;

        hid_t type_id = *((hid_t *)Data);
        hid_t space_id = *((hid_t *)(Data + sizeof(hid_t)));
        void *operator_data = NULL;

        herr_t result2 = H5Diterate(buf, type_id, space_id, dummy_callback, operator_data);
        if (result2 < 0) {
            // Handle error
        }
        free(buf);
    }

    // Fuzz H5Dformat_convert
    herr_t result3 = H5Dformat_convert(file_id);
    if (result3 < 0) {
        // Handle error
    }

    // Fuzz H5Dget_chunk_storage_size
    if (Size >= sizeof(hsize_t)) {
        hsize_t offset = *((hsize_t *)Data);
        hsize_t chunk_bytes;
        herr_t result4 = H5Dget_chunk_storage_size(file_id, &offset, &chunk_bytes);
        if (result4 < 0) {
            // Handle error
        }
    }

    // Fuzz H5Dwrite_chunk
    if (Size >= sizeof(hsize_t) + sizeof(uint32_t) + sizeof(size_t)) {
        uint32_t filters = *((uint32_t *)Data);
        hsize_t offset = *((hsize_t *)(Data + sizeof(uint32_t)));
        size_t data_size = *((size_t *)(Data + sizeof(uint32_t) + sizeof(hsize_t)));
        void *buf = malloc(data_size);

        if (buf) {
            herr_t result5 = H5Dwrite_chunk(file_id, H5P_DEFAULT, filters, &offset, data_size, buf);
            if (result5 < 0) {
                // Handle error
            }
            free(buf);
        }
    }

    // Fuzz H5Dwrite
    if (Size >= sizeof(hid_t) * 4) {
        hid_t mem_type_id = *((hid_t *)Data);
        hid_t mem_space_id = *((hid_t *)(Data + sizeof(hid_t)));
        hid_t file_space_id = *((hid_t *)(Data + 2 * sizeof(hid_t)));
        void *buf = malloc(Size - 3 * sizeof(hid_t));

        if (buf) {
            herr_t result6 = H5Dwrite(file_id, mem_type_id, mem_space_id, file_space_id, H5P_DEFAULT, buf);
            if (result6 < 0) {
                // Handle error
            }
            free(buf);
        }
    }

    return 0;
}