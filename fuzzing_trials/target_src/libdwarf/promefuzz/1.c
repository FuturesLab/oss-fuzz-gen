// This fuzz driver is generated for library libdwarf, aiming to fuzz the following functions:
// dwarf_get_DEFAULTED_name at dwarf_names.c:2303:1 in libdwarf.h
// dwarf_get_GNUIKIND_name at dwarf_names.c:2479:1 in libdwarf.h
// dwarf_get_GNUIVIS_name at dwarf_names.c:2463:1 in libdwarf.h
// dwarf_get_IDX_name at dwarf_names.c:2322:1 in libdwarf.h
// dwarf_get_ISA_name at dwarf_names.c:3472:1 in libdwarf.h
// dwarf_get_LLEX_name at dwarf_names.c:2367:1 in libdwarf.h
// dwarf_get_LNCT_name at dwarf_names.c:3309:1 in libdwarf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "libdwarf.h"

#define DW_DLV_OK 0
#define DW_DLV_NO_ENTRY -1

static void fuzz_dwarf_get_DEFAULTED_name(const uint8_t *Data, size_t Size) {
    const char *output;
    for (size_t i = 0; i < 4 && i < Size; i++) {
        unsigned int value = Data[i];
        dwarf_get_DEFAULTED_name(value, &output);
    }
}

static void fuzz_dwarf_get_GNUIKIND_name(const uint8_t *Data, size_t Size) {
    const char *output;
    for (size_t i = 0; i < 4 && i < Size; i++) {
        unsigned int value = Data[i];
        dwarf_get_GNUIKIND_name(value, &output);
    }
}

static void fuzz_dwarf_get_GNUIVIS_name(const uint8_t *Data, size_t Size) {
    const char *output;
    for (size_t i = 0; i < 3 && i < Size; i++) {
        unsigned int value = Data[i];
        dwarf_get_GNUIVIS_name(value, &output);
    }
}

static void fuzz_dwarf_get_IDX_name(const uint8_t *Data, size_t Size) {
    const char *output;
    for (size_t i = 0; i < 4 && i < Size; i++) {
        unsigned int value = Data[i];
        dwarf_get_IDX_name(value, &output);
    }
}

static void fuzz_dwarf_get_ISA_name(const uint8_t *Data, size_t Size) {
    const char *output;
    for (size_t i = 0; i < 4 && i < Size; i++) {
        unsigned int value = Data[i];
        dwarf_get_ISA_name(value, &output);
    }
}

static void fuzz_dwarf_get_LLEX_name(const uint8_t *Data, size_t Size) {
    const char *output;
    for (size_t i = 0; i < 4 && i < Size; i++) {
        unsigned int value = Data[i];
        dwarf_get_LLEX_name(value, &output);
    }
}

static void fuzz_dwarf_get_LNCT_name(const uint8_t *Data, size_t Size) {
    const char *output;
    for (size_t i = 0; i < 6 && i < Size; i++) {
        unsigned int value = Data[i];
        dwarf_get_LNCT_name(value, &output);
    }
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    fuzz_dwarf_get_DEFAULTED_name(Data, Size);
    fuzz_dwarf_get_GNUIKIND_name(Data, Size);
    fuzz_dwarf_get_GNUIVIS_name(Data, Size);
    fuzz_dwarf_get_IDX_name(Data, Size);
    fuzz_dwarf_get_ISA_name(Data, Size);
    fuzz_dwarf_get_LLEX_name(Data, Size);
    fuzz_dwarf_get_LNCT_name(Data, Size);
    return 0;
}