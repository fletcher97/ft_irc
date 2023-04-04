#if !defined(CONFIGURATION_HPP)
#define CONFIGURATION_HPP

#include <string>
#include <map>

namespace ft_irc
{

class Configuration
{
protected:

public:
	Configuration(void);
	Configuration(const Configuration& s);
	~Configuration(void);
	Configuration& operator=(const Configuration& s);

	bool	get_config(void);

	struct ServerConfig {
    std::string name;
    int port;
    std::string password;
    std::vector<std::string> admins;
};

};

}

#endif // CONFIGURATION_HPP
