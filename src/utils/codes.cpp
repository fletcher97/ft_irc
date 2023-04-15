#include "codes.hpp"

std::string
toString(ft_irc::commands cmd)
{
	switch (cmd) {
		case ft_irc::CAP: {
				return "CAP";
			}

		case ft_irc::AUTHENTICATE: {
				return "AUTHENTICATE";
			}

		case ft_irc::PASS: {
				return "PASS";
			}

		case ft_irc::NICK: {
				return "NICK";
			}

		case ft_irc::USER: {
				return "USER";
			}

		case ft_irc::PING: {
				return "PING";
			}

		case ft_irc::PONG: {
				return "PONG";
			}

		case ft_irc::OPER: {
				return "OPER";
			}

		case ft_irc::QUIT: {
				return "QUIT";
			}

		case ft_irc::ERROR: {
				return "ERROR";
			}

		case ft_irc::JOIN: {
				return "JOIN";
			}

		case ft_irc::PART: {
				return "PART";
			}

		case ft_irc::TOPIC: {
				return "TOPIC";
			}

		case ft_irc::NAMES: {
				return "NAMES";
			}

		case ft_irc::LIST: {
				return "LIST";
			}

		case ft_irc::INVITE: {
				return "INVITE";
			}

		case ft_irc::KICK: {
				return "KICK";
			}

		case ft_irc::MOTD: {
				return "MOTD";
			}

		case ft_irc::VERSION: {
				return "VERSION";
			}

		case ft_irc::ADMIN: {
				return "ADMIN";
			}

		case ft_irc::CONNECT: {
				return "CONNECT";
			}

		case ft_irc::LUSERS: {
				return "LUSERS";
			}

		case ft_irc::TIME: {
				return "TIME";
			}

		case ft_irc::STATS: {
				return "STATS";
			}

		case ft_irc::HELP: {
				return "HELP";
			}

		case ft_irc::INFO: {
				return "INFO";
			}

		case ft_irc::MODE: {
				return "MODE";
			}

		case ft_irc::PRIVMSG: {
				return "PRIVMSG";
			}

		case ft_irc::NOTICE: {
				return "NOTICE";
			}

		case ft_irc::WHO: {
				return "WHO";
			}

		case ft_irc::WHOIS: {
				return "WHOIS";
			}

		case ft_irc::WHOWAS: {
				return "WHOWAS";
			}

		case ft_irc::KILL: {
				return "KILL";
			}

		case ft_irc::REHASH: {
				return "REHASH";
			}

		case ft_irc::RESTART: {
				return "RESTART";
			}

		case ft_irc::SQUIT: {
				return "SQUIT";
			}

		case ft_irc::AWAY: {
				return "AWAY";
			}

		case ft_irc::LINKS: {
				return "LINKS";
			}

		case ft_irc::USERHOST: {
				return "USERHOST";
			}

		case ft_irc::WALLOPS: {
				return "WALLOPS";
			}
	}	// switch
}	// toString
