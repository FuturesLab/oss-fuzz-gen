#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    hid_t loc_id;
    const char *name;
    size_t bufsize;
    char *buf;

    // Ensure the input size is large enough to extract required parameters
    if (size < sizeof(hid_t) + sizeof(size_t) + 1) {
        return 0;
    }

    // Initialize loc_id from data
    memcpy(&loc_id, data, sizeof(hid_t));
    data += sizeof(hid_t);
    size -= sizeof(hid_t);

    // Initialize bufsize from data
    memcpy(&bufsize, data, sizeof(size_t));
    data += sizeof(size_t);
    size -= sizeof(size_t);

    // Ensure bufsize is not greater than remaining data size
    if (bufsize > size - 1) {
        bufsize = size - 1;
    }

    // Initialize name from data
    name = (const char *)data;
    data += size - bufsize;
    size -= size - bufsize;

    // Allocate memory for buf
    buf = (char *)malloc(bufsize + 1);
    if (buf == NULL) {
        return 0;
    }

    // Call the function-under-test
    H5Gget_comment(loc_id, name, bufsize, buf);

    // Free allocated memory
    free(buf);

    return 0;
}