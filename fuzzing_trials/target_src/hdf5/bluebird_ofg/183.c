#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for testing
    if (size < sizeof(hid_t) + 1) {
        return 0;
    }

    // Extract a valid hid_t from the input data
    hid_t file_id = *((hid_t *)data);

    // Allocate a buffer for the file name
    size_t name_size = size - sizeof(hid_t);
    char *name_buffer = (char *)malloc(name_size);
    if (name_buffer == NULL) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of H5Fget_name
    ssize_t result = H5Fget_name(file_id, name_buffer, H5D_CHUNK_CACHE_W0_DEFAULT);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_name to H5Fget_vfd_handle
    hid_t ret_H5Aget_type_csrhw = H5Aget_type(0);
    hid_t ret_H5Aget_type_izwby = H5Aget_type(0);

    herr_t ret_H5Fget_vfd_handle_dmmit = H5Fget_vfd_handle(ret_H5Aget_type_csrhw, ret_H5Aget_type_izwby, (void **)&name_buffer);

    // End mutation: Producer.APPEND_MUTATOR

    free(name_buffer);

    return 0;
}