#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 3) return 0;

    // Split the input data into parts for the parameters
    size_t id_size = sizeof(hid_t);
    size_t name_size = (size - id_size) / 2;
    size_t comment_size = size - id_size - name_size;

    // Extract hid_t from data
    hid_t id;
    memcpy(&id, data, id_size);

    // Extract name from data
    char *name = (char *)malloc(name_size + 1);
    if (!name) return 0;
    memcpy(name, data + id_size, name_size);
    name[name_size] = '\0';

    // Extract comment from data
    char *comment = (char *)malloc(comment_size + 1);
    if (!comment) {
        free(name);
        return 0;
    }
    memcpy(comment, data + id_size + name_size, comment_size);
    comment[comment_size] = '\0';

    // Call the function under test
    H5Gset_comment(id, name, comment);

    // Free allocated memory
    free(name);
    free(comment);

    return 0;
}