#ifndef AUXILIAR_MODULE
#define AUXILIAR_MODULE

#include "Definitions.h"

class AuxiliarModule {
public:
    static bool isValidPassword(String password);
    static bool isValidRequest(String request);
    static bool isValidUsername(String username);
private:
    static bool isValidInputParameter(String input_parameter);
    static bool isValidInputParameterCharacter(char character);
};

#endif /* AUXILIAR_MODULE */
