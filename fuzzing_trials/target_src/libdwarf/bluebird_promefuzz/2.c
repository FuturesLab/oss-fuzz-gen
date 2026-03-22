#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "libdwarf.h"

static void fuzz_dwarf_get_VIRTUALITY_name(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int dw_val_in = *(unsigned int *)Data;
    const char *dw_s_out = NULL;
    dwarf_get_VIRTUALITY_name(dw_val_in, &dw_s_out);
}

static void fuzz_dwarf_get_ID_name(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int dw_val_in = *(unsigned int *)Data;
    const char *dw_s_out = NULL;
    dwarf_get_ID_name(dw_val_in, &dw_s_out);
}

static void fuzz_dwarf_get_OP_name(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int dw_val_in = *(unsigned int *)Data;
    const char *dw_s_out = NULL;
    dwarf_get_OP_name(dw_val_in, &dw_s_out);
}

static void fuzz_dwarf_get_ORD_name(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int dw_val_in = *(unsigned int *)Data;
    const char *dw_s_out = NULL;
    dwarf_get_ORD_name(dw_val_in, &dw_s_out);
}

static void fuzz_dwarf_get_SECT_name(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int dw_val_in = *(unsigned int *)Data;
    const char *dw_s_out = NULL;
    dwarf_get_SECT_name(dw_val_in, &dw_s_out);
}

static void fuzz_dwarf_get_ATCF_name(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int dw_val_in = *(unsigned int *)Data;
    const char *dw_s_out = NULL;
    dwarf_get_ATCF_name(dw_val_in, &dw_s_out);
}

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    fuzz_dwarf_get_VIRTUALITY_name(Data, Size);
    fuzz_dwarf_get_ID_name(Data, Size);
    fuzz_dwarf_get_OP_name(Data, Size);
    fuzz_dwarf_get_ORD_name(Data, Size);
    fuzz_dwarf_get_SECT_name(Data, Size);
    fuzz_dwarf_get_ATCF_name(Data, Size);
    return 0;
}