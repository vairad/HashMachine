#include "noalgorithm.h"


NoAlgorithm::NoAlgorithm(){
    //do nothing
}

/**
 * Ukázková implementace metody hash
 * @param file
 * @return zpráva o výsledku algoritmu
 */
std::string *NoAlgorithm::hash(IFile *file){
    if(file->isOk()){
        return new std::string("File is ok but no hash algorithm choosed");
    }else{
        return new std::string("No algorithm choosed only type sha512 is implemented.");
    }
}
