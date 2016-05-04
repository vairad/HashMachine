#include "localstdin.h"

LocalStdIn::LocalStdIn() {
    std::cout << "File was not choosed \n" << "Type your message:" << std::endl;
    msg = "";
    std::cin >> msg;
    std::cerr << "Readed from std::in: '" << msg << "'" << std::endl;
    std::cerr << "Byte len: " << msg.length() << std::endl;
}

uint64_t LocalStdIn::getBytesCount() {
    return msg.length();
}

uint8_t LocalStdIn::getByte() {
    return msg.at(i++);
}

bool LocalStdIn::isOk(){
    return msg.length() > 0;
}
