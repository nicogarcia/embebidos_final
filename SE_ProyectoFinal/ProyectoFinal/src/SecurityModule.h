#ifndef SECURITY_MODULE
#define SECURITY_MODULE

#include "Definitions.h"

class SecurityModule {
public:
    static bool authorizeRequest(Request request, Input inputs[INPUT_MAX_COUNT]);
};

#endif /* SECURITY_MODULE */
