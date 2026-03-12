#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "lcms2.h"
#include "/src/lcms/include/lcms2_plugin.h"

static cmsUInt32Number DummyRead(struct _cms_io_handler* iohandler, void *Buffer, cmsUInt32Number size, cmsUInt32Number count) {
    // Dummy read function
    return size * count;
}

static cmsBool DummySeek(struct _cms_io_handler* iohandler, cmsUInt32Number offset) {
    // Dummy seek function
    return TRUE;
}

static cmsBool DummyClose(struct _cms_io_handler* iohandler) {
    // Dummy close function
    return TRUE;
}

static cmsUInt32Number DummyTell(struct _cms_io_handler* iohandler) {
    // Dummy tell function
    return 0;
}

static cmsBool DummyWrite(struct _cms_io_handler* iohandler, cmsUInt32Number size, const void* Buffer) {
    // Dummy write function
    return TRUE;
}

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsTagTypeSignature) + sizeof(cmsFloat32Number)) {
        return 0;
    }

    cmsIOHANDLER iohandler;
    memset(&iohandler, 0, sizeof(iohandler));
    iohandler.Read = DummyRead;
    iohandler.Seek = DummySeek;
    iohandler.Close = DummyClose;
    iohandler.Tell = DummyTell;
    iohandler.Write = DummyWrite;

    cmsTagTypeSignature sig;
    memcpy(&sig, Data, sizeof(cmsTagTypeSignature));
    Data += sizeof(cmsTagTypeSignature);
    Size -= sizeof(cmsTagTypeSignature);

    cmsFloat32Number number;
    memcpy(&number, Data, sizeof(cmsFloat32Number));
    Data += sizeof(cmsFloat32Number);
    Size -= sizeof(cmsFloat32Number);

    // Test _cmsWriteTypeBase
    _cmsWriteTypeBase(&iohandler, sig);

    // Test _cmsReadFloat32Number
    _cmsReadFloat32Number(&iohandler, &number);

    // Test _cmsWriteFloat32Number
    _cmsWriteFloat32Number(&iohandler, number);

    // Test cmsCloseIOhandler
    cmsCloseIOhandler(&iohandler);

    // Test _cmsReadAlignment
    _cmsReadAlignment(&iohandler);

    // Test _cmsWriteAlignment
    _cmsWriteAlignment(&iohandler);

    return 0;
}