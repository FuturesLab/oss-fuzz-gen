#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_298(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to prevent buffer overflow issues
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Handle allocation failure gracefully
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize an icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);

    if (component != NULL) {
        // Call the function-under-test
        bool result = icalcomponent_check_restrictions(component);

        // Clean up the created icalcomponent

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_check_restrictions to icalproperty_set_parent
        const char miwgjryt[1024] = "fkgwg";
        icalproperty* ret_icalproperty_new_replyurl_czkkq = icalproperty_new_replyurl(miwgjryt);
        if (ret_icalproperty_new_replyurl_czkkq == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_icalproperty_new_replyurl_czkkq) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!component) {
        	return 0;
        }
        icalproperty_set_parent(ret_icalproperty_new_replyurl_czkkq, component);
        // End mutation: Producer.APPEND_MUTATOR
        
        icalcomponent_free(component);
    }

    // Free the allocated memory for null-terminated data
    free(null_terminated_data);

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

    LLVMFuzzerTestOneInput_298(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
