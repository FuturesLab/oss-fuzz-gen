// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:680:23 in lcms2.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsGetPostScriptColorResource at cmsps2.c:1525:27 in lcms2.h
// cmsSaveProfileToIOhandler at cmsio0.c:1447:27 in lcms2.h
// cmsIsCLUT at cmsio1.c:830:20 in lcms2.h
// cmsGetEncodedICCversion at cmsio0.c:1106:27 in lcms2.h
// cmsGetHeaderFlags at cmsio0.c:997:27 in lcms2.h
// cmsGetHeaderModel at cmsio0.c:1027:27 in lcms2.h
// cmsOpenIOhandlerFromFile at cmsio0.c:378:25 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static cmsIOHANDLER* CreateDummyIOHandler() {
    cmsIOHANDLER* io = cmsOpenIOhandlerFromFile(NULL, "./dummy_file", "w");
    return io;
}

static cmsHPROFILE CreateDummyProfile() {
    return cmsCreate_sRGBProfile(); // Create a dummy sRGB profile
}

static void Cleanup(cmsIOHANDLER* io, cmsHPROFILE hProfile) {
    if (io) cmsCloseIOhandler(io);
    if (hProfile) cmsCloseProfile(hProfile);
}

int LLVMFuzzerTestOneInput_154(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = NULL;
    cmsHPROFILE hProfile = CreateDummyProfile();
    cmsIOHANDLER* io = CreateDummyIOHandler();
    if (!hProfile || !io) {
        Cleanup(io, hProfile);
        return 0;
    }

    cmsUInt32Number intent = Data[0] % 4; // Random intent
    cmsUInt32Number flags = 0; // Default flags
    cmsPSResourceType resourceType = (cmsPSResourceType)(Data[0] % 2); // CSA or CRD

    cmsGetPostScriptColorResource(context, resourceType, hProfile, intent, flags, io);
    cmsSaveProfileToIOhandler(hProfile, io);
    cmsIsCLUT(hProfile, intent, Data[0] % 3);
    cmsGetEncodedICCversion(hProfile);
    cmsGetHeaderFlags(hProfile);
    cmsGetHeaderModel(hProfile);

    Cleanup(io, hProfile);
    return 0;
}