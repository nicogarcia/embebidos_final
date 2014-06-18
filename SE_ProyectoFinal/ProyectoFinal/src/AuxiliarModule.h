#ifndef AUXILIAR_MODULE
#define AUXILIAR_MODULE

#include "Definitions.h"

class AuxiliarModule {
public:
	static String charArrayToString(char char_array[INPUT_MAX_LENGTH + 1]);
	static bool isValidUsername(Username username);
	static bool isValidPassword(Password password);
private:
	static bool isValidInput(Input input);
	static bool isValidInputCharacter(char character);
};

#endif /* AUXILIAR_MODULE */
