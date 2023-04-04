#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct ServerConfig {
    std::string name;
    int port;
    std::string password;
    std::vector<std::string> admins;
};

int main()
{
    std::ifstream config_file("irc_config.txt");

    if (!config_file.is_open())
    {
        std::cerr << "Error: Could not open configuration file" << std::endl;
        return 1;
    }

    ServerConfig server_config;
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

                std::cout << "VALOR: " << value << std::endl;

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
                    std::cerr << "Invalid parameter in irc_config file" << std::endl;
                    exit (1);
                }
            }
        }
    }
    return 0;
}