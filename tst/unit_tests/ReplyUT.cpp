#include "Log.hpp"

#include "ReplyUT.hpp"
#include "codes.hpp"

ft_irc::ReplyUT::ReplyUT() :
	flt::Testable< ft_irc::ReplyUT >("Reply")
{
	REGISTER(ft_irc::ReplyUT, replies_tests)
}	// ReplyUT::ReplyUT


ft_irc::ReplyUT::~ReplyUT() {}	// ReplyUT::~ReplyUT


void
ft_irc::ReplyUT::replies_tests(void)
{
	LOG_TRACE("reply test: 001 RPL_WELCOME")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WELCOME, "smiro", "42", "smiro_nickname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WELCOME, "smiro", "42", "smiro_nickname"),
		"001 smiro :Welcome to the 42 Network, smiro_nickname")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WELCOME, "", "42", "smiro_nickname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WELCOME, "", "42", "smiro_nickname"),
		"001 * :Welcome to the 42 Network, smiro_nickname")

	LOG_TRACE("reply test: 002 RPL_YOURHOST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_YOURHOST, "smiro", "42", "1.0"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_YOURHOST, "smiro", "42", "1.0"),
		"002 smiro :Your host is 42, running version 1.0")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_YOURHOST, "", "42", "1.0"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_YOURHOST, "", "42", "1.0"), "002 * :Your host is 42, running version 1.0")

	LOG_TRACE("reply test: 003 RPL_CREATED")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_CREATED, "smiro", "21/10/03"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_CREATED, "smiro", "21/10/03"), "003 smiro :This server was created 21/10/03")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_CREATED, "", "21/10/03"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_CREATED, "", "21/10/03"), "003 * :This server was created 21/10/03")

	LOG_TRACE("reply test: 004 RPL_MYINFO")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_MYINFO, "smiro", "42", "1.0", "+ioO", "+isklbIes"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_MYINFO, "smiro", "42", "1.0", "+ioO", "+isklbIes"),
		"004 smiro 42 1.0 +ioO +isklbIes")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_MYINFO, "", "42", "1.0", "+ioO", "+isklbIes"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_MYINFO, "", "42", "1.0", "+ioO", "+isklbIes"), "004 * 42 1.0 +ioO +isklbIes")

	LOG_TRACE("reply test: 010 RPL_BOUNCE")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_BOUNCE, "smiro", "'INPORTANT INFO'"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_BOUNCE, "smiro", "'INPORTANT INFO'"), "010 smiro :'INPORTANT INFO'")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_BOUNCE, "", "'INPORTANT INFO'"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_BOUNCE, "", "'INPORTANT INFO'"), "010 * :'INPORTANT INFO'")

	LOG_TRACE("reply test: 221 RPL_UMODEIS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_UMODEIS, "smiro", "+iOo"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_UMODEIS, "smiro", "+iOo"), "221 smiro +iOo")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_UMODEIS, "", "+iOo"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_UMODEIS, "", "+iOo"), "221 * +iOo")

	LOG_TRACE("reply test: 251 RPL_LUSERCLIENT")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSERCLIENT, "smiro", "10", "5", "1"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSERCLIENT, "smiro", "10", "5", "1"),
		"251 smiro :There are 10 users and 5 invisible on 1 servers")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSERCLIENT, "", "10", "5", "1"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSERCLIENT, "", "10", "5", "1"),
		"251 * :There are 10 users and 5 invisible on 1 servers")

	LOG_TRACE("reply test: 252 RPL_LUSEROP")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSEROP, "smiro", "10"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSEROP, "smiro", "10"), "252 smiro 10 :operator(s) online")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSEROP, "", "10"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSEROP, "", "10"), "252 * 10 :operator(s) online")

	LOG_TRACE("reply test: 253 RPL_LUSERUNKNOWN")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSERUNKNOWN, "smiro", "10"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSERUNKNOWN, "smiro", "10"), "253 smiro 10 :unknown connection(s)")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSERUNKNOWN, "", "10"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSERUNKNOWN, "", "10"), "253 * 10 :unknown connection(s)")

	LOG_TRACE("reply test: 254 RPL_LUSERCHANNELS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSERCHANNELS, "smiro", "10"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSERCHANNELS, "smiro", "10"), "254 smiro 10 :channels formed")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSERCHANNELS, "", "10"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSERCHANNELS, "", "10"), "254 * 10 :channels formed")

	LOG_TRACE("reply test: 255 RPL_LUSERME")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSERME, "smiro", "10", "1"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSERME, "smiro", "10", "1"), "255 smiro :I have 10 clients and 1 servers")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LUSERME, "", "10", "1"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LUSERME, "", "10", "1"), "255 * :I have 10 clients and 1 servers")

	LOG_TRACE("reply test: 256 RPL_ADMINME")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ADMINME, "smiro", "42_server"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ADMINME, "smiro", "42_server"), "256 smiro 42_server :Administrative info")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ADMINME, "", "42_server"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ADMINME, "", "42_server"), "256 * 42_server :Administrative info")

	LOG_TRACE("reply test: 257 RPL_ADMINLOC1")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ADMINLOC1, "smiro", "Administrative info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ADMINLOC1, "smiro", "Administrative info"), "257 smiro :Administrative info")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ADMINLOC1, "", "Administrative info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ADMINLOC1, "", "Administrative info"), "257 * :Administrative info")

	LOG_TRACE("reply test: 258 RPL_ADMINLOC2")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ADMINLOC2, "smiro", "Administrative info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ADMINLOC2, "smiro", "Administrative info"), "258 smiro :Administrative info")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ADMINLOC2, "", "Administrative info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ADMINLOC2, "", "Administrative info"), "258 * :Administrative info")

	LOG_TRACE("reply test: 259 RPL_ADMINEMAIL")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ADMINEMAIL, "smiro", "Administrative info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ADMINEMAIL, "smiro", "Administrative info"),
		"259 smiro :Administrative info")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ADMINEMAIL, "", "Administrative info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ADMINEMAIL, "", "Administrative info"), "259 * :Administrative info")

	LOG_TRACE("reply test: 263 RPL_TRYAGAIN")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_TRYAGAIN, "smiro", "PASS"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_TRYAGAIN, "smiro", "PASS"),
		"263 smiro PASS :Please wait a while and try again.")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_TRYAGAIN, "", "PASS"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_TRYAGAIN, "", "PASS"), "263 * PASS :Please wait a while and try again.")

	LOG_TRACE("reply test: 265 RPL_LOCALUSERS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LOCALUSERS, "smiro", "10", "200"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LOCALUSERS, "smiro", "10", "200"),
		"265 smiro :Current local users 10, max 200")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LOCALUSERS, "", "10", "200"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LOCALUSERS, "", "10", "200"), "265 * :Current local users 10, max 200")

	LOG_TRACE("reply test: 266 RPL_GLOBALUSERS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_GLOBALUSERS, "smiro", "10", "200"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_GLOBALUSERS, "smiro", "10", "200"),
		"266 smiro :Current global users 10, max 200")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_GLOBALUSERS, "", "10", "200"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_GLOBALUSERS, "", "10", "200"), "266 * :Current global users 10, max 200")

	LOG_TRACE("reply test: 276 RPL_WHOISCERTFP")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISCERTFP, "smiro", "smiro2", "123456789"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISCERTFP, "smiro", "smiro2", "123456789"),
		"276 smiro smiro2 :has certificate fingerprint 123456789")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISCERTFP, "", "smiro2", "123456789"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISCERTFP, "", "smiro2", "123456789"),
		"276 * smiro2 :has certificate fingerprint 123456789")

	LOG_TRACE("reply test: 300 RPL_NONE")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_NONE, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_NONE, "smiro"), "300 :")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_NONE, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_NONE, ""), "300 :")

	LOG_TRACE("reply test: 301 RPL_AWAY")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_AWAY, "smiro", "smiro2", "I am away"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_AWAY, "smiro", "smiro2", "I am away"), "301 smiro smiro2 :I am away")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_AWAY, "", "smiro2", "I am away"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_AWAY, "", "smiro2", "I am away"), "301 * smiro2 :I am away")

	LOG_TRACE("reply test: 302 RPL_USERHOST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_USERHOST, "smiro", "I am your host"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_USERHOST, "smiro", "I am your host"), "302 smiro :I am your host")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_USERHOST, "", "I am your host"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_USERHOST, "", "I am your host"), "302 * :I am your host")

	LOG_TRACE("reply test: 305 RPL_UNAWAY")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_UNAWAY, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_UNAWAY, "smiro"), "305 smiro :You are no longer marked as being away")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_UNAWAY, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_UNAWAY, ""), "305 * :You are no longer marked as being away")

	LOG_TRACE("reply test: 306 RPL_NOWAWAY")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_NOWAWAY, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_NOWAWAY, "smiro"), "306 smiro :You have been marked as being away")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_NOWAWAY, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_NOWAWAY, ""), "306 * :You have been marked as being away")

	LOG_TRACE("reply test: 352 RPL_WHOREPLY")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOREPLY, "smiro", "#channel", "user", "host", "server", "nick", "flags",
		"realname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOREPLY, "smiro", "#channel", "user", "host", "server", "nick", "flags",
		"realname"),
		"352 smiro #channel user host server nick flags :0 realname")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOREPLY, "", "#channel", "user", "host", "server", "nick", "flags",
		"realname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOREPLY, "", "#channel", "user", "host", "server", "nick", "flags",
		"realname"),
		"352 * #channel user host server nick flags :0 realname")

	LOG_TRACE("reply test: 315 RPL_ENDOFWHO")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFWHO, "smiro", "smiro!*@*"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFWHO, "smiro", "smiro!*@*"), "315 smiro smiro!*@* :End of WHO list")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFWHO, "", "smiro!*@*"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFWHO, "", "smiro!*@*"), "315 * smiro!*@* :End of WHO list")

	LOG_TRACE("reply test: 307 RPL_WHOISREGNICK")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISREGNICK, "smiro", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISREGNICK, "smiro", "smiro2"),
		"307 smiro smiro2 :has identified for this nick")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISREGNICK, "", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISREGNICK, "", "smiro2"), "307 * smiro2 :has identified for this nick")

	LOG_TRACE("reply test: 311 RPL_WHOISUSER")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISUSER, "smiro", "smiro2", "user", "host", "realname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISUSER, "smiro", "smiro2", "user", "host", "realname"),
		"311 smiro smiro2 user host * :realname")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISUSER, "", "smiro2", "user", "host", "realname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISUSER, "", "smiro2", "user", "host", "realname"),
		"311 * smiro2 user host * :realname")

	LOG_TRACE("reply test: 311 RPL_WHOISUSER")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISUSER, "smiro", "smiro2", "user", "host", "realname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISUSER, "smiro", "smiro2", "user", "host", "realname"),
		"311 smiro smiro2 user host * :realname")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISUSER, "", "smiro2", "user", "host", "realname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISUSER, "", "smiro2", "user", "host", "realname"),
		"311 * smiro2 user host * :realname")

	LOG_TRACE("reply test: 312 RPL_WHOISSERVER")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISSERVER, "smiro", "smiro2", "server", "info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISSERVER, "smiro", "smiro2", "server", "info"),
		"312 smiro smiro2 server :info")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISSERVER, "", "smiro2", "server", "info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISSERVER, "", "smiro2", "server", "info"), "312 * smiro2 server :info")

	LOG_TRACE("reply test: 313 RPL_WHOISOPERATOR")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISOPERATOR, "smiro", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISOPERATOR, "smiro", "smiro2"), "313 smiro smiro2 :is an IRC operator")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISOPERATOR, "", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISOPERATOR, "", "smiro2"), "313 * smiro2 :is an IRC operator")

	LOG_TRACE("reply test: 314 RPL_WHOWASUSER")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOWASUSER, "smiro", "smiro2", "user", "host", "realname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOWASUSER, "smiro", "smiro2", "user", "host", "realname"),
		"314 smiro smiro2 user host * :realname")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOWASUSER, "", "smiro2", "user", "host", "realname"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOWASUSER, "", "smiro2", "user", "host", "realname"),
		"314 * smiro2 user host * :realname")

	LOG_TRACE("reply test: 317 RPL_WHOISIDLE")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISIDLE, "smiro", "smiro2", "3600", "42"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISIDLE, "smiro", "smiro2", "3600", "42"),
		"317 smiro smiro2 3600 42 :seconds idle, signon time")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISIDLE, "", "smiro2", "3600", "42"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISIDLE, "", "smiro2", "3600", "42"),
		"317 * smiro2 3600 42 :seconds idle, signon time")

	LOG_TRACE("reply test: 318 RPL_ENDOFWHOIS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFWHOIS, "smiro", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFWHOIS, "smiro", "smiro2"), "318 smiro smiro2 :End of /WHOIS list")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFWHOIS, "", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFWHOIS, "", "smiro2"), "318 * smiro2 :End of /WHOIS list")

	LOG_TRACE("reply test: 319 RPL_WHOISCHANNELS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISCHANNELS, "smiro", "smiro2", "@", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISCHANNELS, "smiro", "smiro2", "@", "#channel"),
		"319 smiro smiro2 :@#channel")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISCHANNELS, "", "smiro2", "@", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISCHANNELS, "", "smiro2", "@", "#channel"), "319 * smiro2 :@#channel")

	LOG_TRACE("reply test: 320 RPL_WHOISSPECIAL")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISSPECIAL, "smiro", "smiro2", "info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISSPECIAL, "smiro", "smiro2", "info"), "320 smiro smiro2 :info")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISSPECIAL, "", "smiro2", "info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISSPECIAL, "", "smiro2", "info"), "320 * smiro2 :info")

	LOG_TRACE("reply test: 321 RPL_LISTSTART")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LISTSTART, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LISTSTART, "smiro"), "321 smiro Channel :Users Names")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LISTSTART, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LISTSTART, ""), "321 * Channel :Users Names")

	LOG_TRACE("reply test: 322 RPL_LIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LIST, "smiro", "#channel", "42", "TOPIC"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LIST, "smiro", "#channel", "42", "TOPIC"), "322 smiro #channel 42 :TOPIC")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LIST, "", "#channel", "42", "TOPIC"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LIST, "", "#channel", "42", "TOPIC"), "322 * #channel 42 :TOPIC")

	LOG_TRACE("reply test: 323 RPL_LISTEND")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LISTEND, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LISTEND, "smiro"), "323 smiro :End of /LIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LISTEND, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LISTEND, ""), "323 * :End of /LIST")

	LOG_TRACE("reply test: 324 RPL_CHANNELMODEIS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_CHANNELMODEIS, "smiro", "#channel", "+ismb", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_CHANNELMODEIS, "smiro", "#channel", "+ismb", "smiro2"),
		"324 smiro #channel +ismb smiro2")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_CHANNELMODEIS, "", "#channel", "+ismb", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_CHANNELMODEIS, "", "#channel", "+ismb", "smiro2"),
		"324 * #channel +ismb smiro2")

	LOG_TRACE("reply test: 329 RPL_CREATIONTIME")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_CREATIONTIME, "smiro", "#channel", "1234566789"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_CREATIONTIME, "smiro", "#channel", "1234566789"),
		"329 smiro #channel 1234566789")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_CREATIONTIME, "", "#channel", "1234566789"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_CREATIONTIME, "", "#channel", "1234566789"), "329 * #channel 1234566789")

	LOG_TRACE("reply test: 330 RPL_WHOISACCOUNT")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISACCOUNT, "smiro", "smiro2", "smiro21"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISACCOUNT, "smiro", "smiro2", "smiro21"),
		"330 smiro smiro2 smiro21 :is logged in as")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISACCOUNT, "", "smiro2", "smiro21"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISACCOUNT, "", "smiro2", "smiro21"),
		"330 * smiro2 smiro21 :is logged in as")

	LOG_TRACE("reply test: 331 RPL_NOTOPIC")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_NOTOPIC, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_NOTOPIC, "smiro", "#channel"), "331 smiro #channel :No topic is set")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_NOTOPIC, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_NOTOPIC, "", "#channel"), "331 * #channel :No topic is set")

	LOG_TRACE("reply test: 332 RPL_TOPIC")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_TOPIC, "smiro", "#channel", "TOPIC"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_TOPIC, "smiro", "#channel", "TOPIC"), "332 smiro #channel :TOPIC")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_TOPIC, "", "#channel", "TOPIC"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_TOPIC, "", "#channel", "TOPIC"), "332 * #channel :TOPIC")

	LOG_TRACE("reply test: 333 RPL_TOPICWHOTIME")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_TOPICWHOTIME, "smiro", "#channel", "smiro2", "1234566789"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_TOPICWHOTIME, "smiro", "#channel", "smiro2", "1234566789"),
		"333 smiro #channel smiro2 1234566789")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_TOPICWHOTIME, "", "#channel", "smiro2", "1234566789"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_TOPICWHOTIME, "", "#channel", "smiro2", "1234566789"),
		"333 * #channel smiro2 1234566789")

	LOG_TRACE("reply test: 336 RPL_INVITELIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_INVITELIST, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_INVITELIST, "smiro", "#channel"), "336 smiro #channel")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_INVITELIST, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_INVITELIST, "", "#channel"), "336 * #channel")

	LOG_TRACE("reply test: 337 RPL_ENDOFINVITELIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFINVITELIST, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFINVITELIST, "smiro"), "337 smiro :End of /INVITE list")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFINVITELIST, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFINVITELIST, ""), "337 * :End of /INVITE list")

	LOG_TRACE("reply test: 338 RPL_WHOISACTUALLY")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISACTUALLY, "smiro", "nick", "127.0.0.1", "127.0.0.1", "user"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISACTUALLY, "smiro", "nick", "127.0.0.1", "127.0.0.1", "user"),
		"338 smiro nick user@127.0.0.1 127.0.0.1 :Is actually using host")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISACTUALLY, "", "nick", "127.0.0.1", "127.0.0.1", "user"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISACTUALLY, "", "nick", "127.0.0.1", "127.0.0.1", "user"),
		"338 * nick user@127.0.0.1 127.0.0.1 :Is actually using host")

	LOG_TRACE("reply test: 341 RPL_INVITING")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_INVITING, "smiro", "nick", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_INVITING, "smiro", "nick", "#channel"), "341 smiro nick #channel")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_INVITING, "", "nick", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_INVITING, "", "nick", "#channel"), "341 * nick #channel")

	LOG_TRACE("reply test: 346 RPL_INVEXLIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_INVEXLIST, "smiro", "#channel", "mask"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_INVEXLIST, "smiro", "#channel", "mask"), "346 smiro #channel mask")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_INVEXLIST, "", "#channel", "mask"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_INVEXLIST, "", "#channel", "mask"), "346 * #channel mask")

	LOG_TRACE("reply test: 347 RPL_ENDOFINVEXLIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFINVEXLIST, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFINVEXLIST, "smiro", "#channel"),
		"347 smiro #channel :End of Channel Invite Exception List")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFINVEXLIST, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFINVEXLIST, "", "#channel"),
		"347 * #channel :End of Channel Invite Exception List")

	LOG_TRACE("reply test: 348 RPL_EXCEPTLIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_EXCEPTLIST, "smiro", "#channel", "mask"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_EXCEPTLIST, "smiro", "#channel", "mask"), "348 smiro #channel mask")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_EXCEPTLIST, "", "#channel", "mask"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_EXCEPTLIST, "", "#channel", "mask"), "348 * #channel mask")

	LOG_TRACE("reply test: 349 RPL_ENDOFEXCEPTLIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFEXCEPTLIST, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFEXCEPTLIST, "smiro", "#channel"),
		"349 smiro #channel :End of channel exception list")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFEXCEPTLIST, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFEXCEPTLIST, "", "#channel"),
		"349 * #channel :End of channel exception list")

	LOG_TRACE("reply test: 351 RPL_VERSION")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_VERSION, "smiro", "1.0", "server", "works"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_VERSION, "smiro", "1.0", "server", "works"), "351 smiro 1.0 server :works")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_VERSION, "", "1.0", "server", "works"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_VERSION, "", "1.0", "server", "works"), "351 * 1.0 server :works")

	LOG_TRACE("reply test: 353 RPL_NAMREPLY")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_NAMREPLY, "smiro", "=", "#channel", "~", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_NAMREPLY, "smiro", "=", "#channel", "~", "smiro2"),
		"353 smiro = #channel :~smiro2")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_NAMREPLY, "", "=", "#channel", "~", "smiro2"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_NAMREPLY, "", "=", "#channel", "~", "smiro2"), "353 * = #channel :~smiro2")

	LOG_TRACE("reply test: 366 RPL_ENDOFNAMES")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFNAMES, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFNAMES, "smiro", "#channel"), "366 smiro #channel :End of /NAMES list")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFNAMES, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFNAMES, "", "#channel"), "366 * #channel :End of /NAMES list")

	LOG_TRACE("reply test: 364 RPL_LINKS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LINKS, "smiro", "server", "0", "server_info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LINKS, "smiro", "server", "0", "server_info"),
		"364 smiro * server :0 server_info")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LINKS, "", "server", "0", "server_info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LINKS, "", "server", "0", "server_info"), "364 * * server :0 server_info")

	LOG_TRACE("reply test: 365 RPL_ENDOFLINKS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFLINKS, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFLINKS, "smiro"), "365 smiro * :End of /LINKS list")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFLINKS, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFLINKS, ""), "365 * * :End of /LINKS list")

	LOG_TRACE("reply test: 367 RPL_BANLIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_BANLIST, "smiro", "#channel", "*!*@*", "smiro2", "12356789"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_BANLIST, "smiro", "#channel", "*!*@*", "smiro2", "12356789"),
		"367 smiro #channel *!*@* smiro2 12356789")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_BANLIST, "", "#channel", "*!*@*", "smiro2", "12356789"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_BANLIST, "", "#channel", "*!*@*", "smiro2", "12356789"),
		"367 * #channel *!*@* smiro2 12356789")

	LOG_TRACE("reply test: 368 RPL_ENDOFBANLIST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFBANLIST, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFBANLIST, "smiro", "#channel"),
		"368 smiro #channel :End of channel ban list")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFBANLIST, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFBANLIST, "", "#channel"), "368 * #channel :End of channel ban list")

	LOG_TRACE("reply test: 369 RPL_ENDOFWHOWAS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFWHOWAS, "smiro", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFWHOWAS, "smiro", "nick"), "369 smiro nick :End of WHOWAS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFWHOWAS, "", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFWHOWAS, "", "nick"), "369 * nick :End of WHOWAS")

	LOG_TRACE("reply test: 371 RPL_INFO")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_INFO, "smiro", "info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_INFO, "smiro", "info"), "371 smiro :info")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_INFO, "", "info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_INFO, "", "info"), "371 * :info")

	LOG_TRACE("reply test: 374 RPL_ENDOFINFO")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFINFO, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFINFO, "smiro"), "374 smiro :End of INFO list")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFINFO, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFINFO, ""), "374 * :End of INFO list")

	LOG_TRACE("reply test: 375 RPL_MOTDSTART")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_MOTDSTART, "smiro", "server"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_MOTDSTART, "smiro", "server"), "375 smiro :- server Message of the day - ")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_MOTDSTART, "", "server"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_MOTDSTART, "", "server"), "375 * :- server Message of the day - ")

	LOG_TRACE("reply test: 372 RPL_MOTD")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_MOTD, "smiro", "line"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_MOTD, "smiro", "line"), "372 smiro :line")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_MOTD, "", "line"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_MOTD, "", "line"), "372 * :line")

	LOG_TRACE("reply test: 376 RPL_ENDOFMOTD")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFMOTD, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFMOTD, "smiro"), "376 smiro :End of /MOTD command.")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFMOTD, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFMOTD, ""), "376 * :End of /MOTD command.")

	LOG_TRACE("reply test: 378 RPL_WHOISHOST")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISHOST, "smiro", "nick", "host"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISHOST, "smiro", "nick", "host"),
		"378 smiro nick :is connecting from *@host")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISHOST, "", "nick", "host"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISHOST, "", "nick", "host"), "378 * nick :is connecting from *@host")

	LOG_TRACE("reply test: 379 RPL_WHOISMODES")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISMODES, "smiro", "nick", "+iO"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISMODES, "smiro", "nick", "+iO"), "379 smiro nick :is using modes +iO")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISMODES, "", "nick", "+iO"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISMODES, "", "nick", "+iO"), "379 * nick :is using modes +iO")

	LOG_TRACE("reply test: 381 RPL_YOUREOPER")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_YOUREOPER, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_YOUREOPER, "smiro"), "381 smiro :You are now an IRC operator")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_YOUREOPER, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_YOUREOPER, ""), "381 * :You are now an IRC operator")

	LOG_TRACE("reply test: 382 RPL_REHASHING")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_REHASHING, "smiro", "config.cfg"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_REHASHING, "smiro", "config.cfg"), "382 smiro config.cfg :Rehashing")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_REHASHING, "", "config.cfg"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_REHASHING, "", "config.cfg"), "382 * config.cfg :Rehashing")

	LOG_TRACE("reply test: 391 RPL_TIME")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_TIME, "smiro", "server", "timestamp", "ts_offset", "time"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_TIME, "smiro", "server", "timestamp", "ts_offset", "time"),
		"391 smiro server timestamp ts_offset :time")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_TIME, "", "server", "timestamp", "ts_offset", "time"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_TIME, "", "server", "timestamp", "ts_offset", "time"),
		"391 * server timestamp ts_offset :time")

	LOG_TRACE("reply test: 400 ERR_UNKNOWNERROR")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_UNKNOWNERROR, "smiro", "PASS", "PASS", "info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_UNKNOWNERROR, "smiro", "PASS", "PASS", "info"), "400 smiro PASS PASS :info")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_UNKNOWNERROR, "", "PASS", "PASS", "info"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_UNKNOWNERROR, "", "PASS", "PASS", "info"), "400 * PASS PASS :info")

	LOG_TRACE("reply test: 401 ERR_NOSUCHNICK")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOSUCHNICK, "smiro", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOSUCHNICK, "smiro", "nick"), "401 smiro nick :No such nick/channel")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOSUCHNICK, "", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOSUCHNICK, "", "nick"), "401 * nick :No such nick/channel")

	LOG_TRACE("reply test: 402 ERR_NOSUCHSERVER")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOSUCHSERVER, "smiro", "server"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOSUCHSERVER, "smiro", "server"), "402 smiro server :No such server")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOSUCHSERVER, "", "server"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOSUCHSERVER, "", "server"), "402 * server :No such server")

	LOG_TRACE("reply test: 403 ERR_NOSUCHCHANNEL")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOSUCHCHANNEL, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOSUCHCHANNEL, "smiro", "#channel"), "403 smiro #channel :No such channel")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOSUCHCHANNEL, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOSUCHCHANNEL, "", "#channel"), "403 * #channel :No such channel")

	LOG_TRACE("reply test: 404 ERR_CANNOTSENDTOCHAN")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_CANNOTSENDTOCHAN, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_CANNOTSENDTOCHAN, "smiro", "#channel"),
		"404 smiro #channel :Cannot send to channel")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_CANNOTSENDTOCHAN, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_CANNOTSENDTOCHAN, "", "#channel"), "404 * #channel :Cannot send to channel")

	LOG_TRACE("reply test: 405 ERR_TOOMANYCHANNELS")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_TOOMANYCHANNELS, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_TOOMANYCHANNELS, "smiro", "#channel"),
		"405 smiro #channel :You have joined too many channels")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_TOOMANYCHANNELS, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_TOOMANYCHANNELS, "", "#channel"),
		"405 * #channel :You have joined too many channels")

	LOG_TRACE("reply test: 406 ERR_WASNOSUCHNICK")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_WASNOSUCHNICK, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_WASNOSUCHNICK, "smiro"), "406 smiro :There was no such nickname")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_WASNOSUCHNICK, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_WASNOSUCHNICK, ""), "406 * :There was no such nickname")

	LOG_TRACE("reply test: 409 ERR_NOORIGIN")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOORIGIN, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOORIGIN, "smiro"), "409 smiro :No origin specified")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOORIGIN, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOORIGIN, ""), "409 * :No origin specified")

	LOG_TRACE("reply test: 411 ERR_NORECIPIENT")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NORECIPIENT, "smiro", "PRIVMSG"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NORECIPIENT, "smiro", "PRIVMSG"), "411 smiro :No recipient given PRIVMSG")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NORECIPIENT, "", "PRIVMSG"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NORECIPIENT, "", "PRIVMSG"), "411 * :No recipient given PRIVMSG")

	LOG_TRACE("reply test: 412 ERR_NOTEXTTOSEND")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOTEXTTOSEND, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOTEXTTOSEND, "smiro"), "412 smiro :No text to send")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOTEXTTOSEND, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOTEXTTOSEND, ""), "412 * :No text to send")

	LOG_TRACE("reply test: 417 ERR_INPUTTOOLONG")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_INPUTTOOLONG, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_INPUTTOOLONG, "smiro"), "417 smiro :Input line was too long")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_INPUTTOOLONG, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_INPUTTOOLONG, ""), "417 * :Input line was too long")

	LOG_TRACE("reply test: 421 ERR_UNKNOWNCOMMAND")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_UNKNOWNCOMMAND, "smiro", "AAAA"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_UNKNOWNCOMMAND, "smiro", "AAAA"), "421 smiro AAAA :Unknown command")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_UNKNOWNCOMMAND, "", "AAAA"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_UNKNOWNCOMMAND, "", "AAAA"), "421 * AAAA :Unknown command")

	LOG_TRACE("reply test: 422 ERR_NOMOTD")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOMOTD, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOMOTD, "smiro"), "422 smiro :MOTD File is missing")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOMOTD, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOMOTD, ""), "422 * :MOTD File is missing")

	LOG_TRACE("reply test: 431 ERR_NONICKNAMEGIVEN")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NONICKNAMEGIVEN, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NONICKNAMEGIVEN, "smiro"), "431 smiro :No nickname given")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NONICKNAMEGIVEN, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NONICKNAMEGIVEN, ""), "431 * :No nickname given")

	LOG_TRACE("reply test: 432 ERR_ERRONEUSNICKNAME")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_ERRONEUSNICKNAME, "smiro", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_ERRONEUSNICKNAME, "smiro", "nick"), "432 smiro nick :Erroneus nickname")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_ERRONEUSNICKNAME, "", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_ERRONEUSNICKNAME, "", "nick"), "432 * nick :Erroneus nickname")

	LOG_TRACE("reply test: 433 ERR_NICKNAMEINUSE")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NICKNAMEINUSE, "smiro", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NICKNAMEINUSE, "smiro", "nick"),
		"433 smiro nick :Nickname is already in use")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NICKNAMEINUSE, "", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NICKNAMEINUSE, "", "nick"), "433 * nick :Nickname is already in use")

	LOG_TRACE("reply test: 441 ERR_USERNOTINCHANNEL")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_USERNOTINCHANNEL, "smiro", "nick", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_USERNOTINCHANNEL, "smiro", "nick", "#channel"),
		"441 smiro nick #channel :They aren't on that channel")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_USERNOTINCHANNEL, "", "nick", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_USERNOTINCHANNEL, "", "nick", "#channel"),
		"441 * nick #channel :They aren't on that channel")

	LOG_TRACE("reply test: 442 ERR_NOTONCHANNEL")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOTONCHANNEL, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOTONCHANNEL, "smiro", "#channel"),
		"442 smiro #channel :You're not on that channel")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOTONCHANNEL, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOTONCHANNEL, "", "#channel"), "442 * #channel :You're not on that channel")

	LOG_TRACE("reply test: 443 ERR_USERONCHANNEL")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_USERONCHANNEL, "smiro", "nick", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_USERONCHANNEL, "smiro", "nick", "#channel"),
		"443 smiro nick #channel :is already on channel")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_USERONCHANNEL, "", "nick", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_USERONCHANNEL, "", "nick", "#channel"),
		"443 * nick #channel :is already on channel")

	LOG_TRACE("reply test: 451 ERR_NOTREGISTERED")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOTREGISTERED, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOTREGISTERED, "smiro"), "451 smiro :You have not registered")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOTREGISTERED, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOTREGISTERED, ""), "451 * :You have not registered")

	LOG_TRACE("reply test: 461 ERR_NEEDMOREPARAMS")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, "smiro", "PASS"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, "smiro", "PASS"), "461 smiro PASS :Not enough parameters")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, "", "PASS"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, "", "PASS"), "461 * PASS :Not enough parameters")

	LOG_TRACE("reply test: 462 ERR_ALREADYREGISTERED")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_ALREADYREGISTERED, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_ALREADYREGISTERED, "smiro"), "462 smiro :You may not reregister")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_ALREADYREGISTERED, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_ALREADYREGISTERED, ""), "462 * :You may not reregister")

	LOG_TRACE("reply test: 464 ERR_PASSWDMISMATCH")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_PASSWDMISMATCH, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_PASSWDMISMATCH, "smiro"), "464 smiro :Password incorrect")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_PASSWDMISMATCH, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_PASSWDMISMATCH, ""), "464 * :Password incorrect")

	LOG_TRACE("reply test: 465 ERR_YOUREBANNEDCREEP")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_YOUREBANNEDCREEP, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_YOUREBANNEDCREEP, "smiro"), "465 smiro :You are banned from this server.")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_YOUREBANNEDCREEP, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_YOUREBANNEDCREEP, ""), "465 * :You are banned from this server.")

	LOG_TRACE("reply test: 471 ERR_CHANNELISFULL")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_CHANNELISFULL, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_CHANNELISFULL, "smiro", "#channel"),
		"471 smiro #channel :Cannot join channel (+l)")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_CHANNELISFULL, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_CHANNELISFULL, "", "#channel"), "471 * #channel :Cannot join channel (+l)")

	LOG_TRACE("reply test: 472 ERR_UNKNOWNMODE")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_UNKNOWNMODE, "smiro", "x"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_UNKNOWNMODE, "smiro", "x"), "472 smiro x :is unknown mode char to me")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_UNKNOWNMODE, "", "x"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_UNKNOWNMODE, "", "x"), "472 * x :is unknown mode char to me")

	LOG_TRACE("reply test: 473 ERR_INVITEONLYCHAN")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_INVITEONLYCHAN, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_INVITEONLYCHAN, "smiro", "#channel"),
		"473 smiro #channel :Cannot join channel (+i)")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_INVITEONLYCHAN, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_INVITEONLYCHAN, "", "#channel"), "473 * #channel :Cannot join channel (+i)")

	LOG_TRACE("reply test: 474 ERR_BANNEDFROMCHAN")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_BANNEDFROMCHAN, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_BANNEDFROMCHAN, "smiro", "#channel"),
		"474 smiro #channel :Cannot join channel (+b)")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_BANNEDFROMCHAN, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_BANNEDFROMCHAN, "", "#channel"), "474 * #channel :Cannot join channel (+b)")

	LOG_TRACE("reply test: 475 ERR_BADCHANNELKEY")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_BADCHANNELKEY, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_BADCHANNELKEY, "smiro", "#channel"),
		"475 smiro #channel :Cannot join channel (+k)")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_BADCHANNELKEY, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_BADCHANNELKEY, "", "#channel"), "475 * #channel :Cannot join channel (+k)")

	LOG_TRACE("reply test: 476 ERR_BADCHANMASK")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_BADCHANMASK, "smiro", "channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_BADCHANMASK, "smiro", "channel"), "476 smiro channel :Bad Channel Mask")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_BADCHANMASK, "", "channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_BADCHANMASK, "", "channel"), "476 * channel :Bad Channel Mask")

	LOG_TRACE("reply test: 481 ERR_NOPRIVILEGES")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOPRIVILEGES, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOPRIVILEGES, "smiro"),
		"481 smiro :Permission Denied- You're not an IRC operator")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOPRIVILEGES, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOPRIVILEGES, ""), "481 * :Permission Denied- You're not an IRC operator")

	LOG_TRACE("reply test: 482 ERR_CHANOPRIVSNEEDED")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_CHANOPRIVSNEEDED, "smiro", "channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_CHANOPRIVSNEEDED, "smiro", "channel"),
		"482 smiro channel :You're not channel operator")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_CHANOPRIVSNEEDED, "", "channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_CHANOPRIVSNEEDED, "", "channel"),
		"482 * channel :You're not channel operator")

	LOG_TRACE("reply test: 483 ERR_CANTKILLSERVER")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_CANTKILLSERVER, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_CANTKILLSERVER, "smiro"), "483 smiro :You cant kill a server!")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_CANTKILLSERVER, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_CANTKILLSERVER, ""), "483 * :You cant kill a server!")

	LOG_TRACE("reply test: 491 ERR_NOOPERHOST")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOOPERHOST, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOOPERHOST, "smiro"), "491 smiro :No O-lines for your host")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOOPERHOST, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOOPERHOST, ""), "491 * :No O-lines for your host")

	LOG_TRACE("reply test: 501 ERR_UMODEUNKNOWNFLAG")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_UMODEUNKNOWNFLAG, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_UMODEUNKNOWNFLAG, "smiro"), "501 smiro :Unknown MODE flag")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_UMODEUNKNOWNFLAG, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_UMODEUNKNOWNFLAG, ""), "501 * :Unknown MODE flag")

	LOG_TRACE("reply test: 502 ERR_USERSDONTMATCH")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_USERSDONTMATCH, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_USERSDONTMATCH, "smiro"), "502 smiro :Cant change mode for other users")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_USERSDONTMATCH, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_USERSDONTMATCH, ""), "502 * :Cant change mode for other users")

	LOG_TRACE("reply test: 524 ERR_HELPNOTFOUND")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_HELPNOTFOUND, "smiro", "subject"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_HELPNOTFOUND, "smiro", "subject"),
		"524 smiro subject :No help available on this topic")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_HELPNOTFOUND, "", "subject"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_HELPNOTFOUND, "", "subject"),
		"524 * subject :No help available on this topic")

	LOG_TRACE("reply test: 525 ERR_INVALIDKEY")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_INVALIDKEY, "smiro", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_INVALIDKEY, "smiro", "#channel"),
		"525 smiro #channel :Key is not well-formed")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_INVALIDKEY, "", "#channel"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_INVALIDKEY, "", "#channel"), "525 * #channel :Key is not well-formed")

	LOG_TRACE("reply test: 670 RPL_STARTTLS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_STARTTLS, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_STARTTLS, "smiro"),
		"670 smiro :STARTTLS successful, proceed with TLS handshake")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_STARTTLS, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_STARTTLS, ""), "670 * :STARTTLS successful, proceed with TLS handshake")

	LOG_TRACE("reply test: 671 RPL_WHOISSECURE")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISSECURE, "smiro", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISSECURE, "smiro", "nick"),
		"671 smiro nick :is using a secure connection")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_WHOISSECURE, "", "nick"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_WHOISSECURE, "", "nick"), "671 * nick :is using a secure connection")

	LOG_TRACE("reply test: 691 ERR_STARTTLS")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_STARTTLS, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_STARTTLS, "smiro"), "691 smiro :STARTTLS failed (Wrong moon phase)")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_STARTTLS, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_STARTTLS, ""), "691 * :STARTTLS failed (Wrong moon phase)")

	LOG_TRACE("reply test: 696 ERR_INVALIDMODEPARAM")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_INVALIDMODEPARAM, "smiro", "#channel", "+b", "#channel", "description"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_INVALIDMODEPARAM, "smiro", "#channel", "+b", "#channel", "description"),
		"696 smiro #channel +b #channel :description")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_INVALIDMODEPARAM, "", "#channel", "+b", "#channel", "description"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_INVALIDMODEPARAM, "", "#channel", "+b", "#channel", "description"),
		"696 * #channel +b #channel :description")

	LOG_TRACE("reply test: 704 RPL_HELPSTART")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_HELPSTART, "smiro", "topic", "line"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_HELPSTART, "smiro", "topic", "line"), "704 smiro topic :line")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_HELPSTART, "", "topic", "line"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_HELPSTART, "", "topic", "line"), "704 * topic :line")

	LOG_TRACE("reply test: 705 RPL_HELPTXT")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_HELPTXT, "smiro", "topic", "line"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_HELPTXT, "smiro", "topic", "line"), "705 smiro topic :line")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_HELPTXT, "", "topic", "line"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_HELPTXT, "", "topic", "line"), "705 * topic :line")

	LOG_TRACE("reply test: 706 RPL_ENDOFHELP")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFHELP, "smiro", "topic", "line"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFHELP, "smiro", "topic", "line"), "706 smiro topic :line")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_ENDOFHELP, "", "topic", "line"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_ENDOFHELP, "", "topic", "line"), "706 * topic :line")

	LOG_TRACE("reply test: 723 ERR_NOPRIVS")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOPRIVS, "smiro", "priv"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOPRIVS, "smiro", "priv"), "723 smiro priv :Insufficient oper privileges.")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NOPRIVS, "", "priv"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NOPRIVS, "", "priv"), "723 * priv :Insufficient oper privileges.")

	LOG_TRACE("reply test: 900 RPL_LOGGEDIN")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LOGGEDIN, "smiro", "nick", "user", "host", "account", "username"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LOGGEDIN, "smiro", "nick", "user", "host", "account", "username"),
		"900 smiro nick!user@host account :You are now logged in as username")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LOGGEDIN, "", "nick", "user", "host", "account", "username"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LOGGEDIN, "", "nick", "user", "host", "account", "username"),
		"900 * nick!user@host account :You are now logged in as username")

	LOG_TRACE("reply test: 901 RPL_LOGGEDOUT")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LOGGEDOUT, "smiro", "nick", "user", "host"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LOGGEDOUT, "smiro", "nick", "user", "host"),
		"901 smiro nick!user@host :You are now logged out")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_LOGGEDOUT, "", "nick", "user", "host"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_LOGGEDOUT, "", "nick", "user", "host"),
		"901 * nick!user@host :You are now logged out")

	LOG_TRACE("reply test: 902 ERR_NICKLOCKED")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NICKLOCKED, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NICKLOCKED, "smiro"), "902 smiro :You must use a nick assigned to you")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_NICKLOCKED, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_NICKLOCKED, ""), "902 * :You must use a nick assigned to you")

	LOG_TRACE("reply test: 903 RPL_SASLSUCCESS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_SASLSUCCESS, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_SASLSUCCESS, "smiro"), "903 smiro :SASL authentication successful")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_SASLSUCCESS, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_SASLSUCCESS, ""), "903 * :SASL authentication successful")

	LOG_TRACE("reply test: 904 ERR_SASLFAIL")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_SASLFAIL, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_SASLFAIL, "smiro"), "904 smiro :SASL authentication failed")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_SASLFAIL, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_SASLFAIL, ""), "904 * :SASL authentication failed")

	LOG_TRACE("reply test: 905 ERR_SASLTOOLONG")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_SASLTOOLONG, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_SASLTOOLONG, "smiro"), "905 smiro :SASL message too long")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_SASLTOOLONG, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_SASLTOOLONG, ""), "905 * :SASL message too long")

	LOG_TRACE("reply test: 906 ERR_SASLABORTED")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_SASLABORTED, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_SASLABORTED, "smiro"), "906 smiro :SASL authentication aborted")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_SASLABORTED, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_SASLABORTED, ""), "906 * :SASL authentication aborted")

	LOG_TRACE("reply test: 907 ERR_SASLALREADY")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_SASLALREADY, "smiro"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_SASLALREADY, "smiro"),
		"907 smiro :You have already authenticated using SASL")
	LOG_TRACE(ft_irc::getReply(ft_irc::ERR_SASLALREADY, ""))
	ASSERT_EQ(ft_irc::getReply(ft_irc::ERR_SASLALREADY, ""), "907 * :You have already authenticated using SASL")

	LOG_TRACE("reply test: 908 RPL_SASLMECHS")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_SASLMECHS, "smiro", "mechaninsm"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_SASLMECHS, "smiro", "mechaninsm"),
		"908 smiro mechaninsm :are available SASL mechanisms")
	LOG_TRACE(ft_irc::getReply(ft_irc::RPL_SASLMECHS, "", "mechaninsm"))
	ASSERT_EQ(ft_irc::getReply(ft_irc::RPL_SASLMECHS, "", "mechaninsm"),
		"908 * mechaninsm :are available SASL mechanisms")
}	// ReplyUT::replies_tests
