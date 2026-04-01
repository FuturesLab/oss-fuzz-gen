// This fuzz driver is generated for library libdwarf, aiming to fuzz the following functions:
// dwarf_get_GNUIVIS_name at dwarf_names.c:2463:1 in libdwarf.h
// dwarf_get_DS_name at dwarf_names.c:2572:1 in libdwarf.h
// dwarf_get_DEFAULTED_name at dwarf_names.c:2303:1 in libdwarf.h
// dwarf_get_IDX_name at dwarf_names.c:2322:1 in libdwarf.h
// dwarf_get_FORM_name at dwarf_names.c:410:1 in libdwarf.h
// dwarf_get_GNUIKIND_name at dwarf_names.c:2479:1 in libdwarf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

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

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
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