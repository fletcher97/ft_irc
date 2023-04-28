#include <algorithm>

#include "Log.hpp"

#include "Client.hpp"
#include "Server.hpp"

static bool
preChecks(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	// check state
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_WARN("mode: Client didn't set the password yet")
		client.sendMsg("ERROR :Password required");

		return false;
	}
	if (client.getStatus() == ft_irc::Client::REGISTER) {
		LOG_WARN("mode: Client " << client.getFd << "hasn't registered yet ")
		client.sendMsg("451");	// 451 - ERR_NOTREGISTERED

		return false;
	}
	// check target
	if (!cmd->args.size()) {
		LOG_WARN("mode: 461: Need more params")
		client.sendMsg("461");	// 461 - ERR_NEEDMOREPARAMS

		return false;
	}

	return true;
}	// preChecks


static bool
updateClientMode(ft_irc::Client &client, char c, bool &add)
{
	switch (c) {
		case '+': {
			add = true;

			return false;
		}

		case '-': {
			add = false;

			return false;
		}

		case 'i': {
			if (add) {
				client.addMode(CL_INVISIBLE);
			} else {
				client.removeMode(CL_INVISIBLE);
			}

			return true;
		}

		case 'o': {
			if (add) {
				client.addMode(CL_OP);
			} else {
				client.removeMode(CL_OP);
			}

			return true;
		}

		case 'O': {
			if (add) {
				client.addMode(CL_LOCALOP);
			} else {
				client.removeMode(CL_LOCALOP);
			}

			return true;
		}

		case 'w': {
			if (add) {
				client.addMode(CL_WALLOPS);
			} else {
				client.removeMode(CL_WALLOPS);
			}

			return true;
		}

		default: {
			LOG_WARN("mode: 221 " + client.getNickname() + " " + c + " :Unknown MODE flag")
			client.sendMsg("221 " + client.getNickname() + " " + c + " :Unknown MODE flag");// 221 - RPL_UMODEIS

			return false;
		}
	}	// updateClientMode
}	// updateClientMode


static void
updatedResponse(std::string &added, std::string &removed, char c, bool add)
{
	if (add && (added.find(c) == std::string::npos)) {
		added += c;
		if ((removed.find(c) != std::string::npos)) {
			removed.erase(std::remove(removed.begin(), removed.end(), c), removed.end());
		}
	} else if (!add && (removed.find(c) == std::string::npos)) {
		removed += c;
		if ((added.find(c) != std::string::npos)) {
			added.erase(std::remove(added.begin(), added.end(), c), added.end());
		}
	}
}	// updatedResponse


static void
modeClient(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd, const std::map< int, ft_irc::Client* > clients)
{
	bool found = false;

	// User exists check
	for (std::map< int, ft_irc::Client* >::const_iterator it = clients.begin(); it != clients.end() && !found; it++) {
		if (it->second->getNickname() == cmd->args[0]) {
			found = true;
		}
	}
	if (!found) {
		LOG_WARN("mode: 401: No such nick")
		client.sendMsg("401");	// 401 - ERR_NOSUCHNICK

		return;
	}

	// Same user check
	if (cmd->args[0] != client.getNickname()) {
		LOG_WARN("mode: 502: Cant change mode for other users")
		client.sendMsg("502");	// 502 - ERR_USERSDONTMATCH

		return;
	}

	// get client modes
	if (cmd->args.size() == 1) {
		ft_irc::Client::mode_t mmodes = client.getMode();
		std::string smodes = "+";

		smodes += ((mmodes & CL_INVISIBLE) ? "i" : "");
		smodes += ((mmodes & CL_LOCALOP) ? "O" : "");
		smodes += ((mmodes & CL_OP) ? "o" : "");
		smodes += ((mmodes & CL_WALLOPS) ? "w" : "");
		LOG_INFO("mode: 221: " + smodes)
		client.sendMsg("221 " + client.getNickname() + " " + smodes);	// 221 - RPL_UMODEIS

		return;
	}

	bool add = (cmd->args[0][0] != '-');// default to add if no sign is specified
	std::string added, removed;

	for (long unsigned int i = 0; i < cmd->args[0].size(); i++) {
		if (updateClientMode(client, cmd->args[0][i], add)) {
			updatedResponse(added, removed, cmd->args[0][i], add);
		}
	}	// switch
	LOG_INFO("mode: 221: " + smodes)
	client.sendMsg("MODE" + client.getNickname() + " :" + (added.size() ? "+" + added : "")
		+ (removed.size() ? "-" + removed : ""));	// 221 - RPL_UMODEIS
}	// modeClient


void
ft_irc::Server::mode(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	// check client state
	if (!preChecks(client, cmd)) {
		return;
	}
	if (cmd->args[0].find_first_of("#&") == std::string::npos) {
		// Target is a client
		modeClient(client, cmd, this->_clients);
	}
}	// Server::mode
