#if !defined(BOTHLGAME_HPP)
#define BOTHLGAME_HPP

#include <map>

#include "IBot.hpp"
#include "Parser.hpp"

namespace ft_irc
{

class BotHLGame :
	public IBot
{
public:
	static const int ID = -1;

private:
	int value;

private:
	std::map< std::string, int > games;

private:
	BotHLGame(const ft_irc::Client &other);

	std::string guess(int x, const std::string &origin) const;

public:
	BotHLGame();
	BotHLGame(const BotHLGame &other);
	~BotHLGame();

	BotHLGame& operator=(const BotHLGame &other);

	virtual void exec(ft_irc::Parser::cmd_t *cmd) const;
	virtual void onInvite(std::string &chan) const;

	void newGame(std::string &chan, int max = 100);
};	// class BotHLGame

}	// namespace ft_irc

#endif // BOTHLGAME_HPP
