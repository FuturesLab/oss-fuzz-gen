// This fuzz driver is generated for library libdwarf, aiming to fuzz the following functions:
// dwarf_get_CC_name at dwarf_names.c:3148:1 in libdwarf.h
// dwarf_get_ATE_name at dwarf_names.c:2176:1 in libdwarf.h
// dwarf_get_LNS_name at dwarf_names.c:3355:1 in libdwarf.h
// dwarf_get_CFA_name at dwarf_names.c:3568:1 in libdwarf.h
// dwarf_get_EH_name at dwarf_names.c:3695:1 in libdwarf.h
// dwarf_get_MACRO_name at dwarf_names.c:3491:1 in libdwarf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "libdwarf.h"

static void fuzz_dwarf_get_CC_name(unsigned int dw_val_in) {
    const char *name = NULL;
    int res = dwarf_get_CC_name(dw_val_in, &name);
    if (res == DW_DLV_OK && name) {
        // Successfully retrieved the name
    }
}

static void fuzz_dwarf_get_ATE_name(unsigned int dw_val_in) {
    const char *name = NULL;
    int res = dwarf_get_ATE_name(dw_val_in, &name);
    if (res == DW_DLV_OK && name) {
        // Successfully retrieved the name
    }
}

static void fuzz_dwarf_get_LNS_name(unsigned int dw_val_in) {
    const char *name = NULL;
    int res = dwarf_get_LNS_name(dw_val_in, &name);
    if (res == DW_DLV_OK && name) {
        // Successfully retrieved the name
    }
}

static void fuzz_dwarf_get_CFA_name(unsigned int dw_val_in) {
    const char *name = NULL;
    int res = dwarf_get_CFA_name(dw_val_in, &name);
    if (res == DW_DLV_OK && name) {
        // Successfully retrieved the name
    }
}

static void fuzz_dwarf_get_EH_name(unsigned int dw_val_in) {
    const char *name = NULL;
    int res = dwarf_get_EH_name(dw_val_in, &name);
    if (res == DW_DLV_OK && name) {
        // Successfully retrieved the name
    }
}

static void fuzz_dwarf_get_MACRO_name(unsigned int dw_val_in) {
    const char *name = NULL;
    int res = dwarf_get_MACRO_name(dw_val_in, &name);
    if (res == DW_DLV_OK && name) {
        // Successfully retrieved the name
    }
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) {
        return 0; // Not enough data to form a valid input
    }

    unsigned int dw_val_in;
    // Extract an unsigned int from the input data
    dw_val_in = *(unsigned int *)Data;

    // Fuzz each target function with the extracted value
    fuzz_dwarf_get_CC_name(dw_val_in);
    fuzz_dwarf_get_ATE_name(dw_val_in);
    fuzz_dwarf_get_LNS_name(dw_val_in);
    fuzz_dwarf_get_CFA_name(dw_val_in);
    fuzz_dwarf_get_EH_name(dw_val_in);
    fuzz_dwarf_get_MACRO_name(dw_val_in);

    return 0;
}