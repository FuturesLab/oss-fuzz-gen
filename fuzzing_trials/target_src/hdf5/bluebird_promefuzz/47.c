// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen_async at H5F.c:848:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Freopen_async at H5F.c:1477:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate_async at H5F.c:673:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
// H5Dopen_async at H5D.c:418:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Dpublic.h>
#include <H5Fpublic.h>

static void fuzz_H5Fopen_async(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    const char *filename = "./dummy_file";
    unsigned flags = Data[0];
    hid_t access_plist = 0; // Default access property list
    hid_t es_id = 0; // Default event set ID

    hid_t file_id = H5Fopen_async(filename, flags, access_plist, es_id);
    if (file_id >= 0) {
        H5Fclose(file_id);
    }
}

static void fuzz_H5Freopen_async(hid_t file_id, const uint8_t *Data, size_t Size) {
    hid_t es_id = 0; // Default event set ID

    hid_t new_file_id = H5Freopen_async(file_id, es_id);
    if (new_file_id >= 0) {
        H5Fclose(new_file_id);
    }
}

static void fuzz_H5Fcreate_async(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    const char *filename = "./dummy_file";
    unsigned flags = Data[0];
    hid_t fcpl_id = 0; // Default creation property list
    hid_t fapl_id = 0; // Default access property list
    hid_t es_id = 0; // Default event set ID

    hid_t file_id = H5Fcreate_async(filename, flags, fcpl_id, fapl_id, es_id);
    if (file_id >= 0) {
        fuzz_H5Freopen_async(file_id, Data, Size);
        H5Fclose(file_id);
    }
}

static void fuzz_H5Dread_async(hid_t dset_id, const uint8_t *Data, size_t Size) {
    hid_t mem_type_id = 0; // Default memory type
    hid_t mem_space_id = 0; // Default memory space
    hid_t file_space_id = 0; // Default file space
    hid_t dxpl_id = 0; // Default data transfer property list
    hid_t es_id = 0; // Default event set ID
    void *buf = NULL;

    herr_t status = H5Dread_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
    if (status < 0) {
        fprintf(stderr, "H5Dread_async failed\n");
    }
}

static void fuzz_H5Dopen_async(hid_t loc_id, const uint8_t *Data, size_t Size) {
    const char *name = "dataset";
    hid_t dapl_id = 0; // Default dataset access property list
    hid_t es_id = 0; // Default event set ID

    hid_t dset_id = H5Dopen_async(loc_id, name, dapl_id, es_id);
    if (dset_id >= 0) {
        fuzz_H5Dread_async(dset_id, Data, Size);
        H5Dclose(dset_id);
    }
}

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    fuzz_H5Fcreate_async(Data, Size);
    return 0;
}