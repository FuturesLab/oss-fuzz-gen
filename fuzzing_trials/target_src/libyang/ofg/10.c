#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "/src/libyang/build/libyang/parser_schema.h"

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    char **search_paths = (char **)malloc(sizeof(char *) * 2);
    char *result_path = NULL;
    LYS_INFORMAT format = LYS_IN_YANG;
    LY_ERR err;

    if (size < 2) {
        free(search_paths);
        return 0;
    }

    // Initialize search paths
    search_paths[0] = strdup("/tmp");
    search_paths[1] = NULL;

    // Create a temporary file to store fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        free(search_paths[0]);
        free(search_paths);
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Call the function-under-test
    err = lys_search_localfile((const char * const *)search_paths, 1, tmpl, "module-name", &result_path, &format);

    // Clean up
    free(search_paths[0]);
    free(search_paths);
    if (result_path) {
        free(result_path);
    }
    unlink(tmpl);

    return 0;
}