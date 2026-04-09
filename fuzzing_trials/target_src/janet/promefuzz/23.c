// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_makejfile at janet.c:18328:12 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_unwrapfile at janet.c:18340:7 in janet.h
// janet_makefile at janet.c:18332:7 in janet.h
// janet_getjfile at janet.c:18318:12 in janet.h
// janet_getfile at janet.c:18322:7 in janet.h
// janet_file_close at janet.c:17826:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

static FILE *open_dummy_file(const char *mode) {
    FILE *f = fopen("./dummy_file", mode);
    if (f) {
        fprintf(f, "Dummy data for fuzz testing.");
        fflush(f);
        fseek(f, 0, SEEK_SET);
    }
    return f;
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    // Initialize Janet VM
    janet_init();

    int32_t flags = *(int32_t *)Data;
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    FILE *file = open_dummy_file("w+");
    if (!file) {
        janet_deinit();
        return 0;
    }

    // Test janet_makejfile
    JanetFile *jfile = janet_makejfile(file, flags);
    if (jfile) {
        // Test janet_unwrapfile
        Janet j = janet_wrap_abstract(jfile);
        int32_t out_flags;
        FILE *unwrapped_file = janet_unwrapfile(j, &out_flags);

        // Test janet_makefile
        Janet jfile_abstract = janet_makefile(unwrapped_file, out_flags);

        // Test janet_getjfile
        Janet argv[] = {jfile_abstract};
        JanetFile *retrieved_jfile = janet_getjfile(argv, 0);

        // Test janet_getfile
        FILE *retrieved_file = janet_getfile(argv, 0, &out_flags);

        // Ensure file is closed only once
        if (retrieved_jfile && retrieved_jfile->file) {
            janet_file_close(retrieved_jfile);
        }
    } else {
        fclose(file);
    }

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}