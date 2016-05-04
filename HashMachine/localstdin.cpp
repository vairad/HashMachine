#include "localstdin.h"

/**
 * Konstruktor s pomocí standardních proudů naplní pole zprávy.
 */
LocalStdIn::LocalStdIn() {
    std::cout << "File was not choosed \n" << "Type your message:" << std::endl;
    msg = "";
    std::cin >> msg;
    std::cerr << name << "Readed from std::in: '" << msg << "'" << std::endl;
    std::cerr << name << "Byte len: " << msg.length() << std::endl;
}

/**
 * vrátí počet bytů souboru
 * @return vrátí počet bytů souboru
 */
uint64_t LocalStdIn::getBytesCount() {
    return msg.length();
}

/**
 * Vrátí následující byte souboru.
 * --
 * Pokud vyžadujeme neexistující byte vrací 0
 * @return následující byte souboru
 */
uint8_t LocalStdIn::getByte() {
    if(i < msg.length()){
        return msg.at(i++);
    }else{
        return 0;
    }
}

/**
 * Zkontroluje, zda lze číst ze souboru.
 * --
 * Kontroluje, že zpráva není prázdná.
 * @return zda lze ze souboru číst
 */
bool LocalStdIn::isOk(){
    return msg.length() > 0;
}
