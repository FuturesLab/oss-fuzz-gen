#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/sam.h"  // Assuming the header file for sam_hdr_t is in htslib/sam.h

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Ensure that the input data is large enough to create non-NULL strings
    if (size < 4) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Divide the input data into three parts for the strings
    size_t len1 = size / 4;
    size_t len2 = size / 4;
    size_t len3 = size / 4;

    char *str1 = (char *)malloc(len1 + 1);
    char *str2 = (char *)malloc(len2 + 1);
    char *str3 = (char *)malloc(len3 + 1);

    if (str1 == NULL || str2 == NULL || str3 == NULL) {
        free(str1);
        free(str2);
        free(str3);
        sam_hdr_destroy(hdr);
        return 0;
    }

    memcpy(str1, data, len1);
    str1[len1] = '\0';

    memcpy(str2, data + len1, len2);
    str2[len2] = '\0';

    memcpy(str3, data + len1 + len2, len3);
    str3[len3] = '\0';

    // Call the function-under-test
    sam_hdr_remove_line_id(hdr, str1, str2, str3);

    // Clean up

    // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from sam_hdr_remove_line_id to sam_hdr_change_HD using the plateau pool
    const char vounxiki[1024] = "afmqg";
    // Ensure dataflow is valid (i.e., non-null)
    if (!hdr) {
    	return 0;
    }
    int ret_sam_hdr_change_HD_acdfa = sam_hdr_change_HD(hdr, vounxiki, NULL);
    if (ret_sam_hdr_change_HD_acdfa < 0){
    	return 0;
    }
    // End mutation: Producer.SPLICE_MUTATOR
    
    free(str1);
    free(str2);
    free(str3);
    sam_hdr_destroy(hdr);

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

    LLVMFuzzerTestOneInput_36(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
