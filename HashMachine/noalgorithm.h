#ifndef NOALGORITHM_H
#define NOALGORITHM_H

#include "ihashstandard.h"


/**
 * Třída která naznačuje využití pro rozhraní IHashStandard.
 * Tato třída představuje poouze prázdný výstup.
 *
 * @author Radek VAIS
 * @version 1.0.0
 * @date 3.5.2016
 */
class NoAlgorithm : public IHashStandard
{
public:
    NoAlgorithm();
    virtual std::string *hash(IFile *file);
};

#endif // NOALGORITHM_H
