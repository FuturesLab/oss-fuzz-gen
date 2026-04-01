#include <stddef.h>
#include <stdint.h>
#include "libdwarf.h"
#include "dwarf.h"  // Include the dwarf.h header for DW_DLV_OK

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int vis_type = *(unsigned int *)data;
    const char *vis_name = NULL;

    // Call the function-under-test
    int result = dwarf_get_VIS_name(vis_type, &vis_name);

    // Optionally, you can use the result and vis_name for further checks
    // For example, ensure vis_name is not NULL if the result indicates success
    if (result == DW_DLV_OK && vis_name != NULL) {
        // Do something with vis_name if needed
    }

    return 0;
}