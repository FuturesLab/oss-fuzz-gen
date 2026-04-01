// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsWriteTypeBase at cmsplugin.c:434:20 in lcms2_plugin.h
// _cmsWriteUInt64Number at cmsplugin.c:324:20 in lcms2_plugin.h
// _cmsAdjustEndianess32 at cmsplugin.c:58:28 in lcms2_plugin.h
// _cmsWriteUInt32Number at cmsplugin.c:295:20 in lcms2_plugin.h
// _cmsReadUInt32Number at cmsplugin.c:156:20 in lcms2_plugin.h
// _cmsWriteUInt16Number at cmsplugin.c:268:20 in lcms2_plugin.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2_plugin.h"

static cmsIOHANDLER* create_iohandler() {
    cmsIOHANDLER* iohandler = (cmsIOHANDLER*)malloc(sizeof(cmsIOHANDLER));
    if (iohandler) {
        iohandler->stream = fopen("./dummy_file", "wb+");
        iohandler->ContextID = NULL;
        iohandler->UsedSpace = 0;
        iohandler->ReportedSize = 0;
        memset(iohandler->PhysicalFile, 0, cmsMAX_PATH);

        iohandler->Read = NULL;  // Implement as needed
        iohandler->Seek = NULL;  // Implement as needed
        iohandler->Close = NULL; // Implement as needed
        iohandler->Tell = NULL;  // Implement as needed
        iohandler->Write = NULL; // Implement as needed
    }
    return iohandler;
}

static void destroy_iohandler(cmsIOHANDLER* iohandler) {
    if (iohandler) {
        if (iohandler->stream) {
            fclose((FILE*)iohandler->stream);
        }
        free(iohandler);
    }
}

int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt64Number) + 2 * sizeof(cmsUInt32Number) + sizeof(cmsUInt16Number)) {
        return 0;
    }

    cmsIOHANDLER* iohandler = create_iohandler();
    if (!iohandler || !iohandler->stream) {
        destroy_iohandler(iohandler);
        return 0;
    }

    cmsTagTypeSignature sig = (cmsTagTypeSignature)(*(uint32_t*)Data);
    cmsUInt64Number uint64 = *(cmsUInt64Number*)(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number uint32 = *(cmsUInt32Number*)(Data + sizeof(cmsUInt64Number) + sizeof(cmsUInt32Number));
    cmsUInt16Number uint16 = *(cmsUInt16Number*)(Data + sizeof(cmsUInt64Number) + 2 * sizeof(cmsUInt32Number));

    // Check if iohandler->Write is implemented before using it
    if (iohandler->Write) {
        // _cmsWriteTypeBase
        _cmsWriteTypeBase(iohandler, sig);

        // _cmsWriteUInt64Number
        _cmsWriteUInt64Number(iohandler, &uint64);

        // _cmsAdjustEndianess32
        _cmsAdjustEndianess32(uint32);

        // _cmsWriteUInt32Number
        _cmsWriteUInt32Number(iohandler, uint32);

        // _cmsReadUInt32Number
        cmsUInt32Number read_uint32;
        _cmsReadUInt32Number(iohandler, &read_uint32);

        // _cmsWriteUInt16Number
        _cmsWriteUInt16Number(iohandler, uint16);
    }

    destroy_iohandler(iohandler);
    return 0;
}