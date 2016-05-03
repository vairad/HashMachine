#ifndef NOALGORITHM_H
#define NOALGORITHM_H

#include "ihashstandard.h"

class NoAlgorithm : public IHashStandard
{
public:
    NoAlgorithm();
    virtual std::string *hash(IFile *file);
};

#endif // NOALGORITHM_H
