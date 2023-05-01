#if !defined(CONFIGURATION_HPP)
#define CONFIGURATION_HPP

#include <map>
#include <string>
#include <vector>

#define CONFIG_FILE "irc_config.txt"

namespace ft_irc
{

class Configuration
{
private:
	std::string _server_name;
	int _port;
	std::string _password;
	std::vector< std::string > _admins;

public:

	Configuration(void);
	Configuration(const Configuration &s);
	~Configuration(void);

	Configuration& operator=(const Configuration &s);

	bool init_config(void);

	int get_port(void) const;
	const std::string& get_psswd(void) const;
	const std::vector< std::string > get_admins(void) const;
	const std::string& get_svname(void) const;
};	// class Configuration

}	// namespace ft_irc

#endif // CONFIGURATION_HPP
