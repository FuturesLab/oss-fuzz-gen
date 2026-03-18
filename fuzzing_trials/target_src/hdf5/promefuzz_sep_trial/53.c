// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Aopen_async at H5A.c:556:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dcreate_async at H5D.c:206:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Aopen_by_name_async at H5A.c:683:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dget_space_async at H5D.c:625:1 in H5Dpublic.h
// H5Acreate_async at H5A.c:247:1 in H5Apublic.h
// H5Aclose at H5A.c:2194:1 in H5Apublic.h
// H5Dread_async at H5D.c:1067:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Dpublic.h"
#include "H5Apublic.h"

static void fuzz_H5Aopen_by_name_async(const uint8_t *Data, size_t Size) {
    if (Size < 4) return;

    hid_t loc_id = (hid_t)Data[0];
    hid_t aapl_id = (hid_t)Data[1];
    hid_t lapl_id = (hid_t)Data[2];
    hid_t es_id = (hid_t)Data[3];

    size_t obj_name_len = (Size > 5) ? Data[4] % (Size - 5) : 0;
    size_t attr_name_len = (Size > 6 + obj_name_len) ? Data[5 + obj_name_len] % (Size - 6 - obj_name_len) : 0;

    char *obj_name = (char *)malloc(obj_name_len + 1);
    char *attr_name = (char *)malloc(attr_name_len + 1);

    if (obj_name && attr_name) {
        memcpy(obj_name, Data + 5, obj_name_len);
        obj_name[obj_name_len] = '\0';
        memcpy(attr_name, Data + 6 + obj_name_len, attr_name_len);
        attr_name[attr_name_len] = '\0';

        hid_t attr_id = H5Aopen_by_name_async(loc_id, obj_name, attr_name, aapl_id, lapl_id, es_id);
        if (attr_id >= 0) {
            H5Aclose(attr_id);
        }

        free(obj_name);
        free(attr_name);
    }
}

static void fuzz_H5Dget_space_async(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    hid_t dset_id = (hid_t)Data[0];
    hid_t es_id = (hid_t)Data[1];

    hid_t space_id = H5Dget_space_async(dset_id, es_id);
    if (space_id >= 0) {
        H5Sclose(space_id);
    }
}

static void fuzz_H5Acreate_async(const uint8_t *Data, size_t Size) {
    if (Size < 6) return;

    hid_t loc_id = (hid_t)Data[0];
    hid_t type_id = (hid_t)Data[1];
    hid_t space_id = (hid_t)Data[2];
    hid_t acpl_id = (hid_t)Data[3];
    hid_t aapl_id = (hid_t)Data[4];
    hid_t es_id = (hid_t)Data[5];

    size_t attr_name_len = (Size > 7) ? Data[6] % (Size - 7) : 0;

    char *attr_name = (char *)malloc(attr_name_len + 1);

    if (attr_name) {
        memcpy(attr_name, Data + 7, attr_name_len);
        attr_name[attr_name_len] = '\0';

        hid_t attr_id = H5Acreate_async(loc_id, attr_name, type_id, space_id, acpl_id, aapl_id, es_id);
        if (attr_id >= 0) {
            H5Aclose(attr_id);
        }

        free(attr_name);
    }
}

static void fuzz_H5Dread_async(const uint8_t *Data, size_t Size) {
    if (Size < 6) return;

    hid_t dset_id = (hid_t)Data[0];
    hid_t mem_type_id = (hid_t)Data[1];
    hid_t mem_space_id = (hid_t)Data[2];
    hid_t file_space_id = (hid_t)Data[3];
    hid_t dxpl_id = (hid_t)Data[4];
    hid_t es_id = (hid_t)Data[5];

    void *buf = malloc(1024); // Arbitrary buffer size for fuzzing

    if (buf) {
        herr_t status = H5Dread_async(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf, es_id);
        free(buf);
    }
}

static void fuzz_H5Aopen_async(const uint8_t *Data, size_t Size) {
    if (Size < 3) return;

    hid_t obj_id = (hid_t)Data[0];
    hid_t aapl_id = (hid_t)Data[1];
    hid_t es_id = (hid_t)Data[2];

    size_t attr_name_len = (Size > 4) ? Data[3] % (Size - 4) : 0;

    char *attr_name = (char *)malloc(attr_name_len + 1);

    if (attr_name) {
        memcpy(attr_name, Data + 4, attr_name_len);
        attr_name[attr_name_len] = '\0';

        hid_t attr_id = H5Aopen_async(obj_id, attr_name, aapl_id, es_id);
        if (attr_id >= 0) {
            H5Aclose(attr_id);
        }

        free(attr_name);
    }
}

static void fuzz_H5Dcreate_async(const uint8_t *Data, size_t Size) {
    if (Size < 7) return;

    hid_t loc_id = (hid_t)Data[0];
    hid_t type_id = (hid_t)Data[1];
    hid_t space_id = (hid_t)Data[2];
    hid_t lcpl_id = (hid_t)Data[3];
    hid_t dcpl_id = (hid_t)Data[4];
    hid_t dapl_id = (hid_t)Data[5];
    hid_t es_id = (hid_t)Data[6];

    size_t name_len = (Size > 8) ? Data[7] % (Size - 8) : 0;

    char *name = (char *)malloc(name_len + 1);

    if (name) {
        memcpy(name, Data + 8, name_len);
        name[name_len] = '\0';

        hid_t dset_id = H5Dcreate_async(loc_id, name, type_id, space_id, lcpl_id, dcpl_id, dapl_id, es_id);
        if (dset_id >= 0) {
            H5Dclose(dset_id);
        }

        free(name);
    }
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    fuzz_H5Aopen_by_name_async(Data, Size);
    fuzz_H5Dget_space_async(Data, Size);
    fuzz_H5Acreate_async(Data, Size);
    fuzz_H5Dread_async(Data, Size);
    fuzz_H5Aopen_async(Data, Size);
    fuzz_H5Dcreate_async(Data, Size);
    return 0;
}