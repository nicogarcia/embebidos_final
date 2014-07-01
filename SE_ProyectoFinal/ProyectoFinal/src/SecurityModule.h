#ifndef SECURITY_MODULE
#define SECURITY_MODULE

#include "Definitions.h"

class SecurityModule {
public:
    static bool authorizeRequest(Request request, Input input_parameters[INPUT_PARAMETER_MAX_COUNT]);
    static bool isValidPassword(Input password);
    static bool isValidRequest(Input request);
    static bool isValidUsername(Input username);
private:
    static bool isValidInputParameter(Input input_parameter);
    static bool isValidInputParameterCharacter(char character);
};

#endif // SECURITY_MODULE
