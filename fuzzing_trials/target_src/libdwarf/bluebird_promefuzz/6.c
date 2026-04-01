#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "libdwarf.h"

static void fuzz_dwarf_get_GNUIVIS_name(unsigned int value) {
    const char *name = NULL;
    dwarf_get_GNUIVIS_name(value, &name);
}

static void fuzz_dwarf_get_DS_name(unsigned int value) {
    const char *name = NULL;
    dwarf_get_DS_name(value, &name);
}

static void fuzz_dwarf_get_DEFAULTED_name(unsigned int value) {
    const char *name = NULL;
    dwarf_get_DEFAULTED_name(value, &name);
}

static void fuzz_dwarf_get_IDX_name(unsigned int value) {
    const char *name = NULL;
    dwarf_get_IDX_name(value, &name);
}

static void fuzz_dwarf_get_FORM_name(unsigned int value) {
    const char *name = NULL;
    dwarf_get_FORM_name(value, &name);
}

static void fuzz_dwarf_get_GNUIKIND_name(unsigned int value) {
    const char *name = NULL;
    dwarf_get_GNUIKIND_name(value, &name);
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int value = *(unsigned int *)Data;

    fuzz_dwarf_get_GNUIVIS_name(value);
    fuzz_dwarf_get_DS_name(value);
    fuzz_dwarf_get_DEFAULTED_name(value);
    fuzz_dwarf_get_IDX_name(value);
    fuzz_dwarf_get_FORM_name(value);
    fuzz_dwarf_get_GNUIKIND_name(value);

    return 0;
}