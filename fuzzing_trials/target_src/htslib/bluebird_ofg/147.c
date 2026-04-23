#include <sys/stat.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t l, m;
    char *s;
} kstring_t;

char * haddextension(kstring_t *str, const char *ext, int flag, const char *sep);

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Ensure there's enough data for the inputs
    }

    // Initialize kstring_t
    kstring_t kstr;
    kstr.l = size / 2;
    kstr.m = size;
    kstr.s = (char *)malloc(kstr.m + 1);
    memcpy(kstr.s, data, kstr.l);
    kstr.s[kstr.l] = '\0';

    // Extract ext from the input data
    const char *ext = (const char *)(data + kstr.l);
    int ext_len = (size - kstr.l) / 2;
    char *ext_str = (char *)malloc(ext_len + 1);
    memcpy(ext_str, ext, ext_len);
    ext_str[ext_len] = '\0';

    // Extract sep from the input data
    const char *sep = (const char *)(data + kstr.l + ext_len);
    int sep_len = size - kstr.l - ext_len;
    char *sep_str = (char *)malloc(sep_len + 1);
    memcpy(sep_str, sep, sep_len);
    sep_str[sep_len] = '\0';

    // Use a fixed flag value for simplicity
    int flag = 1;

    // Call the function-under-test
    char *result = haddextension(&kstr, ext_str, flag, sep_str);

    // Free allocated memory
    free(kstr.s);
    free(ext_str);
    free(sep_str);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_147(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
