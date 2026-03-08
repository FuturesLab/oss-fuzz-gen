// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_parser_add_fd at ucl_util.c:2115:6 in ucl.h
// ucl_parser_get_error at ucl_util.c:665:1 in ucl.h
// ucl_parser_get_object at ucl_util.c:590:1 in ucl.h
// ucl_object_ref at ucl_util.c:3591:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <unistd.h>
#include <fcntl.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    write_dummy_file(Data, Size);

    int fd = open("./dummy_file", O_RDONLY);
    if (fd == -1) {
        ucl_parser_free(parser);
        return 0;
    }

    bool result = ucl_parser_add_fd(parser, fd);
    close(fd);

    const char *error = ucl_parser_get_error(parser);
    if (error != NULL) {
        // Handle error if needed
    }

    ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj != NULL) {
        ucl_object_t *ref_obj = ucl_object_ref(obj);
        (void)ref_obj;
        ucl_object_unref(obj);
    }

    ucl_parser_free(parser);

    // Ensure to clean up any remaining objects
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}