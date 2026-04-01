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

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    fuzz_dwarf_get_DEFAULTED_name(Data, Size);
    fuzz_dwarf_get_GNUIKIND_name(Data, Size);
    fuzz_dwarf_get_GNUIVIS_name(Data, Size);
    fuzz_dwarf_get_IDX_name(Data, Size);
    fuzz_dwarf_get_ISA_name(Data, Size);
    fuzz_dwarf_get_LLEX_name(Data, Size);
    fuzz_dwarf_get_LNCT_name(Data, Size);
    return 0;
}