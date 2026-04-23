#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "/src/htslib/htslib/sam.h" // Correct path to the HTSlib SAM library

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Check if the size is sufficient for splitting into parameters
    if (size < 4) {
        return 0;
    }

    // Initialize bam1_t structure
    bam1_t *bam_record = bam_init1();
    if (bam_record == NULL) {
        return 0;
    }

    // Extract parts of the data for the parameters
    const char *tag = (const char *)data; // Using first few bytes as tag
    int tag_len = 2; // BAM tags are typically 2 characters long

    // Ensure null-termination for the tag
    char tag_buffer[3];
    memcpy(tag_buffer, tag, tag_len);
    tag_buffer[2] = '\0';

    // Use a portion of the data as the length of the string
    int str_length = (int)data[2];

    // Use the remaining data as the string, ensuring null-termination
    const char *str_data = (const char *)(data + 3);
    size_t str_data_length = size - 3;

    // Allocate memory for the string and ensure null-termination
    char *str_buffer = (char *)malloc(str_data_length + 1);
    if (str_buffer == NULL) {
        bam_destroy1(bam_record);
        return 0;
    }
    memcpy(str_buffer, str_data, str_data_length);
    str_buffer[str_data_length] = '\0';

    // Call the function-under-test
    int result = bam_aux_update_str(bam_record, tag_buffer, str_length, str_buffer);

    // Clean up
    free(str_buffer);
    bam_destroy1(bam_record);

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

    LLVMFuzzerTestOneInput_86(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
