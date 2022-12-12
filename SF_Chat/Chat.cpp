#include <iostream>
#include <memory>
#include <exception>
#include "Chat.h"
#include <fstream>

void Chat::startChat()
{
	work_ = true;
}

shared_ptr <User> Chat::getUserLog(const string& login) const
{
	for (auto& user : userArr_)
	{
		if (login == user.getlog())
		{
			return make_shared<User>(user);
		}

	}
	return nullptr;
}

shared_ptr <User> Chat::getUserName(const string& name) const
{
	for (auto& user : userArr_)
	{
		if (name == user.getName())
		{
			return make_shared<User>(user);
		}

	}
	return nullptr;
}


void Chat::userLogin()
{
	string login_check = "login.txt";
	string password_check = "password.txt";
	fstream log;
	fstream pass;
	string login, password;
	log.open(login_check, fstream::in | fstream::out | fstream::app);
	pass.open(password_check, fstream::in | fstream::out | fstream::app);
	if (!log.is_open() && !pass.is_open())
	{
		cout << "Ошибка!" << endl;
	}
	else {
		do
		{
			char op;

			while (!log.eof()) 
			{
				login = "";
				log >> login; 
			}
			while (!pass.eof()) 
			{
				password = "";
				pass >> password; 
			}
			string _log;
			string _pass;
			cout << "Авторизация." << endl;
			cout << "Логин: " << endl;
			cin >> _log;
			cout << "Пароль: " << endl;
			cin >> _pass;
			if (_log != login && _pass != password)
			{
				cout << "Пароль или логин введен не правильно!" << endl;
			}
			else
			{
				currentUser_ = getUserLog(login);
			}

			

		} while (!currentUser_);
	}
}
void Chat::userRegistration()
{
	cout << "Регистрация" << endl;
	string login_check = "login.txt";
	string password_check = "password.txt";
	string name;
	fstream log;
	fstream pass;
	string login, password;
	log.open(login_check, fstream::in | fstream::out | fstream::app);
	pass.open(password_check, fstream::in | fstream::out | fstream::app);
	if (!log.is_open() && !pass.is_open())
	{
		cout << "Ошибка!" << endl;
	}
	else {
		
		cout << "Логин:  " << endl;
		cin >> login;
		cout << "Пароль:   " << endl;
		cin >> password;
		log << login;
		pass << password;
		cout << "Имя: " << endl;
		cin >> name;

		if (getUserLog(login) || login == "all")
		{
			throw UserLoginEx();
		}

		User user = User(login, password, name);
		userArr_.push_back(user);
		currentUser_ = make_shared <User>(user);

	}
}
void Chat::showUserMenu()
{
	char op;
	cout << "Привет, " << currentUser_->getlog() << endl;
	while (currentUser_)
	{
		cout << "1 - Показать чат, 2 - Отправить сообщение, 3 - Показать всех пользователей, 0 - выход" << endl;
		cin >> op;

		switch (op)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsers();
			break;
		case '0':
			currentUser_ = nullptr;
			break;

		default:
			cout << "Введите 1,2,3" << endl;
		}
	}

}

void Chat::addMessage()
{
	string to, text;
	cout << "Введите имя кому отправить сообщение, для отправки сообщения всем - all" << endl;
	cin >> to;
	cout << "Введите сообщение:" << endl;
	cin.ignore();
	getline(cin, text);

	if (!((to == "all") || getUserName(to)))
	{
		cout << "error" << to << endl;
		return;
	}

	if (to == "all")
	{
		messageArr_.push_back(Message{ currentUser_->getlog(), "all", text });
	}

	else
	{
		messageArr_.push_back(Message{ currentUser_->getlog(), getUserName(to)->getlog(), text });
	}

}

void Chat::showLoginMenu()
{
	currentUser_ = nullptr;
	char op;
	do
	{
		cout << " 1 - Авторизация " << endl;
		cout << " 2 - Регистрация " << endl;
		cout << " 0 - выход " << endl;
		cin >> op;

		switch (op)
		{
		case '1':
			userLogin();
			break;
		case '2':
			try
			{
				userRegistration();
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
			break;
		case '0':
			work_ = false;
			break;

		default:
			cout << "Введите 1, 2, 0" << endl;
		}
	} while (!currentUser_ && work_);
}

void Chat::showChat() const
{
	string from, to;
	cout << "Chat " << endl;

	for (auto& message : messageArr_)
	{
		if (currentUser_->getlog() == message.getFrom() || currentUser_->getlog() == message.getTo() || message.getTo() == "all")
		{
			from = (currentUser_->getlog() == message.getFrom()) ? "me" : getUserLog(message.getFrom())->getName();
		}

		if (message.getTo() == "all")
		{
			to = "(all)";
		}

		else
		{
			to = (currentUser_->getlog() == message.getTo()) ? "me" : getUserLog(message.getTo())->getName();
		}

		cout << "from: " << from << " to: " << to << endl;
		cout << " text " << message.getText() << endl;
	}

}

void Chat::showAllUsers() const
{
	cout << "users" << endl;

	for (auto& user : userArr_)
	{
		cout << user.getName();
		cout << endl;
		if (currentUser_->getlog() == user.getlog())
		{
			cout << "(me)";
			cout << endl;
		}
		cout << "" << endl;
	}
}

