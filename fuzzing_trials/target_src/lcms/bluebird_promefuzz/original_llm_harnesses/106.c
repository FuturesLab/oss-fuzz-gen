// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenProfileFromMem at cmsio0.c:1296:23 in lcms2.h
// cmsSetHeaderProfileID at cmsio0.c:1057:16 in lcms2.h
// cmsGetHeaderProfileID at cmsio0.c:1051:16 in lcms2.h
// cmsGetTagCount at cmsio0.c:581:26 in lcms2.h
// cmsGetTagSignature at cmsio0.c:590:27 in lcms2.h
// cmsReadRawTag at cmsio0.c:1913:27 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define DUMMY_FILE "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0; // Not enough data for a Profile ID

    cmsHPROFILE hProfile = cmsOpenProfileFromMem(Data, (cmsUInt32Number)Size);
    if (!hProfile) return 0;

    cmsUInt8Number ProfileID[16];
    memcpy(ProfileID, Data, 16);

    cmsSetHeaderProfileID(hProfile, ProfileID);

    cmsUInt8Number RetrievedProfileID[16];
    cmsGetHeaderProfileID(hProfile, RetrievedProfileID);

    cmsInt32Number tagCount = cmsGetTagCount(hProfile);
    for (cmsUInt32Number i = 0; i < (cmsUInt32Number)tagCount; i++) {
        cmsTagSignature sig = cmsGetTagSignature(hProfile, i);
        if (sig) {
            cmsUInt32Number bufferSize = 1024; // Arbitrary buffer size
            void *buffer = malloc(bufferSize);
            if (buffer) {
                cmsUInt32Number bytesRead = cmsReadRawTag(hProfile, sig, buffer, bufferSize);
                (void)bytesRead; // Suppress unused variable warning
                free(buffer);
            }
        }
    }

    cmsCloseProfile(hProfile);

    return 0;
}