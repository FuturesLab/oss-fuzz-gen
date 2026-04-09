#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test declaration
int hfile_list_plugins(const char **plugins, int *count);

int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create at least one non-NULL string
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the plugins array
    const char *plugins[2];

    // Create a null-terminated string from the data
    char *plugin1 = (char *)malloc(size + 1);
    if (plugin1 == NULL) {
        return 0;
    }
    memcpy(plugin1, data, size);
    plugin1[size] = '\0';

    // Assign the string to the plugins array
    plugins[0] = plugin1;
    plugins[1] = NULL; // NULL-terminate the array

    // Initialize the count variable
    int count = 0;

    // Call the function-under-test
    hfile_list_plugins(plugins, &count);

    // Free allocated memory
    free(plugin1);

    return 0;
}