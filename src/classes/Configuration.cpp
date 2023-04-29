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


ft_irc::Configuration::Configuration(const ft_irc::Configuration&)
{}

ft_irc::Configuration&
ft_irc::Configuration::operator=(const ft_irc::Configuration&)
{
	return *this;
}	// =


ft_irc::Configuration::~Configuration(void) {}

bool
ft_irc::Configuration::init_config()
{
	std::ifstream config_file("irc_config.txt");

	if (!config_file.is_open()) {
		std::cerr << "Error: Could not open configuration file" << std::endl;

		return false;
	}
	std::string line;

	while (std::getline(config_file, line)) {
		if (line.empty()) {
			continue;
		} else {
			size_t equal = line.find('=');

			if (equal == std::string::npos) {
				std::cerr << "Invalid configuration" << std::endl;

				return false;
			}

			std::string key = line.substr(0, equal);
			std::string value = line.substr(equal + 2);

			if (key.substr(0, equal - 1) == "name") {
				this->_server_name = value;
			} else if (key.substr(0, equal - 1) == "port") {
				this->_port = atoi(value.c_str());
			} else if (key.substr(0, equal - 1) == "password") {
				this->_password = value;
			} else if (key.substr(0, equal - 1) == "admin") {
				this->_admins.push_back(value);
			} else {
				LOG_FATAL("Invalid parameter in irc_config file")

				return false;
			}
		}
	}

	return true;
}	// Configuration::init_config


std::string
ft_irc::Configuration::get_svname(void)
{
	return this->_server_name;
}	// Configuration::get_svname


std::string
ft_irc::Configuration::get_psswd(void)
{
	return this->_password;
}	// Configuration::get_psswd


int
ft_irc::Configuration::get_port(void)
{
	return this->_port;
}	// Configuration::get_port


std::vector< std::string >
ft_irc::Configuration::get_admins(void)
{
	return this->_admins;
}	// Configuration::get_admins
