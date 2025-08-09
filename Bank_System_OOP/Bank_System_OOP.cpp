#include <iostream>
#include "clsLoginScreen.h"

#include "clsUtil.h"

using namespace std;

int main()
{
	while (true)
	{
		if (!clsLoginScreen::showLoginScreen())
		{
			break;
		}

	}

	return 0;
}