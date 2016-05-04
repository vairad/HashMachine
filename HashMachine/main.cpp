#include <iostream>
#include <fstream>
#include <cstring>

#include "ifile.h"
#include "ihashstandard.h"

#include "localcfile.h"
#include "localstdin.h"
#include "sha512.h"
#include "noalgorithm.h"


/** promenne ovlivnujici stav spusteni vyplnene vychozimi hodnotami */
bool printHelpBool = false;
char *filename = NULL;
bool fileIsSet = false;
char *hashAlgorithm = "sha512";


/**
 * Projdi argumenty a nastav hodnoty stavu programu
 * @param argc
 * @param argv
 */
void readArguments(int argc, char *argv[]){
    //zpracovani prepinacu
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'h': //help musi byt prvni ... uchova vychozi nastaveni stavu spusteni
                case 'H':
                        printHelpBool = true;
                        break;
                case 'f':
                case 'F':
                        filename = (char *)malloc(strlen(&argv[i][2]));
                        strcpy(filename, &argv[i][2]);
                        fileIsSet = true;
                        break;
                case 't':
                case 'T':
                        hashAlgorithm = (char *)malloc(strlen(&argv[i][2]));
                        strcpy(hashAlgorithm, &argv[i][2]);
                        break;
                default : std::cout << "Ignoruji neznámý přepínač " << argv[i];
            }
        }
        else {
            std::cout << "Ignoruji nepovoleny argument" << *argv[i];
        }
    }
}

void printHelp(){
    std::cout << "Program HashMachine v1.0" << "\n";
    std::cout << "Semestrální práce KIV/BIT akademický rok 2015/16" << "\n";
    std::cout << "Program slouzi k výpočtu zvolených hash funkcí." << "\n";
    std::cout << "Implementovány: SHA-512." << "\n";
    std::cout << "Radek VAIS" << "\n";
    std::cout << "\n";
    std::cout << "Napoveda ke spusteni:" << "\n";
    std::cout << "HashMachine [options]"<< "\n";
    std::cout << "Možné volby:"<< "\n";
    std::cout << "\t" << "-h - zobrazí nápovědu" << "\n";
    std::cout << "\t" << "-t - nastaví typ hash funkce (výchozí sha512)"<< "\n";
    std::cout << "\t" << "-f<filename> - nastavi cestu ke vstupnimu souboru"<< "\n";
    std::cout << "\n";

    std::cout << "Ukazka spusteni" << "\n";
    std::cout << "HashMachine -fboo -tsha512" << "\n";
    std::cout << "Spusti vytvareni hash SHA512 ze souboru boo" << "\n";
}


/**
 * Funkce připraví třídu pro výpočet hash.
 * @param machine adresa pro uložení adresy výpočetního mlýnku
 */
void prepareHashStandard(IHashStandard **machine){
    if(strcmp(hashAlgorithm, "sha512") == 0){
        *machine = new Sha512();
    }else{
        *machine = new NoAlgorithm();
        std::cerr << "main: Nerozopznaný hash algoritmus " << hashAlgorithm << std::endl;
    }
}

int runConsoleApp(int argc, char *argv[]){
    readArguments(argc, argv);
    if(printHelpBool){
        printHelp();
        return 0;
    }

    IHashStandard *machine;
    prepareHashStandard(&machine);

    IFile *file;
    if(!fileIsSet){
        file = new LocalStdIn();
    }else{
        file = new LocalCFile(filename);
    }
    if(file->isOk()){
        std::string *hash = machine->hash(file);
        std::cout << *hash << std::endl;
        delete hash;
    }else{
        std::cout << "File "<< filename <<" is not readable" << std::endl;
        delete machine;
        delete file;
        return 5;
    }

//clean memory
    delete machine;
    delete file;
    return 0;
}

//====================================================================================================

int main(int argc, char *argv[]) {

//přesměrování std::err do souboru s logem
    std::ofstream out("out.log");
    std::streambuf *cerrbuf = std::cerr.rdbuf();
    std::cerr.rdbuf(out.rdbuf()); //redirect std::cerr to out.log

//spust aplikaci
    int retVal = runConsoleApp(argc, argv); // run aplication

//navrácení původní std::err
    out.flush();
    std::cerr.rdbuf(cerrbuf);

    return retVal;
}

