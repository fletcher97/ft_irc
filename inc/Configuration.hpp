#if !defined(CONFIGURATION_HPP)
#define CONFIGURATION_HPP

#include <map>
#include <string>
#include <vector>

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

	int get_port(void);
	std::string get_psswd(void);
	std::vector< std::string > get_admins(void);
	std::string get_svname(void);
};	// class Configuration

}	// namespace ft_irc

#endif // CONFIGURATION_HPP
