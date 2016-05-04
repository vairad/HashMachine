#include "sha512.h"

#include <iostream>
#include <iomanip>
#include <sstream>

/**
 * Metoda rotuje bity v 64bitovém slově směrem vlevo.
 * @param to_rotate word to rotate
 * @param step number of rotation steps
 * @return rotated number
 */
uint64_t Sha512::rotateLeft(uint64_t to_rotate, uint8_t step) {
    return (to_rotate << step) | (to_rotate >> (64 - step) );
}

/**
 * Metoda rotuje bity v 64bitovém slově směrem vpravo.
 * @param to_rotate word to rotate
 * @param step number of rotation steps
 * @return rotated number
 */
uint64_t Sha512::rotateRight(uint64_t to_rotate, uint8_t step) {
    return (to_rotate >> step) | (to_rotate << (64 - step) );
}

//====================== STANDARD FUNCTIONS =============================================

uint64_t Sha512::functionCh(uint64_t x, uint64_t y, uint64_t z) {
    return  ((x & y) xor (~x & z));
}

uint64_t Sha512::functionMaj(uint64_t x, uint64_t y, uint64_t z) {
    return ((x & y) xor ( x & z) xor (y & z));
}

uint64_t Sha512::bigSigma0(uint64_t x){
    return (rotateRight(x, 28) xor rotateRight(x, 34) xor rotateRight(x, 39));
}

uint64_t Sha512::bigSigma1(uint64_t x){
    return (rotateRight(x, 14) xor rotateRight(x, 18) xor rotateRight(x, 41));
}

uint64_t Sha512::smallSigma0(uint64_t x){
      return (rotateRight(x, 1) xor rotateRight(x, 8) xor (x >> 7));
}

uint64_t Sha512::smallSigma1(uint64_t x){
      return (rotateRight(x, 19) xor rotateRight(x, 61) xor (x >> 6));
}

//=======================================================================================

/**
 * Metoda vypočte zarovnání zprávy následujícím způsobem:
 * Hledáme nejmenší nezáporné řešení rovnice (početBitůZprávy + 1 + ?počet nul? + 128) % 1024 je 0.
 *
 * Po získání řešení nastaví stavové proměnné týkající se zarovnání zprávy:
 * @code{zeroBytesCount}, @code{restZeroBytes}, @code{msgBlocks}
 * Počet nul pro odsazení a počet bloků zprávy
 */
void Sha512::computePadding(){
    uint64_t space = 8;     //minimal length of one bit space
    uint64_t ending = 128;  //normalized size of endnding
    uint64_t zeros = 0;

    for(; zeros < 1024; ++zeros){
        if( (msgBits + space + ending + zeros) % 1024 == 0 ){
            break;
        }
    }

    zeroBytesCount = zeros / 8;
    restZeroBytes = zeroBytesCount;
    std::cerr << name << " zeros to be placed " << zeros << " without margin space 8bit" << std::endl;

    msgBlocks = (msgBits + space + ending + zeros) / 1024;
    std::cerr << name << " msg block count " << msgBlocks << std::endl;
}

/**
 * Metoda dle standardu připraví W schedule vektor pro iteraci bloku zprávy
 */
void Sha512::computeWVector(){
    for(int i = 0; i < 16; ++i){
        W[i] = messageBlock[i];
    }
    for(int i = 16; i < 80; ++i){
        W[i] = smallSigma1(W[i-2]) + W[i-7] + smallSigma0(W[i-15]) + W[i-16];
    }
}

/**
 * Meotda připraví stav třídy pro výpočet nové hash
 */
void Sha512::initHashComputation(){
    for(int i = 0; i < 8; ++i){
        H[i] = initialVector[i];
    }
    spaceWritten = false;
}

/**
 * Metoda připraví do pomocné proměnné další blok zarovnané zprávy.
 */
void Sha512::prepareNextMsgBlock(){
    for(int i = 0; i < 16; i++){ //message length is 16*8 byte == 1024 bit
        uint64_t tmp = 0;

        if(restMsgBytes > 0 || restZeroBytes > 0){ //pokud existují nějaké byty nul nebo zprávy zapisuj byte po bytu
            for(int j = 0; j < 8; j++){ //sizeof uint64_t
               tmp += nextMessageByte(); //append next byte of message
               if(j == 7){  // if it is last byte do not shift
                   break;
               }
               tmp = tmp << 8; //else shift msg byte for another msgByte
            }
            messageBlock[i] = tmp;
        }else{                  // else write last 128bit with msgBit count
            messageBlock[i] = 0; // this implementation can work with files, that bit count is in range uint64_t
            i++;
            messageBlock[i] = msgBits;
        }
    }
    std::cerr << name << " message ready "<< std::endl;
}

/**
 * Metoda připraví další byte zprávy v závislosti na stavových proměnných třídy.
 * Jsou tři možné návratové stavy: byte je ze zdrojového souboru, byte je zarovnání, byte jsou nuly
 * @return next byte of message
 */
uint8_t Sha512::nextMessageByte(){
    uint8_t out = 0;
    if(restMsgBytes > 0){ //existují byty zprávy vrať byte zprávy
        out = file->getByte();
        restMsgBytes--;
    }else if(!spaceWritten && restZeroBytes == zeroBytesCount){// je zapsáno zarovnání?
        out = space;
        spaceWritten = true;
        std::cerr << name << " space was written " << std::endl;
    }else if(restZeroBytes > 0){ // esistují nuly k zapsání?
        out = 0;
        restZeroBytes--;
    }
    return out;
}

/**
 * Metoda vykoná iteraci hash funkce nad blokem zprávy. Dle standardu
 */
void Sha512::iterateHash(){
    prepareNextMsgBlock();
    computeWVector();

    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    for(int i = 0; i < 80; ++i){
        uint64_t T1, T2;

        T1 = h + bigSigma1(e) + functionCh(e, f, g) + K[i] + W[i];
        T2 = bigSigma0(a) + functionMaj(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;
}

/**
 * Metoda připraví řetězec výstupu do pole @code{outHash}
 * Výstup je ve formátu hexadecimálního čísla.
 */
void Sha512::prepareOutString(){
    std::stringstream stream;

    for (int i = 0; i < 8; ++i) {
        stream << std::setw(16) << std::setfill('0') << std::hex << H[i];        
    }
    outHash = new std::string( stream.str() );
}

//=======================================================================================

/**
 * Metoda výpočet hashfunkce SHA512 nad souborem v parametru.
 *
 * @param file file to compute hash
 * @return hexadecimal output of function
 */
std::string *Sha512::hash(IFile *file){
    this->file = file;

// compute msg bits
    msgBytes = file->getBytesCount();
    restMsgBytes = msgBytes;
    std::cerr << name << " msg byte count " << msgBytes << std::endl;

    uint64_t uintMax = 0xffffffffffffffff; // kontrola, zda soubor není nad možnosti tohoto alg
    if( (uintMax / 8) <= msgBytes ){
        std::cerr << name << " WARNING " << " possible problem with msg length "<< std::endl;
    }

//compute bits
    this->msgBits = file->getBytesCount()*8;
    std::cerr << name << " msg bits count " << msgBits << std::endl;

//compute padding constants of message
    computePadding();

// initialize variables
    initHashComputation();

// iterate over msgBlocks (one block 1024 bit)
    for(uint32_t n = 0; n < msgBlocks; n++){
        iterateHash();
    }

    prepareOutString();

    return outHash;
}

//=======================================================================================

Sha512::Sha512() {
    //do nothing
}

Sha512::~Sha512(){
    //do nothing ?? clear space
}
