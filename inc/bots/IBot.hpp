#if !defined(IBOT_HPP)
#define IBOT_HPP

#include <string>

#include "Client.hpp"
#include "Parser.hpp"

namespace ft_irc
{

class IBot :
	public Client
{
private:
public:
	IBot(void);
	IBot(const IBot &other);
	IBot(const ft_irc::Client &other);
	virtual ~IBot(void) {}

	IBot& operator=(const IBot &other);

	// From
	virtual void sendMsg(const std::string &msg) const;
	virtual void respond(const std::string &msg, const std::string &response) const;
	virtual void respond(const ft_irc::Parser::cmd_t *cmd, const std::string &response) const;

	virtual void onInvite(std::string &chan) const;
	virtual void exec(ft_irc::Parser::cmd_t *cmd) const = 0;
};	// class IBot

}	// namespace ft_irc

#endif // IBOT_HPP
