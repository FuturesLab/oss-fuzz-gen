// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_resolve at janet.c:34444:18 in janet.h
// janet_resolve_ext at janet.c:34439:14 in janet.h
// janet_optsymbol at janet.c:4531:1 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static JanetTable dummy_table;
static Janet dummy_janet;
static Janet dummy_argv[1]; // Allocate space for one Janet element
static JanetString dummy_default_string = (JanetString)"default";
static const uint8_t dummy_symbol_data[] = "dummy_symbol";
static const uint8_t *dummy_symbol = dummy_symbol_data;

static JanetBindingType fuzz_janet_resolve(JanetTable *env, JanetSymbol sym, Janet *out) {
    return janet_resolve(env, sym, out);
}

static JanetBinding fuzz_janet_resolve_ext(JanetTable *env, JanetSymbol sym) {
    return janet_resolve_ext(env, sym);
}

static JanetSymbol fuzz_janet_optsymbol(const Janet *argv, int32_t argc, int32_t n, JanetString dflt) {
    return janet_optsymbol(argv, argc, n, dflt);
}

static JanetKeyword fuzz_janet_unwrap_keyword(Janet x) {
    return janet_unwrap_keyword(x);
}

static JanetSymbol fuzz_janet_unwrap_symbol(Janet x) {
    return janet_unwrap_symbol(x);
}

int LLVMFuzzerTestOneInput_489(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return 0;

    Janet input_janet;
    memcpy(&input_janet, Data, sizeof(Janet));

    // Initialize dummy_argv with a valid Janet value
    dummy_argv[0] = janet_wrap_nil(); // Example initialization with a nil value

    // Fuzz janet_resolve_ext
    fuzz_janet_resolve_ext(&dummy_table, dummy_symbol);

    // Fuzz janet_optsymbol
    fuzz_janet_optsymbol(dummy_argv, 1, 0, dummy_default_string);

    // Fuzz janet_resolve
    Janet out_janet;
    fuzz_janet_resolve(&dummy_table, dummy_symbol, &out_janet);

    // Fuzz janet_unwrap_keyword
    fuzz_janet_unwrap_keyword(input_janet);

    // Fuzz janet_unwrap_symbol
    fuzz_janet_unwrap_symbol(input_janet);

    return 0;
}