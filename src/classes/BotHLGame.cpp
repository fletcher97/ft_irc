#include <cstdlib>

#include "Log.hpp"

#include "BotHLGame.hpp"
#include "Server.hpp"

std::string
ft_irc::BotHLGame::guess(int x, const std::string &origin) const
{
	if (this->games.at(origin) > x) {
		return "Too high";
	}
	if (this->games.at(origin) < x) {
		return "Too low";
	}

	return "Correct!";
}	// BotHLGame::guess


ft_irc::BotHLGame::BotHLGame(void) :
	ft_irc::IBot()
{
	this->_fd = ft_irc::BotHLGame::ID;
	this->_nickname = "BotHLGame";
	this->_username = "BotHLGame";
	this->_realname = "BotHLGame";
	this->_status = ONLINE;
	this->_mode = 0;
}


ft_irc::BotHLGame::BotHLGame(const ft_irc::BotHLGame &other) :
	ft_irc::IBot(other)
{
	this->games = other.games;
}


ft_irc::BotHLGame::~BotHLGame()
{}

ft_irc::BotHLGame&
ft_irc::BotHLGame::operator=(const ft_irc::BotHLGame &other)
{
	ft_irc::IBot::operator=(other);
	this->games = other.games;

	return *this;
	// TODO: insert return statement here
}	// =


void
ft_irc::BotHLGame::exec(ft_irc::Parser::cmd_t *cmd) const
{
	std::string where;
	std::string token;

	if (cmd->args.size() != 2) {
		LOG_TRACE("Message has too many arguments")

		return;
	}

	where = cmd->args[0];
	std::stringstream msg(cmd->args[1]);

	msg >> token;
	if (token != "?hl") {
		LOG_TRACE("Message not for BotHLGame")

		return;
	}

	msg >> token;
	if (token == "guess") {
		msg >> token;
		if (token.empty()) {
			this->respond(cmd, "Usage: ?hl guess <value>");
		}
		this->respond(cmd, this->guess(std::atoi(token.c_str()), where));
	} else if (token == "new") {
		msg >> token;
		if (token.empty()) {
			this->respond(cmd, "Usage: ?hl new <max_size>");
		}
		dynamic_cast< ft_irc::BotHLGame & >(ft_irc::Server::getInstance().getClient(this->ID)).newGame(where,
			std::atoi(token.c_str()));
	} else if (token == "help") {
		this->respond(cmd, "Usage:");
		this->respond(cmd, "?hl help");
		this->respond(cmd, "    Show this message");
		this->respond(cmd, "?hl guess <value>");
		this->respond(cmd, "    Try to guess");
		this->respond(cmd, "?hl new <max_size>");
		this->respond(cmd, "    Start a new game. max_size is exclusive");
	} else {
		this->respond(cmd, "Unknown command " + token);
	}
}	// BotHLGame::exec


void
ft_irc::BotHLGame::onInvite(std::string &chan) const
{
	ft_irc::IBot::onInvite(chan);
	dynamic_cast< ft_irc::BotHLGame & >(ft_irc::Server::getInstance().getClient(this->ID)).newGame(chan);
}	// BotHLGame::onInvite


void
ft_irc::BotHLGame::newGame(std::string &chan, int max)
{
	this->games[chan] = (std::rand() % max);
}	// BotHLGame::newGame
