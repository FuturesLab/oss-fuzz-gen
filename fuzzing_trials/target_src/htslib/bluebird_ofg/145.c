#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"
#include "htslib/sam.h"  // Include the header where hts_base_mod_state is defined

extern int bam_mods_queryi(hts_base_mod_state *state, int param1, int *param2, int *param3, char *param4);

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Ensure there is enough data to initialize parameters
    if (size < sizeof(int) * 3) {
        return 0;
    }

    // Initialize hts_base_mod_state
    hts_base_mod_state *state = hts_base_mod_state_alloc();
    if (state == NULL) {
        return 0;
    }

    // Extract integers from the data
    int param1 = *(int *)(data);
    int param2_value = *(int *)(data + sizeof(int));
    int param3_value = *(int *)(data + 2 * sizeof(int));

    // Allocate memory for param2 and param3
    int *param2 = (int *)malloc(sizeof(int));
    int *param3 = (int *)malloc(sizeof(int));
    if (param2 == NULL || param3 == NULL) {
        hts_base_mod_state_free(state);
        free(param2);
        free(param3);
        return 0;
    }

    // Copy extracted values to param2 and param3
    *param2 = param2_value;
    *param3 = param3_value;

    // Allocate memory for param4 string
    size_t param4_size = size - 3 * sizeof(int);
    char *param4 = (char *)malloc(param4_size + 1);  // +1 for null-terminator
    if (param4 == NULL) {
        hts_base_mod_state_free(state);
        free(param2);
        free(param3);
        return 0;
    }

    // Copy remaining data into param4 and null-terminate it
    memcpy(param4, data + 3 * sizeof(int), param4_size);
    param4[param4_size] = '\0';

    // Call the function-under-test
    int result = bam_mods_queryi(state, param1, param2, param3, param4);

    // Clean up
    hts_base_mod_state_free(state);
    free(param2);
    free(param3);
    free(param4);

    return 0;
}