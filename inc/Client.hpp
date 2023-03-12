#if !defined(CLIENT_HPP)
#define CLIENT_HPP

#include <string>
#include <map>

#include "Channel.hpp"

enum	ClientStatus
{
	PASSWORD,
	REGISTER,
	ONLINE,
	AWAY
};

struct	ClientMode
{
	bool	a;
	bool	i;
	bool	w;
	bool	r;
	bool	o;
	bool	O;
	bool	s;
	
	ClientMode();
	ClientMode(const ClientMode& m);
	ClientMode& operator=(const ClientMode& m);
};

class Channel;
class Client
{
private:
	int	_fd;
	std::string _address;
	std::string _hostname;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	std::map<std::string, Channel&> _channels;
	ClientStatus	_status;
	ClientMode	_mode;
public:
	Client(int fd, struct sockaddr_in socket);
	Client(const Client& c);
	Client& operator=(const Client& c);
	~Client();

	int	getFd() const;
	std::string	getAddress() const;
	std::string getHostname() const;
	std::string getNickname() const;
	std::string getUsername() const;
	std::string getRealname() const;
	ClientStatus	getStatus() const;
	
	// std::vector<Channel&>	getChannels() const; TODO
	bool	getMode(char c) const;
	
	void	setNickname(std::string nickname);
	void	setUsername(std::string username);
	void	setRealname(std::string realname);
	void	setStatus(ClientStatus status);
	void	setMode(char c);
	
	//void handleCommand TODO
	//void sendTo TODO
};

#endif // CLIENT_HPP
