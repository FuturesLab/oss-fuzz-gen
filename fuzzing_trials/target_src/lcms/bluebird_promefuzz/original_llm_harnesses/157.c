// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenProfileFromMem at cmsio0.c:1296:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsGetPostScriptColorResource at cmsps2.c:1525:27 in lcms2.h
// cmsSaveProfileToIOhandler at cmsio0.c:1447:27 in lcms2.h
// cmsIsCLUT at cmsio1.c:830:20 in lcms2.h
// cmsGetEncodedICCversion at cmsio0.c:1106:27 in lcms2.h
// cmsGetHeaderFlags at cmsio0.c:997:27 in lcms2.h
// cmsGetHeaderModel at cmsio0.c:1027:27 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>

#define DUMMY_FILE "./dummy_file"

typedef struct {
    void* stream;
    cmsContext ContextID;
    cmsUInt32Number UsedSpace;
    cmsUInt32Number ReportedSize;
    char PhysicalFile[cmsMAX_PATH];
    cmsUInt32Number (* Read)(struct _cms_io_handler* iohandler, void *Buffer, cmsUInt32Number size, cmsUInt32Number count);
    cmsBool (* Seek)(struct _cms_io_handler* iohandler, cmsUInt32Number offset);
    cmsBool (* Close)(struct _cms_io_handler* iohandler);
    cmsUInt32Number (* Tell)(struct _cms_io_handler* iohandler);
    cmsBool (* Write)(struct _cms_io_handler* iohandler, cmsUInt32Number size, const void* Buffer);
} DummyIOHANDLER;

static DummyIOHANDLER* CreateDummyIOHandler() {
    DummyIOHANDLER* io = (DummyIOHANDLER*)malloc(sizeof(DummyIOHANDLER));
    if (!io) return NULL;

    io->stream = fopen(DUMMY_FILE, "wb+");
    if (!io->stream) {
        free(io);
        return NULL;
    }

    io->ContextID = NULL;
    io->UsedSpace = 0;
    io->ReportedSize = 0;
    snprintf(io->PhysicalFile, sizeof(io->PhysicalFile), "%s", DUMMY_FILE);

    io->Read = NULL;
    io->Seek = NULL;
    io->Close = NULL;
    io->Tell = NULL;
    io->Write = NULL;

    return io;
}

static void DestroyDummyIOHandler(DummyIOHANDLER* io) {
    if (io) {
        if (io->stream) fclose((FILE*)io->stream);
        free(io);
    }
}

int LLVMFuzzerTestOneInput_157(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 3) return 0;

    cmsContext context = NULL;
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(Data, Size);
    if (!hProfile) return 0;

    cmsUInt32Number Intent = *(cmsUInt32Number*)(Data + 1);
    cmsUInt32Number dwFlags = *(cmsUInt32Number*)(Data + 2);

    DummyIOHANDLER* io = CreateDummyIOHandler();
    if (!io) {
        cmsCloseProfile(hProfile);
        return 0;
    }

    cmsPSResourceType Type = (cmsPSResourceType)(Data[0] % 2); // Simplified for fuzzing

    // Fuzzing cmsGetPostScriptColorResource
    cmsGetPostScriptColorResource(context, Type, hProfile, Intent, dwFlags, (cmsIOHANDLER*)io);

    // Fuzzing cmsSaveProfileToIOhandler
    cmsSaveProfileToIOhandler(hProfile, (cmsIOHANDLER*)io);

    // Fuzzing cmsIsCLUT
    cmsIsCLUT(hProfile, Intent, dwFlags);

    // Fuzzing cmsGetEncodedICCversion
    cmsGetEncodedICCversion(hProfile);

    // Fuzzing cmsGetHeaderFlags
    cmsGetHeaderFlags(hProfile);

    // Fuzzing cmsGetHeaderModel
    cmsGetHeaderModel(hProfile);

    DestroyDummyIOHandler(io);
    cmsCloseProfile(hProfile);
    return 0;
}