#include <ctime>
#include <iostream>
#include <string>

#include "codes.hpp"

static std::string
rpl_welcome(const std::string &networkname, const std::string &nick)
{
	return ":Welcome to the " + networkname + " Network, " + nick;
}	// RPL_WELCOME


static std::string
rpl_yourhost(const std::string &servername, const std::string &version)
{
	return ":Your host is " + servername + ", running version " + version;
}	// RPL_YOURHOST


static std::string
rpl_created(const std::string &datetime)
{
	return ":This server was created " + datetime;
}	// RPL_CREATE


static std::string
rpl_myinfo(const std::string &servername,
	const std::string &version,
	const std::string &user_modes,
	const std::string &channel_modes)
{
	return servername + " " + version + " " + user_modes + " " + channel_modes;
}	// RPL_MYINFO


static std::string
rpl_info(const std::string &info)
{
	return ":" + info;
}	// RPL_BOUNCE


static std::string
rpl_luserclient(const std::string &u, const std::string &i, const std::string &s)
{
	return ":There are " + u + " users and " + i + " invisible on " + s + " servers";
}	// RPL_LUSERCLIENT


static std::string
rpl_luserop(const std::string &ops)
{
	return ops + " :operator(s) online";
}	// RPL_LUSEROP


static std::string
rpl_luserunknown(const std::string &connections)
{
	return connections + " :unknown connection(s)";
}	// RPL_LUSERUNKNOWN


static std::string
rpl_luserchannels(const std::string &channels)
{
	return channels + " :channels formed";
}	// RPL_LUSERCHANNELS


static std::string
rpl_luserme(const std::string &c, const std::string &s)
{
	return ":I have " + c + " clients and " + s + " servers";
}	// RPL_LUSERME


static std::string
rpl_adminme(const std::string &server)
{
	return server + " :Administrative info";
}	// RPL_ADMINME


static std::string
rpl_tryagain(const std::string &command)
{
	return command + " :Please wait a while and try again.";
}	// RPL_TRYAGAIN


static std::string
rpl_localuser(const std::string &u, const std::string &m)
{
	return ":Current local users " + u + ", max" + m;
}	// RPL_LOCALUSERS


static std::string
rpl_globaluser(const std::string &u, const std::string &m)
{
	return ":Current local users " + u + ", max" + m;
}	// RPL_GLOBALUSERS


static std::string
rpl_whoiscertfp(const std::string &nick, const std::string &fingerprint)
{
	return nick + " :has certificate fingerprint " + fingerprint;
}	// RPL_WHOISCERTFP


static std::string
rpl_away(const std::string &nick, const std::string &msg)
{
	return nick + " :" + msg;
}	// RPL_AWAY


static std::string
rpl_userhost(const std::string &reply)
{
	return ":" + reply;
}	// RPL_USERHOST


static std::string
rpl_unaway(void)
{
	return ":You are no longer marked as being away";
}	// RPL_UNAWAY


static std::string
rpl_nowaway(void)
{
	return ":You have been marked as being away";
}	// RPL_NOWAWAY


static std::string
rpl_whoreply(const std::string &channel,
	const std::string &username,
	const std::string &host,
	const std::string &server,
	const std::string &nick,
	const std::string &flags,
	const std::string &realname)
{
	return channel + " " + username + " " + host + " " + server + " " + nick + " " + flags + " :" + "0 " + realname;
}	// RPL_WHOREPLY


static std::string
rpl_endofwho(const std::string &mask)
{
	return mask + " :End of WHO list";
}	// RPL_ENDOFWHO


static std::string
rpl_whoisregnick(const std::string &nick)
{
	return nick + " :has identified for this nick";
}	// RPL_WHOISREGNICK


static std::string
rpl_whoisuser(const std::string &nick, std::string username, std::string host, std::string realname)
{
	return nick + " " + username + " " + host + " * :" + realname;
}	// RPL_WHOISUSER


static std::string
rpl_whoisserver(const std::string &nick, const std::string &server, const std::string &server_info)
{
	return nick + " " + server + " :" + server_info;
}	// RPL_WHOISSERVER


static std::string
rpl_whoisoperator(const std::string &nick)
{
	return nick + " :is an IRC operator";
}	// RPL_WHOISOPERATOR


static std::string
rpl_whowasuser(const std::string &nick,
	const std::string &username,
	const std::string &host,
	const std::string &realname)
{
	return nick + " " + username + " " + host + " * :" + realname;
}	// RPL_WHOWASUSER


static std::string
rpl_whoisidle(const std::string &nick, const std::string &secs, const std::string &signon)
{
	return nick + " " + secs + " " + signon + " :seconds idle, signon time";
}	// RPL_WHOISIDLE


static std::string
rpl_endofwhois(const std::string &nick)
{
	return nick + " :End of /WHOIS list";
}	// RPL_ENDOFWHOIS


static std::string
rpl_whoischannels(const std::string &nick, const std::string &prefix, const std::string &channel)
{
	return nick + " :" + prefix + channel;
}	// RPL_WHOISCHANNELS


static std::string
rpl_whoisspecial(const std::string &nick, const std::string &info)
{
	return nick + " :" + info;
}	// RPL_WHOISSPECIAL


static std::string
rpl_liststart(void)
{
	return "Channel :Users  Name";
}	// RPL_LISTSTART


static std::string
rpl_list(const std::string &channel, const std::string &client_count, const std::string &topic)
{
	return channel + " " + client_count + " :" + topic;
}	// RPL_LIST


static std::string
rpl_listend(void)
{
	return ":End of /LIST";
}	// RPL_LISTEND


static std::string
rpl_channelmodeis(const std::string &channel, const std::string &modestring, const std::string &mode_arg)
{
	return channel + " " + modestring + " " + mode_arg;
}	// RPL_CHANNELMODEIS


static std::string
rpl_createontime(const std::string &channel, const std::string &creationtime)
{
	return channel + " " + creationtime;
}	// RPL_CREATIONTIME


static std::string
rpl_whoisaccount(const std::string &nick, const std::string &account)
{
	return nick + " " + account + " :is logged in as";
}	// RPL_WHOISACCOUNT


static std::string
rpl_notopic(const std::string &channel)
{
	return channel + " :No topic is set";
}	// RPL_NOTOPIC


static std::string
rpl_topic(const std::string &channel, const std::string &topic)
{
	return channel + " :" + topic;
}	// RPL_TOPIC


static std::string
rpl_topicwhotime(const std::string &channel, const std::string &nick, const std::string &setat)
{
	return channel + " " + nick + " " + setat;
}	// RPL_TOPICWHOTIME


static std::string
rpl_endofinvitelist(void)
{
	return ":End of /INVITE list";
}	// RPL_ENDOFINVITELIST


static std::string
rpl_whoisactually(const std::string &nick,
	const std::string &ip,
	const std::string &hostname,
	const std::string &username)
{
	return nick + " " + username + "@" + hostname + " " + ip + " :Is actually using host";
}	// RPL_WHOISACTUALLY


static std::string
rpl_inviting(const std::string &nick, const std::string &channel)
{
	return nick + " " + channel;
}	// RPL_INVITING


static std::string
rpl_invexlist(const std::string &channel, const std::string &mask)
{
	return channel + " " + mask;
}	// RPL_INVEXLIST


static std::string
rpl_endofinvexlist(const std::string &channel)
{
	return channel + " :End of Channel Invite Exception List";
}	// RPL_ENDOFINVEXLIST


static std::string
rpl_endofexceptlist(const std::string &channel)
{
	return channel + " :End of channel exception list";
}	// RPL_ENDOFEXCEPTLIST


static std::string
rpl_version(const std::string &version, const std::string &server, const std::string &comments)
{
	return version + " " + server + " :" + comments;
}	// RPL_VERSION


static std::string
rpl_namereply(const std::string &symbol, const std::string &channel, const std::string &prefix, const std::string &nick)
{
	return symbol + " " + channel + " :" + prefix + nick;
}	// RPL_NAMREPLY


static std::string
rpl_endofnames(const std::string &channel)
{
	return channel + " :End of /NAMES list";
}	// RPL_ENDOFNAMES


static std::string
rpl_links(const std::string &server, const std::string &hopcount, const std::string &server_info)
{
	return "* " + server + " :" + hopcount + " " + server_info;
}	// RPL_LINKS


static std::string
rpl_endoflinks(void)
{
	return "* :End of /LINKS list";
}	// RPL_ENDOFLINKS


static std::string
rpl_banlist(const std::string &channel, const std::string &mask, const std::string &who, const std::string &set_ts)
{
	return channel + " " + mask + " " + who + " " + set_ts;
}	// RPL_BANLIST


static std::string
rpl_endofbanlist(const std::string &channel)
{
	return channel + " :End of channel ban list";
}	// RPL_ENDOFBANLIST


static std::string
rpl_endofwhowas(const std::string &nick)
{
	return nick + " :End of WHOWAS";
}	// RPL_ENDOFWHOWAS


static std::string
rpl_endofinfo(void)
{
	return ":End of INFO list";
}	// RPL_ENDOFINFO


static std::string
rpl_motdstart(const std::string &server)
{
	return ":- " + server + " Message of the day - ";
}	// RPL_MOTDSTART


static std::string
rpl_motd(const std::string &line)
{
	return ":" + line;
}	// RPL_MOTD


static std::string
rpl_endofmotd(void)
{
	return ":End of /MOTD command.";
}	// RPL_ENDOFMOTD


static std::string
rpl_whoishost(const std::string &nick, const std::string &host)
{
	return nick + " :is connecting from *@" + host;
}	// RPL_WHOISHOST


static std::string
rpl_whoismodes(const std::string &nick, const std::string &modestring)
{
	return nick + " :is using modes " + modestring;
}	// RPL_WHOISMODES


static std::string
rpl_youreoper(void)
{
	return ":You are now an IRC operator";
}	// RPL_YOUREOPER


static std::string
rpl_rehashing(const std::string &conf_file)
{
	return conf_file + " :Rehashing";
}	// RPL_REHASHING


static std::string
rpl_time(const std::string &server, const std::string &timestamp, const std::string &ts_offset, const std::string &time)
{
	return server + " " + timestamp + " " + ts_offset + " :" + time;
}	// RPL_TIME


static std::string
err_unknownerror(const std::string &command, const std::string &subcommand, const std::string &info)
{
	return command + " " + subcommand + " :" + info;
}	// ERR_UNKNOWNERROR


static std::string
err_nosuchnick(const std::string &nickname)
{
	return nickname + " :No such nick/channel";
}	// ERR_NOSUCHNICK


static std::string
err_nosuchserver(const std::string &server_name)
{
	return server_name + " :No such server";
}	// ERR_NOSUCHSERVER


static std::string
err_nosuchchannel(const std::string &channel)
{
	return channel + " :No such channel";
}	// ERR_NOSUCHCHANNEL


static std::string
err_cannotsendtochan(const std::string &channel)
{
	return channel + " :Cannot send to channel";
}	// ERR_CANNOTSENDTOCHAN


static std::string
err_toomanychannels(const std::string &channel)
{
	return channel + " :You have joined too many channels";
}	// ERR_TOOMANYCHANNELS


static std::string
err_wasnosuchnick(void)
{
	return ":There was no such nickname";
}	// ERR_WASNOSUCHNICK


static std::string
err_noorigin(void)
{
	return ":No origin specified";
}	// ERR_NOORIGIN


static std::string
err_norecipient(const std::string &command)
{
	return ":No recipient given " + command;
}	// ERR_NOORIGIN


static std::string
err_notexttosend(void)
{
	return ":No text to send";
}	// ERR_NOORIGIN


static std::string
err_inputtoolong(void)
{
	return ":Input line was too long";
}	// ERR_INPUTTOOLONG


static std::string
err_unknowncommand(const std::string &command)
{
	return command + " :Unknown command";
}	// ERR_UNKNOWNCOMMAND


static std::string
err_nomotd(void)
{
	return ":MOTD File is missing";
}	// ERR_NOMOTD


static std::string
err_nonicknamegiven(void)
{
	return ":No nickname given";
}	// ERR_ERRONEUSNICKNAME


static std::string
err_erroneusnickname(const std::string &nick)
{
	return nick + " :Erroneus nickname";
}	// ERR_ERRONEUSNICKNAME


static std::string
err_nicknameinuse(const std::string &nick)
{
	return nick + " :Nickname is already in use";
}	// ERR_NICKNAMEINUSE


static std::string
err_usernotinchannel(const std::string &nick, const std::string &channel)
{
	return nick + " " + channel + " :They aren't on that channel";
}	// ERR_USERNOTINCHANNEL


static std::string
err_notonchannel(const std::string &channel)
{
	return channel + " :You're not on that channel";
}	// ERR_NOTONCHANNEL


static std::string
err_useronchannel(const std::string &nick, const std::string &channel)
{
	return nick + " " + channel + " :is already on channel";
}	// ERR_USERONCHANNEL


static std::string
err_notregistered(void)
{
	return ":You have not registered";
}	// ERR_NOTREGISTERED


static std::string
err_needmoreparams(const std::string &command)
{
	return command + " :Not enough parameters";
}	// ERR_NEEDMOREPARAMS


static std::string
err_alreadyregistered(void)
{
	return ":You may not reregister";
}	// ERR_ALREADYREGISTERED


static std::string
err_passwdmismatch(void)
{
	return ":Password incorrect";
}	// ERR_PASSWDMISMATCH


static std::string
err_yourebannedcreep(void)
{
	return ":You are banned from this server.";
}	// ERR_YOUREBANNEDCREEP


static std::string
err_channelisfull(const std::string &channel)
{
	return channel + " :Cannot join channel (+l)";
}	// ERR_CHANNELISFULL


static std::string
err_unknownmode(const std::string &modechar)
{
	return modechar + " :is unknown mode char to me";
}	// ERR_UNKNOWNMODE


static std::string
err_inviteonlychan(const std::string &channel)
{
	return channel + " :Cannot join channel (+i)";
}	// ERR_INVITEONLYCHAN


static std::string
err_bannedfromchan(const std::string &channel)
{
	return channel + " :Cannot join channel (+b)";
}	// ERR_BANNEDFROMCHAN


static std::string
err_badchannelkey(const std::string &channel)
{
	return channel + " :Cannot join channel (+k)";
}	// ERR_BADCHANNELKEY


static std::string
err_badchanmask(const std::string &channel)
{
	return channel + " :Bad Channel Mask";
}	// ERR_BADCHANMASK


static std::string
err_noprivileges(void)
{
	return ":Permission Denied- You're not an IRC operator";
}	// ERR_NOPRIVILEGES


static std::string
err_chanoprivsneeded(const std::string &channel)
{
	return channel + " :You're not channel operator";
}	// ERR_CHANOPRIVSNEEDED


static std::string
err_cantkillserver(void)
{
	return ":You cant kill a server!";
}	// ERR_CANTKILLSERVER


static std::string
err_nooperhost(void)
{
	return +" :No O-lines for your host";
}	// ERR_NOOPERHOST


static std::string
err_umodeunknownflag(void)
{
	return ":Unknown MODE flag";
}	// ERR_UMODEUNKNOWNFLAG


static std::string
err_usersdontmatch(void)
{
	return ":Cant change mode for other users";
}	// ERR_USERSDONTMATCH


static std::string
err_helpnotfound(const std::string &subject)
{
	return subject + " :No help available on this topic";
}	// ERR_HELPNOTFOUND


static std::string
err_invalidkey(const std::string &target_chan)
{
	return target_chan + " :Key is not well-formed";
}	// ERR_INVALIDKEY


static std::string
rpl_starttls(void)
{
	return ":STARTTLS successful, proceed with TLS handshake";
}	// RPL_STARTTLS


static std::string
rpl_whoissecure(const std::string &nick)
{
	return nick + " :is using a secure connection";
}	// RPL_WHOISSECURE


static std::string
err_starttls(void)
{
	return ":STARTTLS failed (Wrong moon phase)";
}	// ERR_STARTTLS


static std::string
err_invalidmodeparam(const std::string &target,
	const std::string &modechar,
	const std::string &parameter,
	const std::string &description)
{
	return target + " " + modechar + " " + parameter + " :" + description;
}	// ERR_INVALIDMODEPARAM


static std::string
rpl_helpline(const std::string &subject, const std::string &line)
{
	return subject + " :" + line;
}	// RPL_HELPSTART


static std::string
err_noprivs(const std::string &priv)
{
	return priv + " :Insufficient oper privileges.";
}	// ERR_NOPRIVS


static std::string
rpl_loggedin(const std::string &nick,
	const std::string &user,
	const std::string &host,
	const std::string &account,
	const std::string &username)
{
	return nick + "!" + user + "@" + host + " " + account + " :You are now logged in as " + username;
}	// RPL_LOGGEDIN


static std::string
rpl_loggedout(const std::string &nick, const std::string &user, const std::string &host)
{
	return nick + "!" + user + "@" + host + " :You are now logged out";
}	// RPL_LOGGEDOUT


static std::string
err_nicklocked(void)
{
	return ":You must use a nick assigned to you";
}	// ERR_NICKLOCKED


static std::string
rpl_saslsuccess(void)
{
	return ":SASL authentication successful";
}	// RPL_SASLSUCCESS


static std::string
err_saslfail(void)
{
	return ":SASL authentication failed";
}	// ERR_SASLFAIL


static std::string
err_sasltoolong(void)
{
	return ":SASL message too long";
}	// ERR_SASLTOOLONG


static std::string
err_saslaborted(void)
{
	return ":SASL authentication aborted";
}	// ERR_SASLABORTED


static std::string
err_saslalready(void)
{
	return ":You have already authenticated using SASL";
}	// ERR_SASLALREADY


static std::string
rpl_saslmechs(const std::string &mechanisms)
{
	return mechanisms + " :are available SASL mechanisms";
}	// RPL_SASLMECHS


std::string
ft_irc::getReply(ft_irc::codes code,
	std::string source,
	const std::string arg1,
	const std::string arg2,
	const std::string arg3,
	const std::string arg4,
	const std::string arg5,
	const std::string arg6,
	const std::string arg7)
{
	if (source.empty()) {
		source = "*";
	}
	source += " ";
	switch (code) {
		case ft_irc::RPL_WELCOME: {
			return SSTR(code) + " " + source + rpl_welcome(arg1, arg2);
		}

		case ft_irc::RPL_YOURHOST: {
			return SSTR(code) + " " + source + rpl_yourhost(arg1, arg2);
		}

		case ft_irc::RPL_CREATED: {
			return SSTR(code) + " " + source + rpl_created(arg1);
		}

		case ft_irc::RPL_MYINFO: {
			return SSTR(code) + " " + source + rpl_myinfo(arg1, arg2, arg3, arg4);
		}

		case ft_irc::RPL_ISUPPORT: {
			return SSTR(code);
		}

		case ft_irc::RPL_BOUNCE: {
			return SSTR(code) + " " + source + rpl_info(arg1);
		}

		case ft_irc::RPL_UMODEIS: {
			return SSTR(code) + " " + source + arg1;
		}

		case ft_irc::RPL_LUSERCLIENT: {
			return SSTR(code) + " " + source + rpl_luserclient(arg1, arg2, arg3);
		}

		case ft_irc::RPL_LUSEROP: {
			return SSTR(code) + " " + source + rpl_luserop(arg1);
		}

		case ft_irc::RPL_LUSERUNKNOWN: {
			return SSTR(code) + " " + source + rpl_luserunknown(arg1);
		}

		case ft_irc::RPL_LUSERCHANNELS: {
			return SSTR(code) + " " + source + rpl_luserchannels(arg1);
		}

		case ft_irc::RPL_LUSERME: {
			return SSTR(code) + " " + source + rpl_luserme(arg1, arg2);
		}

		case ft_irc::RPL_ADMINME: {
			return SSTR(code) + " " + source + rpl_adminme(arg1);
		}

		case ft_irc::RPL_ADMINLOC1: {
			return SSTR(code) + " " + source + rpl_info(arg1);
		}

		case ft_irc::RPL_ADMINLOC2: {
			return SSTR(code) + " " + source + rpl_info(arg1);
		}

		case ft_irc::RPL_ADMINEMAIL: {
			return SSTR(code) + " " + source + rpl_info(arg1);
		}

		case ft_irc::RPL_TRYAGAIN: {
			return SSTR(code) + " " + source + rpl_tryagain(arg1);
		}

		case ft_irc::RPL_LOCALUSERS: {
			return SSTR(code) + " " + source + rpl_localuser(arg1, arg2);
		}

		case ft_irc::RPL_GLOBALUSERS: {
			return SSTR(code) + " " + source + rpl_globaluser(arg1, arg2);
		}

		case ft_irc::RPL_WHOISCERTFP: {
			return SSTR(code) + " " + source + rpl_whoiscertfp(arg1, arg2);
		}

		case ft_irc::RPL_NONE: {
			return SSTR(code << " :");
		}

		case ft_irc::RPL_AWAY: {
			return SSTR(code) + " " + source + rpl_away(arg1, arg2);
		}

		case ft_irc::RPL_USERHOST: {
			return SSTR(code) + " " + source + rpl_userhost(arg1);
		}

		case ft_irc::RPL_UNAWAY: {
			return SSTR(code) + " " + source + rpl_unaway();
		}

		case ft_irc::RPL_NOWAWAY: {
			return SSTR(code) + " " + source + rpl_nowaway();
		}

		case ft_irc::RPL_WHOREPLY: {
			return SSTR(code) + " " + source + rpl_whoreply(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		}

		case ft_irc::RPL_ENDOFWHO: {
			return SSTR(code) + " " + source + rpl_endofwho(arg1);
		}

		case ft_irc::RPL_WHOISREGNICK: {
			return SSTR(code) + " " + source + rpl_whoisregnick(arg1);
		}

		case ft_irc::RPL_WHOISUSER: {
			return SSTR(code) + " " + source + rpl_whoisuser(arg1, arg2, arg3, arg4);
		}

		case ft_irc::RPL_WHOISSERVER: {
			return SSTR(code) + " " + source + rpl_whoisserver(arg1, arg2, arg3);
		}

		case ft_irc::RPL_WHOISOPERATOR: {
			return SSTR(code) + " " + source + rpl_whoisoperator(arg1);
		}

		case ft_irc::RPL_WHOWASUSER: {
			return SSTR(code) + " " + source + rpl_whowasuser(arg1, arg2, arg3, arg4);
		}

		case ft_irc::RPL_WHOISIDLE: {
			return SSTR(code) + " " + source + rpl_whoisidle(arg1, arg2, arg3);
		}

		case ft_irc::RPL_ENDOFWHOIS: {
			return SSTR(code) + " " + source + rpl_endofwhois(arg1);
		}

		case ft_irc::RPL_WHOISCHANNELS: {
			return SSTR(code) + " " + source + rpl_whoischannels(arg1, arg2, arg3);
		}

		case ft_irc::RPL_WHOISSPECIAL: {
			return SSTR(code) + " " + source + rpl_whoisspecial(arg1, arg2);
		}

		case ft_irc::RPL_LISTSTART: {
			return SSTR(code) + " " + source + rpl_liststart();
		}

		case ft_irc::RPL_LIST: {
			return SSTR(code) + " " + source + rpl_list(arg1, arg2, arg3);
		}

		case ft_irc::RPL_LISTEND: {
			return SSTR(code) + " " + source + rpl_listend();
		}

		case ft_irc::RPL_CHANNELMODEIS: {
			return SSTR(code) + " " + source + rpl_channelmodeis(arg1, arg2, arg3);
		}

		case ft_irc::RPL_CREATIONTIME: {
			return SSTR(code) + " " + source + rpl_createontime(arg1, arg2);
		}

		case ft_irc::RPL_WHOISACCOUNT: {
			return SSTR(code) + " " + source + rpl_whoisaccount(arg1, arg2);
		}

		case ft_irc::RPL_NOTOPIC: {
			return SSTR(code) + " " + source + rpl_notopic(arg1);
		}

		case ft_irc::RPL_TOPIC: {
			return SSTR(code) + " " + source + rpl_topic(arg1, arg2);
		}

		case ft_irc::RPL_TOPICWHOTIME: {
			return SSTR(code) + " " + source + rpl_topicwhotime(arg1, arg2, arg3);
		}

		case ft_irc::RPL_INVITELIST: {
			return SSTR(code) + " " + source + arg1;
		}

		case ft_irc::RPL_ENDOFINVITELIST: {
			return SSTR(code) + " " + source + rpl_endofinvitelist();
		}

		case ft_irc::RPL_WHOISACTUALLY: {
			return SSTR(code) + " " + source + rpl_whoisactually(arg1, arg2, arg3, arg4);
		}

		case ft_irc::RPL_INVITING: {
			return SSTR(code) + " " + source + rpl_inviting(arg1, arg2);
		}

		case ft_irc::RPL_INVEXLIST: {
			return SSTR(code) + " " + source + rpl_invexlist(arg1, arg2);
		}

		case ft_irc::RPL_ENDOFINVEXLIST: {
			return SSTR(code) + " " + source + rpl_endofinvexlist(arg1);
		}

		case ft_irc::RPL_EXCEPTLIST: {
			return SSTR(code) + " " + source + arg1 + " " + arg2;
		}

		case ft_irc::RPL_ENDOFEXCEPTLIST: {
			return SSTR(code) + " " + source + rpl_endofexceptlist(arg1);
		}

		case ft_irc::RPL_VERSION: {
			return SSTR(code) + " " + source + rpl_version(arg1, arg2, arg3);
		}

		case ft_irc::RPL_NAMREPLY: {
			return SSTR(code) + " " + source + rpl_namereply(arg1, arg2, arg3, arg4);
		}

		case ft_irc::RPL_ENDOFNAMES: {
			return SSTR(code) + " " + source + rpl_endofnames(arg1);
		}

		case ft_irc::RPL_LINKS: {
			return SSTR(code) + " " + source + rpl_links(arg1, arg2, arg3);
		}

		case ft_irc::RPL_ENDOFLINKS: {
			return SSTR(code) + " " + source + rpl_endoflinks();
		}

		case ft_irc::RPL_BANLIST: {
			return SSTR(code) + " " + source + rpl_banlist(arg1, arg2, arg3, arg4);
		}

		case ft_irc::RPL_ENDOFBANLIST: {
			return SSTR(code) + " " + source + rpl_endofbanlist(arg1);
		}

		case ft_irc::RPL_ENDOFWHOWAS: {
			return SSTR(code) + " " + source + rpl_endofwhowas(arg1);
		}

		case ft_irc::RPL_INFO: {
			return SSTR(code) + " " + source + rpl_info(arg1);
		}

		case ft_irc::RPL_ENDOFINFO: {
			return SSTR(code) + " " + source + rpl_endofinfo();
		}

		case ft_irc::RPL_MOTDSTART: {
			return SSTR(code) + " " + source + rpl_motdstart(arg1);
		}

		case ft_irc::RPL_MOTD: {
			return SSTR(code) + " " + source + rpl_motd(arg1);
		}

		case ft_irc::RPL_ENDOFMOTD: {
			return SSTR(code) + " " + source + rpl_endofmotd();
		}

		case ft_irc::RPL_WHOISHOST: {
			return SSTR(code) + " " + source + rpl_whoishost(arg1, arg2);
		}

		case ft_irc::RPL_WHOISMODES: {
			return SSTR(code) + " " + source + rpl_whoismodes(arg1, arg2);
		}

		case ft_irc::RPL_YOUREOPER: {
			return SSTR(code) + " " + source + rpl_youreoper();
		}

		case ft_irc::RPL_REHASHING: {
			return SSTR(code) + " " + source + rpl_rehashing(arg1);
		}

		case ft_irc::RPL_TIME: {
			return SSTR(code) + " " + source + rpl_time(arg1, arg2, arg3, arg4);
		}

		case ft_irc::ERR_UNKNOWNERROR: {
			return SSTR(code) + " " + source + err_unknownerror(arg1, arg2, arg3);
		}

		case ft_irc::ERR_NOSUCHNICK: {
			return SSTR(code) + " " + source + err_nosuchnick(arg1);
		}

		case ft_irc::ERR_NOSUCHSERVER: {
			return SSTR(code) + " " + source + err_nosuchserver(arg1);
		}

		case ft_irc::ERR_NOSUCHCHANNEL: {
			return SSTR(code) + " " + source + err_nosuchchannel(arg1);
		}

		case ft_irc::ERR_CANNOTSENDTOCHAN: {
			return SSTR(code) + " " + source + err_cannotsendtochan(arg1);
		}

		case ft_irc::ERR_TOOMANYCHANNELS: {
			return SSTR(code) + " " + source + err_toomanychannels(arg1);
		}

		case ft_irc::ERR_WASNOSUCHNICK: {
			return SSTR(code) + " " + source + err_wasnosuchnick();
		}

		case ft_irc::ERR_NOORIGIN: {
			return SSTR(code) + " " + source + err_noorigin();
		}

		case ft_irc::ERR_NORECIPIENT: {
			return SSTR(code) + " " + source + err_norecipient(arg1);
		}

		case ft_irc::ERR_NOTEXTTOSEND: {
			return SSTR(code) + " " + source + err_notexttosend();
		}

		case ft_irc::ERR_INPUTTOOLONG: {
			return SSTR(code) + " " + source + err_inputtoolong();
		}

		case ft_irc::ERR_UNKNOWNCOMMAND: {
			return SSTR(code) + " " + source + err_unknowncommand(arg1);
		}

		case ft_irc::ERR_NOMOTD: {
			return SSTR(code) + " " + source + err_nomotd();
		}

		case ft_irc::ERR_NONICKNAMEGIVEN: {
			return SSTR(code) + " " + source + err_nonicknamegiven();
		}

		case ft_irc::ERR_ERRONEUSNICKNAME: {
			return SSTR(code) + " " + source + err_erroneusnickname(arg1);
		}

		case ft_irc::ERR_NICKNAMEINUSE: {
			return SSTR(code) + " " + source + err_nicknameinuse(arg1);
		}

		case ft_irc::ERR_USERNOTINCHANNEL: {
			return SSTR(code) + " " + source + err_usernotinchannel(arg1, arg2);
		}

		case ft_irc::ERR_NOTONCHANNEL: {
			return SSTR(code) + " " + source + err_notonchannel(arg1);
		}

		case ft_irc::ERR_USERONCHANNEL: {
			return SSTR(code) + " " + source + err_useronchannel(arg1, arg2);
		}

		case ft_irc::ERR_NOTREGISTERED: {
			return SSTR(code) + " " + source + err_notregistered();
		}

		case ft_irc::ERR_NEEDMOREPARAMS: {
			return SSTR(code) + " " + source + err_needmoreparams(arg1);
		}

		case ft_irc::ERR_ALREADYREGISTERED: {
			return SSTR(code) + " " + source + err_alreadyregistered();
		}

		case ft_irc::ERR_PASSWDMISMATCH: {
			return SSTR(code) + " " + source + err_passwdmismatch();
		}

		case ft_irc::ERR_YOUREBANNEDCREEP: {
			return SSTR(code) + " " + source + err_yourebannedcreep();
		}

		case ft_irc::ERR_CHANNELISFULL: {
			return SSTR(code) + " " + source + err_channelisfull(arg1);
		}

		case ft_irc::ERR_UNKNOWNMODE: {
			return SSTR(code) + " " + source + err_unknownmode(arg1);
		}

		case ft_irc::ERR_INVITEONLYCHAN: {
			return SSTR(code) + " " + source + err_inviteonlychan(arg1);
		}

		case ft_irc::ERR_BANNEDFROMCHAN: {
			return SSTR(code) + " " + source + err_bannedfromchan(arg1);
		}

		case ft_irc::ERR_BADCHANNELKEY: {
			return SSTR(code) + " " + source + err_badchannelkey(arg1);
		}

		case ft_irc::ERR_BADCHANMASK: {
			return SSTR(code) + " " + source + err_badchanmask(arg1);
		}

		case ft_irc::ERR_NOPRIVILEGES: {
			return SSTR(code) + " " + source + err_noprivileges();
		}

		case ft_irc::ERR_CHANOPRIVSNEEDED: {
			return SSTR(code) + " " + source + err_chanoprivsneeded(arg1);
		}

		case ft_irc::ERR_CANTKILLSERVER: {
			return SSTR(code) + " " + source + err_cantkillserver();
		}

		case ft_irc::ERR_NOOPERHOST: {
			return SSTR(code) + " " + source + err_nooperhost();
		}

		case ft_irc::ERR_UMODEUNKNOWNFLAG: {
			return SSTR(code) + " " + source + err_umodeunknownflag();
		}

		case ft_irc::ERR_USERSDONTMATCH: {
			return SSTR(code) + " " + source + err_usersdontmatch();
		}

		case ft_irc::ERR_HELPNOTFOUND: {
			return SSTR(code) + " " + source + err_helpnotfound(arg1);
		}

		case ft_irc::ERR_INVALIDKEY: {
			return SSTR(code) + " " + source + err_invalidkey(arg1);
		}

		case ft_irc::RPL_STARTTLS: {
			return SSTR(code) + " " + source + rpl_starttls();
		}

		case ft_irc::RPL_WHOISSECURE: {
			return SSTR(code) + " " + source + rpl_whoissecure(arg1);
		}

		case ft_irc::ERR_STARTTLS: {
			return SSTR(code) + " " + source + err_starttls();
		}

		case ft_irc::ERR_INVALIDMODEPARAM: {
			return SSTR(code) + " " + source + err_invalidmodeparam(arg1, arg2, arg3, arg4);
		}

		case ft_irc::RPL_HELPSTART: {
			return SSTR(code) + " " + source + rpl_helpline(arg1, arg2);
		}

		case ft_irc::RPL_HELPTXT: {
			return SSTR(code) + " " + source + rpl_helpline(arg1, arg2);
		}

		case ft_irc::RPL_ENDOFHELP: {
			return SSTR(code) + " " + source + rpl_helpline(arg1, arg2);
		}

		case ft_irc::ERR_NOPRIVS: {
			return SSTR(code) + " " + source + err_noprivs(arg1);
		}

		case ft_irc::RPL_LOGGEDIN: {
			return SSTR(code) + " " + source + rpl_loggedin(arg1, arg2, arg3, arg4, arg5);
		}

		case ft_irc::RPL_LOGGEDOUT: {
			return SSTR(code) + " " + source + rpl_loggedout(arg1, arg2, arg3);
		}

		case ft_irc::ERR_NICKLOCKED: {
			return SSTR(code) + " " + source + err_nicklocked();
		}

		case ft_irc::RPL_SASLSUCCESS: {
			return SSTR(code) + " " + source + rpl_saslsuccess();
		}

		case ft_irc::ERR_SASLFAIL: {
			return SSTR(code) + " " + source + err_saslfail();
		}

		case ft_irc::ERR_SASLTOOLONG: {
			return SSTR(code) + " " + source + err_sasltoolong();
		}

		case ft_irc::ERR_SASLABORTED: {
			return SSTR(code) + " " + source + err_saslaborted();
		}

		case ft_irc::ERR_SASLALREADY: {
			return SSTR(code) + " " + source + err_saslalready();
		}

		case ft_irc::RPL_SASLMECHS: {
			return SSTR(code) + " " + source + rpl_saslmechs(arg1);
		}

		default: {
			return "";
		}
	}	// switch
}	// ft_irc::getReply
