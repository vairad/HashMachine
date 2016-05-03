#ifndef IHASHSTANDARD_H
#define IHASHSTANDARD_H

#include "ifile.h"
#include <string>

/**
 * Třída definující rozhraní třídy zajišťující algoritmus hash funkce.
 *
 * @author Radek VAIS
 * @version 1.0.0
 * @date 3.5.2016
 */
class IHashStandard
{
public:
   /**
   * Metoda, která zajišťuje vykonání algoritmu hash funkce, jako návratová hodnota je
   * std::string, který představuj výstup hash algoritmu.
   * Výstupem je zpravidla hexadecimální číslo.
   *
   * @param file instance třídy IFile
   * @return výstup hash funkce
   */
  virtual std::string *hash(IFile *file) = 0;

  virtual ~IHashStandard(){}
};


#endif // IHASHSTANDARD_H
