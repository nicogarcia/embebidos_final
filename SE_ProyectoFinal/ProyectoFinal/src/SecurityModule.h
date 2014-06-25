#ifndef SECURITY_MODULE
#define SECURITY_MODULE

#include "Definitions.h"

class SecurityModule {
public:
    static bool authorizeRequest(Request request, InputParameter input_parameters[INPUT_PARAMETER_MAX_COUNT]);
};

#endif /* SECURITY_MODULE */
