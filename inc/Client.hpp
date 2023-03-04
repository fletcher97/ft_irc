#if !defined(CLIENT_HPP)
#define CLIENT_HPP

#include <string>

class Client
{
protected:
	std::string _nick;
	std::string _address;
	std::string _username;
public:
	Client(std::string nick, std::string address, std::string username);
	Client(const Client& c);
	Client& operator=(const Client& c);
	~Client();
};

#endif // CLIENT_HPP
