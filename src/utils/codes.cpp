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


ft_irc::commands
ft_irc::commandFromString(const std::string &cmd)
{
	if (cmd == "CAP") {
		return ft_irc::CMD_CAP;
	}
	if (cmd == "AUTHENTICATE") {
		return ft_irc::CMD_AUTHENTICATE;
	}
	if (cmd == "PASS") {
		return ft_irc::CMD_PASS;
	}
	if (cmd == "NICK") {
		return ft_irc::CMD_NICK;
	}
	if (cmd == "USER") {
		return ft_irc::CMD_USER;
	}
	if (cmd == "PING") {
		return ft_irc::CMD_PING;
	}
	if (cmd == "PONG") {
		return ft_irc::CMD_PONG;
	}
	if (cmd == "OPER") {
		return ft_irc::CMD_OPER;
	}
	if (cmd == "QUIT") {
		return ft_irc::CMD_QUIT;
	}
	if (cmd == "ERROR") {
		return ft_irc::CMD_ERROR;
	}
	if (cmd == "JOIN") {
		return ft_irc::CMD_JOIN;
	}
	if (cmd == "PART") {
		return ft_irc::CMD_PART;
	}
	if (cmd == "TOPIC") {
		return ft_irc::CMD_TOPIC;
	}
	if (cmd == "NAMES") {
		return ft_irc::CMD_NAMES;
	}
	if (cmd == "LIST") {
		return ft_irc::CMD_LIST;
	}
	if (cmd == "INVITE") {
		return ft_irc::CMD_INVITE;
	}
	if (cmd == "KICK") {
		return ft_irc::CMD_KICK;
	}
	if (cmd == "MOTD") {
		return ft_irc::CMD_MOTD;
	}
	if (cmd == "VERSION") {
		return ft_irc::CMD_VERSION;
	}
	if (cmd == "ADMIN") {
		return ft_irc::CMD_ADMIN;
	}
	if (cmd == "CONNECT") {
		return ft_irc::CMD_CONNECT;
	}
	if (cmd == "LUSERS") {
		return ft_irc::CMD_LUSERS;
	}
	if (cmd == "TIME") {
		return ft_irc::CMD_TIME;
	}
	if (cmd == "STATS") {
		return ft_irc::CMD_STATS;
	}
	if (cmd == "HELP") {
		return ft_irc::CMD_HELP;
	}
	if (cmd == "INFO") {
		return ft_irc::CMD_INFO;
	}
	if (cmd == "MODE") {
		return ft_irc::CMD_MODE;
	}
	if (cmd == "PRIVMSG") {
		return ft_irc::CMD_PRIVMSG;
	}
	if (cmd == "NOTICE") {
		return ft_irc::CMD_NOTICE;
	}
	if (cmd == "WHO") {
		return ft_irc::CMD_WHO;
	}
	if (cmd == "WHOIS") {
		return ft_irc::CMD_WHOIS;
	}
	if (cmd == "WHOWAS") {
		return ft_irc::CMD_WHOWAS;
	}
	if (cmd == "KILL") {
		return ft_irc::CMD_KILL;
	}
	if (cmd == "REHASH") {
		return ft_irc::CMD_REHASH;
	}
	if (cmd == "RESTART") {
		return ft_irc::CMD_RESTART;
	}
	if (cmd == "SQUIT") {
		return ft_irc::CMD_SQUIT;
	}
	if (cmd == "AWAY") {
		return ft_irc::CMD_AWAY;
	}
	if (cmd == "LINKS") {
		return ft_irc::CMD_LINKS;
	}
	if (cmd == "USERHOST") {
		return ft_irc::CMD_USERHOST;
	}
	if (cmd == "WALLOPS") {
		return ft_irc::CMD_WALLOPS;
	}

	throw std::invalid_argument("Command given was not a valid command enum");
}	// toString
