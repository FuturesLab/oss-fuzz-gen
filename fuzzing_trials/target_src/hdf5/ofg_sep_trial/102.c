#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    hid_t group_id;
    const char *name;
    size_t size_buf;
    char *buf;

    // Initialize HDF5 library
    H5open();

    // Ensure size is large enough to extract necessary data
    if (size < sizeof(hid_t) + sizeof(size_t) + 1) {
        return 0;
    }

    // Extract group_id from input data
    group_id = *(const hid_t *)data;
    data += sizeof(hid_t);
    size -= sizeof(hid_t);

    // Extract size_buf from input data
    size_buf = *(const size_t *)data;
    data += sizeof(size_t);
    size -= sizeof(size_t);

    // Ensure there is enough data left for name and buffer
    if (size < 1 + size_buf) {
        return 0;
    }

    // Use the remaining data as a null-terminated string for name
    name = (const char *)data;
    data += strlen(name) + 1;
    size -= strlen(name) + 1;

    // Use the remaining data for buf
    buf = (char *)data;

    // Call the function-under-test
    H5Gget_linkval(group_id, name, size_buf, buf);

    // Close HDF5 library
    H5close();

    return 0;
}