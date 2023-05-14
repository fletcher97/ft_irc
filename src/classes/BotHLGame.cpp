#include <stdexcept>

#include <cstdlib>

#include "Log.hpp"

#include "BotHLGame.hpp"
#include "Server.hpp"

std::string
ft_irc::BotHLGame::guess(int x, const std::string &origin) const
{
	try {
		LOG_TRACE("BotHLGame: guess on chan " + origin)
		LOG_TRACE("BotHLGame: value is " << this->games.at(origin) << " and " << x << " was guessed")
		if (this->games.at(origin) > x) {
			LOG_TRACE("BotHLGame: Too low")

			return "Too low";
		}
		if (this->games.at(origin) < x) {
			LOG_TRACE("BotHLGame: Too high")

			return "Too high";
		}

		LOG_TRACE("BotHLGame: Correct!")

		return "Correct!";
	} catch (std::exception &e) {
		LOG_ERROR("BotHLGame: exception will guessing")
		LOG_ERROR(e.what())

		return "Error!";
	}
}	// BotHLGame::guess


ft_irc::BotHLGame::BotHLGame(void) :
	ft_irc::IBot()
{
	this->_fd = ft_irc::BotHLGame::ID;
	this->_nickname = "BotHLGame";
	this->_username = "BotHLGame";
	this->_realname = "BotHLGame";
	this->_status = ONLINE;
	this->_mode = CL_BOT;
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

	LOG_TRACE("BotHLGame: exec")

	where = cmd->args[0];

	if (cmd->args[1] != "?hl") {
		LOG_TRACE("BotHLGame: Message not for BotHLGame")

		return;
	}

	LOG_FATAL("Arg size: " << cmd->args.size())
	for (size_t i = 0; i < cmd->args.size(); i++) {
		LOG_FATAL(cmd->args[i])
	}

	if (cmd->args[2] == "guess") {
		if (cmd->args.size() < 4) {
			LOG_TRACE("BotHLGame: invalid usage")
			this->respond(cmd, "Usage: ?hl guess <value>");
		}
		this->respond(cmd, this->guess(std::atoi(cmd->args[3].c_str()), where));
	} else if (cmd->args[2] == "new") {
		if (cmd->args.size() < 4) {
			LOG_TRACE("BotHLGame: invalid usage")
			this->respond(cmd, "Usage: ?hl new <max_size>");
		}
		dynamic_cast< ft_irc::BotHLGame & >(ft_irc::Server::getInstance().getClient(this->ID)).newGame(where,
			std::atoi(cmd->args[3].c_str()));
	} else if (cmd->args[2] == "help") {
		LOG_TRACE("BotHLGame: help")
		this->respond(cmd, "Usage:");
		this->respond(cmd, "?hl help");
		this->respond(cmd, "    Show this message");
		this->respond(cmd, "?hl guess <value>");
		this->respond(cmd, "    Try to guess");
		this->respond(cmd, "?hl new <max_size>");
		this->respond(cmd, "    Start a new game. max_size is exclusive");
	} else {
		LOG_TRACE("BotHLGame: Unknown command")
		this->respond(cmd, "Unknown command " + cmd->args[2]);
	}
}	// BotHLGame::exec


void
ft_irc::BotHLGame::onInvite(std::string &chan) const
{
	LOG_TRACE("BotHLGame: onInvite to chan " + chan)
	try {
		ft_irc::IBot::onInvite(chan);
	} catch (...) {
		LOG_ERROR("Issue on join from IBot")
	}

	dynamic_cast< ft_irc::BotHLGame & >(ft_irc::Server::getInstance().getClient(this->ID)).newGame(chan);
}	// BotHLGame::onInvite


void
ft_irc::BotHLGame::newGame(std::string &chan, int max)
{
	LOG_TRACE("BotHLGame: new game for chan " + chan);
	this->games[chan] = (std::rand() % max);
}	// BotHLGame::newGame
