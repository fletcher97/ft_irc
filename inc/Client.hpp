#if !defined(CLIENT_HPP)
#define CLIENT_HPP

#include <string>
#include <stdexcept>

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

protected:
	int	_fd;
	std::string _address;
	std::string _hostname;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	Client::Status	_status;

	Client(void);

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
	Client::Status	getStatus(void) const;
	std::string	getMask(void) const;

	void	setNickname(const std::string& nickname);
	void	setUsername(const std::string& username);
	void	setRealname(const std::string& realname);
	void	setStatus(Client::Status status);

public:
	class EmptyArgument : public std::invalid_argument
	{
	public:
			EmptyArgument(std::string msg);
	};
};

#endif // CLIENT_HPP
