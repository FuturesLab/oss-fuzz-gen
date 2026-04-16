#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for testing
    if (size < sizeof(hid_t) + 1) {
        return 0;
    }

    // Extract a valid hid_t from the input data
    hid_t file_id = *((hid_t *)data);

    // Allocate a buffer for the file name
    size_t name_size = size - sizeof(hid_t);
    char *name_buffer = (char *)malloc(name_size);
    if (name_buffer == NULL) {
        return 0;
    }

    // Call the function-under-test
    ssize_t result = H5Fget_name(file_id, name_buffer, name_size);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fget_name to H5Dread_multi
    hid_t ret_H5Fget_create_plist_pylck = H5Fget_create_plist(0);
    hid_t ret_H5Dget_access_plist_mhgnj = H5Dget_access_plist(0);
    hid_t ret_H5Aget_create_plist_itdak = H5Aget_create_plist(0);
    hid_t skvlujyx;
    memset(&skvlujyx, 0, sizeof(skvlujyx));
    hid_t kwosrufg;
    memset(&kwosrufg, 0, sizeof(kwosrufg));
    herr_t ret_H5Dread_multi_qoued = H5Dread_multi(H5F_FAMILY_DEFAULT, &skvlujyx, &ret_H5Fget_create_plist_pylck, &kwosrufg, &ret_H5Dget_access_plist_mhgnj, ret_H5Aget_create_plist_itdak, (void **)&name_buffer);
    // End mutation: Producer.APPEND_MUTATOR
    
    free(name_buffer);

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

    LLVMFuzzerTestOneInput_108(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
