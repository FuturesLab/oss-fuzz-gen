#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern int hfile_list_plugins(const char **, int *);

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to avoid out-of-bounds access
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the char* array
    const char *plugin_names[2];
    char *plugin_name1 = (char *)malloc(size / 2 + 1);
    char *plugin_name2 = (char *)malloc(size / 2 + 1);

    if (plugin_name1 == NULL || plugin_name2 == NULL) {
        // Handle memory allocation failure
        free(plugin_name1);
        free(plugin_name2);
        return 0;
    }

    // Copy data into the plugin name buffers
    memcpy(plugin_name1, data, size / 2);
    plugin_name1[size / 2] = '\0';  // Null-terminate the string
    memcpy(plugin_name2, data + size / 2, size / 2);
    plugin_name2[size / 2] = '\0';  // Null-terminate the string

    // Initialize the plugin names array
    plugin_names[0] = plugin_name1;
    plugin_names[1] = plugin_name2;

    // Initialize an integer to hold the result
    int result = 0;

    // Call the function-under-test
    hfile_list_plugins(plugin_names, &result);

    // Free allocated memory
    free(plugin_name1);
    free(plugin_name2);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_1(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
