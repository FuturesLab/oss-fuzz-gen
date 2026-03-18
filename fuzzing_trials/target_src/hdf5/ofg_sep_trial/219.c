#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    H5F_mem_t type;
    size_t nsects;
    H5F_sect_info_t *sect_info = NULL;
    ssize_t result;

    // Ensure the data size is sufficient for the test
    if (size < sizeof(hid_t) + sizeof(H5F_mem_t) + sizeof(size_t)) {
        return 0;
    }

    // Extract values from data
    file_id = *((hid_t *)data);
    type = *((H5F_mem_t *)(data + sizeof(hid_t)));
    nsects = *((size_t *)(data + sizeof(hid_t) + sizeof(H5F_mem_t)));

    // Allocate memory for sect_info based on nsects
    if (nsects > 0) {
        sect_info = (H5F_sect_info_t *)malloc(nsects * sizeof(H5F_sect_info_t));
        if (sect_info == NULL) {
            return 0;
        }
    }

    // Call the function under test
    result = H5Fget_free_sections(file_id, type, nsects, sect_info);

    // Clean up
    if (sect_info != NULL) {
        free(sect_info);
    }

    return 0;
}