// This fuzz driver is generated for library libdwarf, aiming to fuzz the following functions:
// dwarf_get_UT_name at dwarf_names.c:2504:1 in libdwarf.h
// dwarf_get_VIS_name at dwarf_names.c:2681:1 in libdwarf.h
// dwarf_get_FRAME_name at dwarf_names.c:3750:1 in libdwarf.h
// dwarf_get_INL_name at dwarf_names.c:3255:1 in libdwarf.h
// dwarf_get_DSC_name at dwarf_names.c:3293:1 in libdwarf.h
// dwarf_get_TAG_name at dwarf_names.c:12:1 in libdwarf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

static void fuzz_dwarf_get_UT_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int res = dwarf_get_UT_name(dw_val_in, &dw_s_out);
    if (res == DW_DLV_OK) {
        // Successfully retrieved the name
    } else {
        // Handle error or unknown value
    }
}

static void fuzz_dwarf_get_VIS_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int res = dwarf_get_VIS_name(dw_val_in, &dw_s_out);
    if (res == DW_DLV_OK) {
        // Successfully retrieved the name
    } else {
        // Handle error or unknown value
    }
}

static void fuzz_dwarf_get_FRAME_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int res = dwarf_get_FRAME_name(dw_val_in, &dw_s_out);
    if (res == DW_DLV_OK) {
        // Successfully retrieved the name
    } else {
        // Handle error or unknown value
    }
}

static void fuzz_dwarf_get_INL_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int res = dwarf_get_INL_name(dw_val_in, &dw_s_out);
    if (res == DW_DLV_OK) {
        // Successfully retrieved the name
    } else {
        // Handle error or unknown value
    }
}

static void fuzz_dwarf_get_DSC_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int res = dwarf_get_DSC_name(dw_val_in, &dw_s_out);
    if (res == DW_DLV_OK) {
        // Successfully retrieved the name
    } else {
        // Handle error or unknown value
    }
}

static void fuzz_dwarf_get_TAG_name(unsigned int dw_val_in) {
    const char *dw_s_out = NULL;
    int res = dwarf_get_TAG_name(dw_val_in, &dw_s_out);
    if (res == DW_DLV_OK) {
        // Successfully retrieved the name
    } else {
        // Handle error or unknown value
    }
}

int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) {
        return 0; // Not enough data to form an unsigned int
    }

    unsigned int dw_val_in = *(unsigned int *)Data;

    fuzz_dwarf_get_UT_name(dw_val_in);
    fuzz_dwarf_get_VIS_name(dw_val_in);
    fuzz_dwarf_get_FRAME_name(dw_val_in);
    fuzz_dwarf_get_INL_name(dw_val_in);
    fuzz_dwarf_get_DSC_name(dw_val_in);
    fuzz_dwarf_get_TAG_name(dw_val_in);

    return 0;
}