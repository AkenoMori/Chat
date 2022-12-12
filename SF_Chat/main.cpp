#include "Chat.h"
#include <iostream>

int main()
{
	setlocale(LC_ALL, "");
	Chat chat;
	chat.startChat();

	while (chat.work())
	{
		chat.showLoginMenu();
		while (chat.getcurrentUser())
		{
			chat.showUserMenu();
		}
	}
	return 0;
}
