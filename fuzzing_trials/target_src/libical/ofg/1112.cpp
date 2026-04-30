#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

extern "C" {
    #include <libical/ical.h>  // Correct path for ical.h
}

extern "C" int LLVMFuzzerTestOneInput_1112(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for icalproperty
    icalproperty *prop = icalproperty_new(ICAL_REPLYURL_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *replyurl = (char *)malloc(size + 1);
    if (replyurl == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(replyurl, data, size);
    replyurl[size] = '\0';

    // Check if the replyurl is a valid URL format (basic check)
    if (strstr(replyurl, "http://") == replyurl || strstr(replyurl, "https://") == replyurl) {
        // Call the function-under-test
        icalproperty_set_replyurl(prop, replyurl);
    }

    // Clean up
    free(replyurl);
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_1112(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
