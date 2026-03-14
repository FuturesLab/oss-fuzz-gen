#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"
#include "/src/lcms/include/lcms2_plugin.h"

static cmsIOHANDLER* CreateDummyIOHandler() {
    cmsIOHANDLER* io = (cmsIOHANDLER*)malloc(sizeof(cmsIOHANDLER));
    if (io) {
        memset(io, 0, sizeof(cmsIOHANDLER));
        io->stream = fopen("./dummy_file", "wb+");
        if (!io->stream) {
            free(io);
            return NULL;
        }
    }
    return io;
}

static void DestroyDummyIOHandler(cmsIOHANDLER* io) {
    if (io) {
        if (io->stream) {
            fclose((FILE*)io->stream);
        }
        free(io);
    }
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ) * 3 + sizeof(cmsCIELab) + sizeof(cmsCIExyY) + sizeof(cmsUInt16Number) * 3) {
        return 0;
    }

    // cmsAdaptToIlluminant
    cmsCIEXYZ Result, SourceWhitePt, Illuminant, Value;
    memcpy(&SourceWhitePt, Data, sizeof(cmsCIEXYZ));
    memcpy(&Illuminant, Data + sizeof(cmsCIEXYZ), sizeof(cmsCIEXYZ));
    memcpy(&Value, Data + 2 * sizeof(cmsCIEXYZ), sizeof(cmsCIEXYZ));
    cmsAdaptToIlluminant(&Result, &SourceWhitePt, &Illuminant, &Value);

    // cmsLab2XYZ
    cmsCIEXYZ xyz;
    cmsCIELab Lab;
    memcpy(&Lab, Data + 3 * sizeof(cmsCIEXYZ), sizeof(cmsCIELab));
    cmsLab2XYZ(&SourceWhitePt, &xyz, &Lab);

    // cmsFloat2XYZEncoded
    cmsUInt16Number XYZ[3];
    cmsFloat2XYZEncoded(XYZ, &xyz);

    // cmsxyY2XYZ
    cmsCIExyY Source;
    memcpy(&Source, Data + 3 * sizeof(cmsCIEXYZ) + sizeof(cmsCIELab), sizeof(cmsCIExyY));
    cmsxyY2XYZ(&Result, &Source);

    // _cmsReadXYZNumber
    cmsIOHANDLER* io = CreateDummyIOHandler();
    if (io && io->stream) {
        fwrite(Data, 1, Size, (FILE*)io->stream);
        rewind((FILE*)io->stream);
        if (io->Read && _cmsReadXYZNumber(io, &Result)) {
            // Handle successful read if necessary
        }
        DestroyDummyIOHandler(io);
    } else {
        DestroyDummyIOHandler(io);
    }

    // cmsXYZEncoded2Float
    cmsXYZEncoded2Float(&xyz, XYZ);

    return 0;
}