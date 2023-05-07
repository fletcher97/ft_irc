#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Configuration.hpp"
#include "Log.hpp"
#include "Server.hpp"

ft_irc::Configuration::Configuration(void) :
	_server_name()
{
	LOG_DEBUG("Creating configuration")
	LOG_INFO("New configuration created")
}


ft_irc::Configuration::Configuration(const ft_irc::Configuration &s) :
	_server_name(s._server_name),
	_port(s._port),
	_password(s._password),
	_admins(s._admins)
{}

ft_irc::Configuration&
ft_irc::Configuration::operator=(const ft_irc::Configuration &s)
{
	this->_server_name = s._server_name;
	this->_port = s._port;
	this->_password = s._password;
	this->_admins = s._admins;

	return *this;
}	// =


ft_irc::Configuration::~Configuration(void) {}

bool
ft_irc::Configuration::init_config()
{
	std::ifstream config_file(CONFIG_FILE);

	if (!config_file.is_open()) {
		LOG_FATAL("Could not open configuration file")

		return false;
	}
	std::string line;
	int control = 1;

	while (std::getline(config_file, line)) {
		if (line.empty()) {
			continue;
		} else {
			size_t equal = line.find('=');

			if (equal == std::string::npos) {
				LOG_FATAL("Invalid parameter in irc_config file")

				return false;
			}
			std::string key = line.substr(0, equal - 1);
			std::string value = line.substr(equal + 2);

			if (key.substr(0, equal) == "name") {
				this->_server_name = value;
				ft_irc::Server::getInstance().setName(this->_server_name);
			} else if (key.substr(0, equal) == "port") {
				this->_port = atoi(value.c_str());
			} else if (key.substr(0, equal) == "password") {
				this->_password = value;
			} else if ((key.substr(0, equal) == "admin") && (control == 1)) {
				if ((value[0] != '[') || (value[value.size() - 1] != ']')) {
					return false;
				}
				size_t end = value.find_first_of(",]");

				while (end != (std::string::npos)) {
					std::string res = value.substr(1, end - 1);

					if (res.find_first_not_of(32) == std::string::npos) {
						return false;
					}
					value = value.substr(end + 1);
					this->_admins.push_back(res);
					end = value.find_first_of(",]");
				}
				control = 0;
			} else {
				LOG_FATAL("Invalid parameter in irc_config file")

				return false;
			}
		}
	}

	return true;
}	// Configuration::init_config


bool
ft_irc::Configuration::find_admin(std::string name) const
{
	unsigned long i = 0;

	while (i < this->_admins.size()) {
		if (this->_admins[i] == name) {
			return true;
		}
		i++;
	}

	return false;
}	// Configuration::find_admin


const std::string&
ft_irc::Configuration::get_svname(void) const
{
	return this->_server_name;
}	// Configuration::get_svname


const std::string&
ft_irc::Configuration::get_psswd(void) const
{
	return this->_password;
}	// Configuration::get_psswd


int
ft_irc::Configuration::get_port(void) const
{
	return this->_port;
}	// Configuration::get_port


const std::vector< std::string >
ft_irc::Configuration::get_admins(void) const
{
	return this->_admins;
}	// Configuration::get_admins
