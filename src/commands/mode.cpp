#include <algorithm>
#include <list>

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
		LOG_WARN("mode: Client " << client.getFd() << "hasn't registered yet ")
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
updatedListResponse(std::list< std::pair< std::string, std::string > > listResponse, char c, bool add, std::string mask)
{
	std::string first = (add ? "+" : "-") + c;
	std::string rfirst = (!add ? "+" : "-") + c;

	for (std::list< std::pair< std::string, std::string > >::iterator it = listResponse.begin();
		 it != listResponse.end();
		 it++)
	{
		if ((it->first == rfirst) && (it->second == mask)) {
			listResponse.erase(it);

			return;
		}
	}
	listResponse.push_back(std::pair< std::string, std::string >(first, mask));
}	// updateListResponse


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

	bool add = (cmd->args[1][0] != '-');// default to add if no sign is specified
	std::string added, removed;

	for (long unsigned int i = 0; i < cmd->args[1].size(); i++) {
		if (updateClientMode(client, cmd->args[1][i], add)) {
			updatedResponse(added, removed, cmd->args[1][i], add);
		}
	}	// switch
	LOG_INFO("mode: 221: MDOE " + client.getNickname() + " :" + (added.size() ? "+" + added : "")
		+ (removed.size() ? "-" + removed : ""))
	client.sendMsg("MODE " + client.getNickname() + " :" + (added.size() ? "+" + added : "")
		+ (removed.size() ? "-" + removed : ""));	// 221 - RPL_UMODEIS
}	// modeClient


static bool
updateServerMode(ft_irc::Client &client, ft_irc::Channel &chan, char c, bool &add)
{
	ft_irc::Channel::channel_mode mode = 0;

	switch (c) {
		case 'i': {
			mode = CH_INVITE_ONLY;
			break;
		}

		case 'm': {
			mode = CH_MODERATE;
			break;
		}

		case 's': {
			mode = CH_SECRET;
			break;
		}

		case 't': {
			mode = CH_PROTECTED_TOPIC;
			break;
		}

		case 'n': {
			mode = CH_NOT_EXTERNAL_MSGS;
			break;
		}

		case '+': {
			add = true;

			return false;
		}

		case '-': {
			add = false;

			return false;
		}

		default: {
			LOG_WARN("mode: 472 :is unknown mode char to me")
			client.sendMsg("472 :is unknown mode char to me");	// 472 - ERR_UNKNOWNMODE

			return false;
		}
	}	// switch

	if (mode) {
		if ((add && !(chan.getMode() & mode)) || (!add && (chan.getMode() & mode))) {
			chan.toggleMode(mode);
		}
	}

	return true;
}	// updateServerMode


static bool
updateList(bool &add,
	std::map< std::string, ft_irc::Channel::mask_mode > &masks,
	const ft_irc::Parser::cmd_t *cmd,
	long unsigned int &pos,
	ft_irc::Channel::channel_mode maskValue)
{
	// Look for existing masks
	for (ft_irc::Channel::mask_iterator it = masks.begin(); it != masks.end(); it++) {
		if ((it->first == cmd->args[pos]) && ((!add == !(it->second & maskValue)))) {
			// Already Banned
			pos++;

			return false;
		}
		if ((it->first == cmd->args[pos])) {
			// Add mask
			it->second ^= maskValue;// toggle bit
			if (!it->second) {
				// Remove if no mask is left
				masks.erase(it);
			}
			pos++;

			return true;
		}
	}

	if (!add) {
		// can't remove mask that doesn't exist
		return false;
	}

	std::pair< std::string, ft_irc::Channel::mask_mode > newPair;

	newPair.first = cmd->args[pos];
	newPair.second = maskValue;
	masks.insert(newPair);
	pos++;

	return true;
}	// updateBanStatus


static bool
updateChannelList(ft_irc::Client &client,
	bool &add,
	ft_irc::Channel::channel_mode &listProc,
	ft_irc::Channel &chan,
	const ft_irc::Parser::cmd_t *cmd,
	long unsigned int &pos,
	ft_irc::Channel::channel_mode maskValue)
{
	std::map< std::string, ft_irc::Channel::mask_mode > &masks = chan.getMasks();

	if (listProc & maskValue) {
		return false;
	}
	if (pos >= cmd->args.size()) {
		listProc |= maskValue;
		for (ft_irc::Channel::mask_iterator it = masks.begin(); it != masks.end(); it++) {
			if (it->second & maskValue) {
				client.sendMsg("367 " + client.getNickname() + " " + chan.getName() + " " + it->first);	// TODO: write ban message
			}
		}

		return false;
	}

	return updateList(add, masks, cmd, pos, maskValue);
}	// updateChannelLists


static bool
updateChannelLists(ft_irc::Client &client,
	char c,
	bool &add,
	ft_irc::Channel::channel_mode &listProc,
	ft_irc::Channel &chan,
	const ft_irc::Parser::cmd_t *cmd,
	long unsigned int &pos)
{
	ft_irc::Channel::channel_mode maskValue;

	switch (c) {
		case 'b': {
			maskValue = CH_BAN;
			break;
		}

		case 'e': {
			maskValue = CH_EXCEPTION;
			break;
		}

		case 'I': {
			maskValue = CH_INVITE_EXCEPTION;
			break;
		}

		default: {
			LOG_WARN("mode: 472 :is unknown mode char to me")
			client.sendMsg("472 :is unknown mode char to me");	// 472 - ERR_UNKNOWNMODE

			return false;
		}
	}	// switch

	return updateChannelList(client, add, listProc, chan, cmd, pos, maskValue);
}	// updateChannelLists


static void
sendResponse(ft_irc::Client &client,
	std::string added,
	std::string removed,
	std::list< std::pair< std::string,
	std::string > > listResponse)
{
	std::string response;
	std::string masks;

	if (added.size()) {
		response = added;
	}
	for (std::list< std::pair< std::string, std::string > >::iterator it = listResponse.begin();
		 it != listResponse.end();
		 it++)
	{
		if (it->first[0] == '+') {
			if (!response.size()) {
				response = "+";
			}
			response += it->first[1];
			masks += " " + it->second;
		}
	}
	if (removed.size()) {
		response += '-' + removed;
	}
	for (std::list< std::pair< std::string, std::string > >::iterator it = listResponse.begin();
		 it != listResponse.end();
		 it++)
	{
		if (it->first[0] == '-') {
			if (response.find("-") == std::string::npos) {
				response += "-";
			}
			response += it->first[1];
			masks += " " + it->second;
		}
	}
	response += " " + masks;
	if (response.size()) {
		client.sendMsg("MODE " + response);
	}
}	// sendResponse


static void
modeChannel(ft_irc::Client &client,
	const ft_irc::Parser::cmd_t *cmd,
	std::map< std::string,
	ft_irc::Channel* > channels)
{
	ft_irc::Channel *chan = NULL;

	// Channel exists check
	for (std::map< std::string, ft_irc::Channel* >::const_iterator it = channels.begin();
		 it != channels.end() && !chan;
		 it++)
	{
		if (it->second->getName() == cmd->args[0]) {
			chan = it->second;
		}
	}
	if (!chan) {
		LOG_WARN("mode: 403: No such channel")
		client.sendMsg("403");	// 401 - ERR_NOSUCHNICK

		return;
	}

	// get channel mode
	if (cmd->args.size() == 1) {
		ft_irc::Channel::channel_mode mmode = chan->getMode();
		std::string smode = "+";

		smode += ((mmode & CH_INVITE_ONLY) ? "i" : "");
		smode += ((mmode & CH_MODERATE) ? "m" : "");
		smode += ((mmode & CH_SECRET) ? "s" : "");
		smode += ((mmode & CH_PROTECTED_TOPIC) ? "t" : "");
		smode += ((mmode & CH_NOT_EXTERNAL_MSGS) ? "n" : "");
		LOG_INFO("mode: 324: " + smode)
		client.sendMsg("324 " + client.getNickname() + " " + chan->getName() + " :" + smode);	// 221 - RPL_UMODEIS

		return;
	}

	if (!(client.getMode() & (CH_OPERATOR | CH_HALFOP | CH_FOUNDER))) {
		LOG_WARN("mode: 482: :You're not channel operator")
		client.sendMsg("482: You're not channel operator");	// 482 - ERR_CHANOPRIVSNEEDED

		return;
	}

	bool add = (cmd->args[1][0] != '-');// default to add if no sign is specified
	std::string added, removed;
	std::list< std::pair< std::string, std::string > > listResponse;
	ft_irc::Channel::channel_mode listsSent = 0;
	long unsigned int pos = 2;

	for (long unsigned int i = 0; i < cmd->args[1].size(); i++) {
		// Parse type D
		if ((std::string("+-imstn").find(cmd->args[1][i]) != std::string::npos)) {
			if (updateServerMode(client, *chan, cmd->args[1][i], add)) {
				updatedResponse(added, removed, cmd->args[1][i], add);
			}
		} else if ((std::string("beI").find(cmd->args[1][i]) != std::string::npos)) {
			// Parse A
			if (updateChannelLists(client, cmd->args[1][i], add, listsSent, *chan, cmd, pos)) {
				updatedListResponse(listResponse, cmd->args[1][i], add, cmd->args[pos - 1]);
			}
		} else {
			LOG_WARN("mode: 472 :is unknown mode char to me")
			client.sendMsg("472 :is unknown mode char to me");	// 472 - ERR_UNKNOWNMODE
		}
	}

	sendResponse(client, added, removed, listResponse);
}	// modeChannel


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
	} else {
		// Target is a channel
		modeChannel(client, cmd, this->_channels);
	}
}	// Server::mode
