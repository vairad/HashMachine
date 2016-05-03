#ifndef IFILE_H
#define IFILE_H

#include <cstdint>

/**
 * Třída defnující rozhraní souboru pro komunikaci s rozhraním IHashStandard
 *
 * @author Radek VAIS
 * @version 1.0.0
 * @date 3.5.2016
 */
class IFile
{
public:
  /**
   * vrátí počet bytů souboru
   * @return vrátí počet bytů souboru
   */
  virtual uint64_t getBytesCount() = 0;

  /**
   * Vrátí následující byte souboru.
   * @return následující byte souboru
   */
  virtual uint8_t getByte() = 0;

  /**
   * Zkontroluje, zda lze číst ze souboru.
   * @return zda lze ze souboru číst
   */
  virtual bool isOk() = 0;

  virtual ~IFile(){}
};

#endif // IFILE_H
