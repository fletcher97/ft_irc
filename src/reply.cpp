#include <iostream>
#include <string>
#include <ctime>

std::string RPL_WELCOME(std::string client, std::string networkname, std::string nick)
{
	return (client + " :Welcome to the " + networkname + " Network, " + nick); //[!<user>@<host>]
}

std::string RPL_YOURHOST(std::string client, std::string servername, std::string version)
{
	return (client + " :Your host is " + servername + ", running version " + version);
}

std::string RPL_CREATE(std::string client, std::string datetime)
{
	return (client + " :This server was created " + datetime);
}

std::string RPL_MYINFO(std::string client, std::string servername, std::string version, std::string user_modes, std::string channel_modes)
{
	return (client + " " + servername + " " + version + " " + user_modes + " " + channel_modes);
}

std::string RPL_ISUPPORT(std::string client)
{
	return (client + " :are supported by this server");
}

std::string RPL_BOUNCE(std::string client, std::string hostname, std::string port, std::string info)
{
	return (client + " " + hostname + " " + port + " :" + info);
}

std::string RPL_UMODEIS(std::string client, std::string user_modes)
{
	return (client + user_modes);
}

std::string RPL_LUSERCLIENT(std::string client, unsigned int u, unsigned int i, unsigned s)
{
	return (client + " :There are " + std::to_string(u) + " users and " + std::to_string(i) + " invisible on " + std::to_string(s) + " servers");
}

std::string RPL_LUSEROP(std::string client, int ops)
{
	return (client + " " + std::to_string(ops) + " :operator(s) online");
}

std::string RPL_LUSERUNKNOWN(std::string client, int connections)
{
	return (client + " " + std::to_string(connections) + " :unknown connection(s)");
}

std::string RPL_LUSERCHANNELS(std::string client, int channels)
{
	return (client + " " + std::to_string(channels) + " :channels formed");
}

std::string RPL_LUSERME(std::string client, int c, int s)
{
	return (client + " :I have " + std::to_string(c) + " clients and " + std::to_string(s) + " servers");
}

std::string RPL_ADMINME(std::string client, std::string server, int control)
{
	if (control == 0)
		return (client + " :Administrative info");
	else
		return (client + " " + server + " :Administrative info");
}

std::string RPL_ADMINLOC1(std::string client, std::string info)
{
	return (client + " :" + info);
}

std::string RPL_ADMINLOC2(std::string client, std::string info)
{
	return (client + " :" + info);
}

std::string RPL_ADMINEMAIL(std::string client, std::string info)
{
	return (client + " :" + info);
}

std::string RPL_TRYAGAIN(std::string client, std::string command)
{
	return (client + " " + command + " :Please wait a while and try again.");
}

std::string RPL_LOCALUSERS(std::string client, unsigned int u, unsigned int m)
{
	return (client + " :Current local users " + std::to_string(u) + ", max" + std::to_string(m));
}

std::string RPL_GLOBALUSERS(std::string client, unsigned int u, unsigned int m)
{
	return (client + " :Current local users " + std::to_string(u) + ", max" + std::to_string(m));
}

std::string RPL_WHOISCERTFP(std::string client, std::string nick, int fingerprint) //int ?
{
	return (client + " " + nick + " :has client certificate fingerprint " + std::to_string(fingerprint));
}

std::string RPL_NONE(void)
{
	return ("Undefined format");
}

std::string RPL_AWAY(std::string client, std::string nick, std::string msg)
{
	return (client + " " + nick + " :" + msg);
}

std::string RPL_USERHOST(std::string client, std::string reply)
{
	return (client + " :" + reply);
}

std::string RPL_UNAWAY(std::string client)
{
	return (client + " :You are no longer marked as being away");
}

std::string RPL_NOWAWAY(std::string client)
{
	return (client + " :You have been marked as being away");
}

std::string RPL_WHOREPLY(std::string client, std::string channel, std::string username, std::string host, std::string server, std::string nick, std::string flags, std::string realname, int hopcount)
{
	return (client + " " + channel + " " + username + " " + host + " " + server + " " + nick + " " + flags + " :" + std::to_string(hopcount) + " " + realname);
}

std::string RPL_ENDOFWHO(std::string client, std::string mask)
{
	return (client + " " + mask + " :End of WHO list");
}

std::string RPL_WHOISREGNICK(std::string client, std::string nick)
{
	return (client + " " + nick + " :has identified for this nick");
}

std::string RPL_WHOISUSER(std::string client, std::string nick, std::string username, std::string host, std::string realname)
{
	return (client + " " + nick + " " + username + " " + host + " * :" + realname);
}

std::string RPL_WHOISSERVER(std::string client, std::string nick, std::string server, std::string server_info)
{
	return (client + " " + nick + " " + server + " :" + server_info);
}

std::string RPL_WHOISOPERATOR(std::string client, std::string nick)
{
	return (client + " " + nick + " :is an IRC operator");
}

std::string RPL_WHOWASUSER(std::string client, std::string nick, std::string username, std::string host, std::string realname)
{
	return (client + " " + nick + " " + username + " " + host + " * :" + realname);
}

std::string RPL_WHOISIDLE(std::string client, std::string nick, unsigned int secs, time_t signon)
{
	return (client + " " + nick + " " + std::to_string(secs) + " " + std::to_string(signon) + " :seconds idle, signon time");
}

std::string RPL_ENDOFWHOIS(std::string client, std::string nick)
{
	return (client + " " + nick + " :End of /WHOIS list");
}

std::string RPL_WHOISCHANNELS(std::string client, std::string nick, std::string prefix, std::string channel)
{
	return (client + " " + nick + " :" + prefix + channel);
}

std::string RPL_WHOISSPECIAL(std::string client, std::string nick)
{
	return (client + " " + nick + " :blah blah blah");
}

std::string RPL_LISTSTART(std::string client)
{
	return (client + " Channel :Users  Name"); //cambiar esto
}

std::string RPL_LIST(std::string client, std::string channel, int client_count, std::string topic)
{
	return (client + " " + channel + " " + std::to_string(client_count) + " :" + topic);
}

std::string RPL_LISTEND(std::string client)
{
	return (client + " :End of /LIST");
}

std::string RPL_CHANNELMODEIS(std::string client, std::string channel, std::string modestring, std::string mode_arg)
{
	return (client + " " + channel + " " + modestring + " " + mode_arg + "...");
}

std::string RPL_CREATIONTIME(std::string client, std::string channel, time_t creationtime)
{
	return (client + " " + channel + " " + std::to_string(creationtime));
}

std::string RPL_WHOISACCOUNT(std::string client, std::string nick, std::string account)
{
	return (client + " " + nick + " " + account + " :is logged in as");
}

std::string RPL_NOTOPIC(std::string client, std::string channel)
{
	return (client + " " + channel + " :No topic is set");
}

std::string RPL_TOPIC(std::string client, std::string channel, std::string topic)
{
	return (client + " " + channel + " :" + topic);
}

std::string RPL_TOPICWHOTIME(std::string client, std::string channel, std::string nick, time_t setat)
{
	return (client + " " + channel + " " + nick + " " + std::to_string(setat));
}

std::string RPL_INVITELIST(std::string client, std::string channel)
{
	return (client + " " + channel);
}

std::string RPL_ENDOFINVITELIST(std::string client)
{
	return (client + " :End of /INVITE list");
}

std::string RPL_WHOISACTUALLY(std::string client, std::string nick, std::string ip, std::string hostname, std::string username)
{
	return (client + " " + nick + " :is actually...\n" + client + " " + nick + " " + ip + " :Is actually using host\n" + client + " " + nick + " " + username + "@" + hostname + " " + ip + " :Is actually using host");
}

std::string RPL_INVITING(std::string client, std::string nick, std::string channel)
{
	return (client + " " + nick + " " + channel);
}

std::string RPL_INVEXLIST(std::string client, std::string channel, std::string mask)
{
	return (client + " " + channel + " " + mask);
}

std::string RPL_ENDOFINVEXLIST(std::string client, std::string channel)
{
	return (client + " " + channel + " :End of Channel Invite Exception List");
}

std::string RPL_ENDOFEXCEPTLIST(std::string client, std::string channel)
{
	return (client + " " + channel + " :End of channel exception list");
}

std::string RPL_VERSION(std::string client, std::string version, std::string server, std::string comments)
{
	return (client + " " + version + " " + server + " :" + comments);
}

std::string RPL_NAMREPLY(std::string client, std::string symbol, std::string channel, std::string prefix, std::string nick)
{
	return (client + " " + symbol + " " + channel + " :" + prefix + nick);
}

std::string RPL_ENDOFNAMES(std::string client, std::string channel)
{
	return (client + " " + channel + " :End of /NAMES list");
}


/*int main()
{
	time_t x = time(NULL);
	std::string res;
	res = RPL_WHOISIDLE("hola", "aaa", 12345, x);
	std::cout << res << std::endl;
	return (0);
}*/
