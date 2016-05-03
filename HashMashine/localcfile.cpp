#include "localcfile.h"

/**
 * Konstruktor otevře soubor a nastaví základní proměnné.
 *
 * @param path cesta k souboru
 */
LocalCFile::LocalCFile(char *path){
   file = fopen(path,"r");
   if(file != NULL){
       std::cerr << name << " file " << path << " was opened" << std::endl;
   }else{
       std::cerr << name << " file " << path << " was NOT opened" << std::endl;
   }
   fseek(file, 0, SEEK_END);
   byteCount = ftell(file);
   fseek(file, 0, SEEK_SET);
   std::cerr << name << " file " << path << " is " << byteCount << " long " << std::endl;
}

/**
 * Vrátí počet bytů v souboru
 *
 * @return 64bit number
 */
uint64_t LocalCFile::getBytesCount(){
    return byteCount;
}

/**
 * Přečte jeden další byte ze souboru.
 *
 * @return 8bit number
 */
uint8_t LocalCFile::getByte(){
    uint8_t tmp;
    fread(&tmp, 1, 1, file);
    return tmp;
}

/**
 * Kontroluje, zda je lze ze souboru číst.
 *
 * @return zda lze soubor číst
 */
bool LocalCFile::isOk(){
    if(file != NULL){
        return true;
    }
    return false;
}
