// This fuzz driver is generated for library libdwarf, aiming to fuzz the following functions:
// dwarf_get_LNS_name at dwarf_names.c:3355:1 in libdwarf.h
// dwarf_get_LNE_name at dwarf_names.c:3412:1 in libdwarf.h
// dwarf_get_LNAME_name at dwarf_names.c:2966:1 in libdwarf.h
// dwarf_get_AT_name at dwarf_names.c:564:1 in libdwarf.h
// dwarf_get_RLE_name at dwarf_names.c:2429:1 in libdwarf.h
// dwarf_get_ATCF_name at dwarf_names.c:2622:1 in libdwarf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

static void fuzz_dwarf_get_LNS_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int result = dwarf_get_LNS_name(dw_val_in, &dw_s_out);
    if (result == DW_DLV_OK) {
        // Successfully retrieved the LNS name
    }
}

static void fuzz_dwarf_get_LNE_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int result = dwarf_get_LNE_name(dw_val_in, &dw_s_out);
    if (result == DW_DLV_OK) {
        // Successfully retrieved the LNE name
    }
}

static void fuzz_dwarf_get_LNAME_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int result = dwarf_get_LNAME_name(dw_val_in, &dw_s_out);
    if (result == DW_DLV_OK) {
        // Successfully retrieved the LNAME name
    }
}

static void fuzz_dwarf_get_AT_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int result = dwarf_get_AT_name(dw_val_in, &dw_s_out);
    if (result == DW_DLV_OK) {
        // Successfully retrieved the AT name
    }
}

static void fuzz_dwarf_get_RLE_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int result = dwarf_get_RLE_name(dw_val_in, &dw_s_out);
    if (result == DW_DLV_OK) {
        // Successfully retrieved the RLE name
    }
}

static void fuzz_dwarf_get_ATCF_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int result = dwarf_get_ATCF_name(dw_val_in, &dw_s_out);
    if (result == DW_DLV_OK) {
        // Successfully retrieved the ATCF name
    }
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int dw_val_in = *(unsigned int *)Data;

    fuzz_dwarf_get_LNS_name(dw_val_in);
    fuzz_dwarf_get_LNE_name(dw_val_in);
    fuzz_dwarf_get_LNAME_name(dw_val_in);
    fuzz_dwarf_get_AT_name(dw_val_in);
    fuzz_dwarf_get_RLE_name(dw_val_in);
    fuzz_dwarf_get_ATCF_name(dw_val_in);

    return 0;
}