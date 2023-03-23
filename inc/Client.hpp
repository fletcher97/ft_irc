#if !defined(CLIENT_HPP)
#define CLIENT_HPP

#include <string>
#include <map>

#include "Channel.hpp"

class Channel;
class Client
{
public:
	enum	Status
	{
		PASSWORD,
		REGISTER,
		ONLINE,
		AWAY,
		DELETE
	};

private:
	int	_fd;
	std::string _address;
	std::string _hostname;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	Status	_status;

public:
	Client(int fd, struct sockaddr_in socket);
	Client(const Client& c);
	Client& operator=(const Client& c);
	~Client(void);

	int	getFd(void) const;
	const std::string&	getAddress(void) const;
	const std::string&	getHostname(void) const;
	const std::string&	getNickname(void) const;
	const std::string&	getUsername(void) const;
	const std::string&	getRealname(void) const;
	Status	getStatus(void) const;

	void	setNickname(std::string& nickname);
	void	setUsername(std::string& username);
	void	setRealname(std::string& realname);
	void	setStatus(Status status);
};

#endif // CLIENT_HPP
