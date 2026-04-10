// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_dynprintf at janet.c:18262:6 in janet.h
// janet_dynfile at janet.c:17994:7 in janet.h
// janet_unwrapfile at janet.c:18340:7 in janet.h
// janet_ev_lasterr at janet.c:11280:7 in janet.h
// janet_dynprintf at janet.c:18262:6 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_getfile at janet.c:18322:7 in janet.h
// janet_init at vm.c:1652:5 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_dynprintf(const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    const char *name = (const char *)Data;
    FILE *dflt_file = fopen("./dummy_file", "w");
    if (!dflt_file) return;
    const char *format = "%s";
    janet_dynprintf(name, dflt_file, format, "Fuzzing janet_dynprintf");
    fclose(dflt_file);
}

static void fuzz_janet_dynfile(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    const char *name = (const char *)Data;
    FILE *def = fopen("./dummy_file", "w");
    if (!def) return;
    FILE *file = janet_dynfile(name, def);
    if (file && file != def) fclose(file);
    fclose(def);
}

static void fuzz_janet_unwrapfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet j;
    memcpy(&j, Data, sizeof(Janet));
    int32_t flags;
    FILE *file = janet_unwrapfile(j, &flags);
    if (file) fclose(file);
}

static void fuzz_janet_ev_lasterr(void) {
    Janet err = janet_ev_lasterr();
    janet_dynprintf(NULL, stdout, "Last error: %s\n", janet_unwrap_string(err));
}

static void fuzz_janet_getfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet argv[1];
    memcpy(argv, Data, sizeof(Janet));
    int32_t flags;
    FILE *file = janet_getfile(argv, 0, &flags);
    if (file) fclose(file);
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
    fuzz_janet_dynprintf(Data, Size);
    fuzz_janet_dynfile(Data, Size);
    fuzz_janet_unwrapfile(Data, Size);
    fuzz_janet_ev_lasterr();
    fuzz_janet_getfile(Data, Size);
    return 0;
}