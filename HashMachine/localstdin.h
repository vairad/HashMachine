#ifndef LOCALSTDIN_H
#define LOCALSTDIN_H

#include <iostream>
#include <string>

#include "ifile.h"

class LocalStdIn : public IFile
{
    std::string msg;
    int i = 0;

public:
    LocalStdIn();

    /**
     * vrátí počet bytů souboru
     * @return vrátí počet bytů souboru
     */
    virtual uint64_t getBytesCount();

    /**
     * Vrátí následující byte souboru.
     * @return následující byte souboru
     */
    virtual uint8_t getByte();

    /**
     * Zkontroluje, zda lze číst ze souboru.
     * @return zda lze ze souboru číst
     */
    virtual bool isOk();
};

#endif // LOCALSTDIN_H
