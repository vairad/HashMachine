#include "noalgorithm.h"

NoAlgorithm::NoAlgorithm(){
}

std::string *NoAlgorithm::hash(IFile *file){
    return new std::string("No algorithm choosed");
}
