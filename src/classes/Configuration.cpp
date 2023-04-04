#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Configuration.hpp"
#include "Server.hpp"
#include "Log.hpp"

ft_irc::Configuration::Configuration(void)
{
    LOG_DEBUG("Creating configuration")
    LOG_INFO("New configuration created")
}

ft_irc::Configuration::Configuration(const ft_irc::Configuration&)
{}

ft_irc::Configuration&
ft_irc::Configuration::operator=(const ft_irc::Configuration& s) {
     if (this == &s)
        return *this;
    return *this;
}

ft_irc::Configuration::~Configuration(void) {}

bool get_config()
{
    std::ifstream config_file("irc_config.txt");

    if (!config_file.is_open())
    {
        std::cerr << "Error: Could not open configuration file" << std::endl;
        return 1;
    }

    ft_irc::Configuration::ServerConfig server_config;
    std::string line;
    
    while (std::getline(config_file, line))
    {
        if (line.empty())
            continue;
        else 
        {
            size_t equal = line.find('=');

            if (equal != std::string::npos) 
            {
                std::string key = line.substr(0, equal);
                std::string value = line.substr(equal + 2);

                if (key.substr(0, 4) == "name")
                    server_config.name = value;
                else if (key.substr(0, 4) == "port")
                    server_config.port = std::stoi(value);
                else if (key.substr(0, 8) == "password")
                    server_config.password = value;
                else if (key.substr(0, 5) == "admin")
                    server_config.admins.push_back(value);
                else
                {
                    LOG_FATAL("Invalid parameter in irc_config file")
                    return (false);
                }
            }
        }
    }
    return true;
}
