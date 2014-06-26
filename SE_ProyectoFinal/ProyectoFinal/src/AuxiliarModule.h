#ifndef AUXILIAR_MODULE
#define AUXILIAR_MODULE

#include "Definitions.h"

class AuxiliarModule {
public:
    static bool isValidPassword(char* password);
    static bool isValidRequest(char* request);
    static bool isValidUsername(char* username);
    static void stringToCharArray(String string, char *array);
private:
    static bool isValidInputParameter(char* input_parameter);
    static bool isValidInputParameterCharacter(char character);
};

#endif /* AUXILIAR_MODULE */
