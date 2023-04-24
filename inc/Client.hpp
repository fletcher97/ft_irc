#if !defined(CLIENT_HPP)
#define CLIENT_HPP

#include <stdexcept>
#include <string>

#define CL_NETWORK_OPER 0x01
#define CL_LOCAL_OPER 0x02
#define CL_INVISIBLE 0x04
#define CL_WALLOPS 0x08

namespace ft_irc
{

class Client
{
public:
	enum    Status
	{
		PASSWORD,
		REGISTER,
		ONLINE,
		AWAY,
		DELETE
	};

	typedef char client_mode;

protected:
	int _fd;
	std::string _hostname;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	Client::Status _status;
	client_mode _mode;

	Client(void);

public:
	Client(int fd, struct sockaddr_in socket);
	Client(const Client &c);

	Client& operator=(const Client &c);

	~Client(void);

	int getFd(void) const;
	const std::string& getAddress(void) const;
	const std::string& getHostname(void) const;
	const std::string& getNickname(void) const;
	const std::string& getUsername(void) const;
	const std::string& getRealname(void) const;
	Client::Status getStatus(void) const;
	std::string getMask(void) const;

	void setNickname(const std::string &nickname);
	void setUsername(const std::string &username);
	void setRealname(const std::string &realname);
	void setStatus(Client::Status status);
	void toggleMode(const client_mode mode);
	void sendMsg(const std::string &msg);

public:
	class InvalidMode :
		public std::invalid_argument
	{
public:
		InvalidMode(std::string msg);
	};	// class InvalidMode
};	// class Client

}	// namespace ft_irc

#endif // CLIENT_HPP
