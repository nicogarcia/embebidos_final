#ifndef AUXILIAR_MODULE
#define AUXILIAR_MODULE

#include "Definitions.h"

class AuxiliarModule {
public:
    static bool isValidPassword(Input password);
    static bool isValidRequest(Input request);
    static bool isValidUsername(Input username);
    static void stringToCharArray(String string, char char_array[]);
private:
    static bool isValidInputParameter(Input input_parameter);
    static bool isValidInputParameterCharacter(char character);
};

#endif // AUXILIAR_MODULE
