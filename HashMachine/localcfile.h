#ifndef LOCALCFILE_H
#define LOCALCFILE_H

#include <cstdio>
#include <iostream>

#include "ifile.h"

/**
 * Třída která k načtení souboru využívá standardní c implementaci stdio.h.
 * Implementuje interface IFile pro definici služeb od souboru.
 *
 * @author Radek VAIS
 * @version 1.0.0
 * @date 3.5.2016
 */
class LocalCFile : public IFile
{
    const char *name = "LocalCFile:";
    FILE *file;
    uint64_t byteCount;

public:
    LocalCFile(char* path);
    uint64_t getBytesCount();
    uint8_t getByte();
    bool isOk();
};

#endif // LOCALCFILE_H
