#ifndef LOCALSTDIN_H
#define LOCALSTDIN_H

#include <iostream>
#include <string>

#include "ifile.h"

/**
 * Třída která implementuje IFile a jako vstup dat používá std::cin.
 * Implementace přečte znaky do zadání enter.
 *
 * @author Radek VAIS
 * @version 1.0.0
 * @date 4.5.2016
 */
class LocalStdIn : public IFile
{
    const char *name = "LocalStdIn:"; // log name
    std::string msg; //place to store message
    uint64_t i = 0; // iterator

public:
    LocalStdIn(); //working constructor !!

    virtual uint64_t getBytesCount();
    virtual uint8_t getByte();
    virtual bool isOk();
};

#endif // LOCALSTDIN_H
