#if !defined(CLIENT_HPP)
#define CLIENT_HPP

#include <string>

// Client modes. Registered will not be implemented
#define CL_INVISIBLE 0x01
#define CL_LOCALOP 0x02
#define CL_OP 0x04
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

	typedef unsigned char mode_t;
protected:
	int _fd;
	std::string _address;
	std::string _hostname;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	Client::Status _status;
	mode_t _mode;

protected:
	Client(void);

public:
	Client(int fd, struct sockaddr_in socket);
	Client(const Client &c);

	Client& operator=(const Client &c);

	virtual ~Client(void);

	int getFd(void) const;
	const std::string& getAddress(void) const;
	const std::string& getHostname(void) const;
	const std::string& getNickname(void) const;
	const std::string& getUsername(void) const;
	const std::string& getRealname(void) const;
	Client::Status getStatus(void) const;
	std::string getMask(void) const;
	Client::mode_t getMode(void) const;

	void setNickname(const std::string &nickname);
	void setUsername(const std::string &username);
	void setRealname(const std::string &realname);
	void setStatus(Client::Status status);

	bool addMode(const Client::mode_t mode);
	bool removeMode(const Client::mode_t mode);

	virtual void sendMsg(const std::string &msg) const;
};	// class Client

}	// namespace ft_irc

#endif // CLIENT_HPP
