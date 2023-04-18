#include <stdexcept>

#include "codes.hpp"

std::string
ft_irc::toString(ft_irc::commands cmd)
{
	switch (cmd) {
		case ft_irc::CMD_CAP: {
				return "CAP";
			}

		case ft_irc::CMD_AUTHENTICATE: {
				return "AUTHENTICATE";
			}

		case ft_irc::CMD_PASS: {
				return "PASS";
			}

		case ft_irc::CMD_NICK: {
				return "NICK";
			}

		case ft_irc::CMD_USER: {
				return "USER";
			}

		case ft_irc::CMD_PING: {
				return "PING";
			}

		case ft_irc::CMD_PONG: {
				return "PONG";
			}

		case ft_irc::CMD_OPER: {
				return "OPER";
			}

		case ft_irc::CMD_QUIT: {
				return "QUIT";
			}

		case ft_irc::CMD_ERROR: {
				return "ERROR";
			}

		case ft_irc::CMD_JOIN: {
				return "JOIN";
			}

		case ft_irc::CMD_PART: {
				return "PART";
			}

		case ft_irc::CMD_TOPIC: {
				return "TOPIC";
			}

		case ft_irc::CMD_NAMES: {
				return "NAMES";
			}

		case ft_irc::CMD_LIST: {
				return "LIST";
			}

		case ft_irc::CMD_INVITE: {
				return "INVITE";
			}

		case ft_irc::CMD_KICK: {
				return "KICK";
			}

		case ft_irc::CMD_MOTD: {
				return "MOTD";
			}

		case ft_irc::CMD_VERSION: {
				return "VERSION";
			}

		case ft_irc::CMD_ADMIN: {
				return "ADMIN";
			}

		case ft_irc::CMD_CONNECT: {
				return "CONNECT";
			}

		case ft_irc::CMD_LUSERS: {
				return "LUSERS";
			}

		case ft_irc::CMD_TIME: {
				return "TIME";
			}

		case ft_irc::CMD_STATS: {
				return "STATS";
			}

		case ft_irc::CMD_HELP: {
				return "HELP";
			}

		case ft_irc::CMD_INFO: {
				return "INFO";
			}

		case ft_irc::CMD_MODE: {
				return "MODE";
			}

		case ft_irc::CMD_PRIVMSG: {
				return "PRIVMSG";
			}

		case ft_irc::CMD_NOTICE: {
				return "NOTICE";
			}

		case ft_irc::CMD_WHO: {
				return "WHO";
			}

		case ft_irc::CMD_WHOIS: {
				return "WHOIS";
			}

		case ft_irc::CMD_WHOWAS: {
				return "WHOWAS";
			}

		case ft_irc::CMD_KILL: {
				return "KILL";
			}

		case ft_irc::CMD_REHASH: {
				return "REHASH";
			}

		case ft_irc::CMD_RESTART: {
				return "RESTART";
			}

		case ft_irc::CMD_SQUIT: {
				return "SQUIT";
			}

		case ft_irc::CMD_AWAY: {
				return "AWAY";
			}

		case ft_irc::CMD_LINKS: {
				return "LINKS";
			}

		case ft_irc::CMD_USERHOST: {
				return "USERHOST";
			}

		case ft_irc::CMD_WALLOPS: {
				return "WALLOPS";
			}

		default: {
				throw std::invalid_argument("Command given was not a valid command enum");
			}
	}	// switch
}	// toString
