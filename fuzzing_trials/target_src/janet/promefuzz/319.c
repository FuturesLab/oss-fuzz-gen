// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_dynprintf at janet.c:18262:6 in janet.h
// janet_dynfile at janet.c:17994:7 in janet.h
// janet_unwrapfile at janet.c:18340:7 in janet.h
// janet_ev_lasterr at janet.c:11280:7 in janet.h
// janet_getfile at janet.c:18322:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

#define DUMMY_FILE_PATH "./dummy_file"

static void initialize_janet() {
    // Initialize the Janet VM
    janet_init();
}

static void cleanup_janet() {
    // Deinitialize the Janet VM
    janet_deinit();
}

static void fuzz_janet_dynprintf(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    // Prepare data for janet_dynprintf
    const char *name = (const char *)Data;
    FILE *dflt_file = fopen(DUMMY_FILE_PATH, "w");
    if (!dflt_file) return;

    // Use a simple format string
    const char *format = "%s";
    const char *arg = "fuzzing";

    // Call janet_dynprintf
    janet_dynprintf(name, dflt_file, format, arg);
    fclose(dflt_file);
}

static void fuzz_janet_dynfile(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    // Prepare data for janet_dynfile
    const char *name = (const char *)Data;
    FILE *def = fopen(DUMMY_FILE_PATH, "w");
    if (!def) return;

    // Call janet_dynfile
    FILE *result_file = janet_dynfile(name, def);
    if (result_file != def) {
        // Only close if result_file is not the same as def
        fclose(result_file);
    }
    fclose(def);
}

static void fuzz_janet_unwrapfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;

    // Prepare a dummy Janet object
    Janet j;
    memcpy(&j, Data, sizeof(Janet));
    int32_t flags = 0;

    // Call janet_unwrapfile
    FILE *file = janet_unwrapfile(j, &flags);
    if (file) fclose(file);
}

static void fuzz_janet_ev_lasterr() {
    // Call janet_ev_lasterr
    Janet error = janet_ev_lasterr();
    // Normally you would process the error, but for fuzzing we just call it
}

static void fuzz_janet_getfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;

    // Prepare a dummy Janet array
    const Janet *argv = (const Janet *)Data;
    int32_t flags = 0;

    // Call janet_getfile
    FILE *file = janet_getfile(argv, 0, &flags);
    if (file) fclose(file);
}

int LLVMFuzzerTestOneInput_319(const uint8_t *Data, size_t Size) {
    initialize_janet();

    fuzz_janet_dynprintf(Data, Size);
    fuzz_janet_dynfile(Data, Size);
    fuzz_janet_unwrapfile(Data, Size);
    fuzz_janet_ev_lasterr();
    fuzz_janet_getfile(Data, Size);

    cleanup_janet();
    return 0;
}