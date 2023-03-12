//throw std::invalid_argument("Invalid nickname");

#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <poll.h>
#include <stdexcept>
#include <unistd.h>

#include "Communications.hpp"
#include "Server.hpp"
#include "Log.hpp"

Communications::Communications(int port, std::string psswd) {
	LOG_DEBUG("Creating communitation");
	LOG_INFO("New communitation created");
	if (port < 1023 || port > 65535)
		write_error("Invalid port");
	this->port = port;
	this->_psswd = psswd;
}

Communications::Communications(const Communications &s) {
	this->port = s.port;
	this->_psswd = s._psswd;
}

Communications &Communications::operator=(const Communications &s) {
	this->_psswd = s._psswd;
	this->port = s.port;
	return *this;
}

Communications::~Communications() {
}

bool Communications::is_digits(const std::string &str)
{
    return (str.find_first_not_of("0123456789") == std::string::npos);
}


void Communications::write_error(const char *s)
{
    std::cerr << s << std::endl;
    exit (EXIT_FAILURE);
}

void Communications::init_server(void)
{
	this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_socket == -1)
        write_error("Error creating socket");

    memset(&this->server_address, 0, sizeof(this->server_address));
    this->server_address.sin_family = AF_INET;
    this->server_address.sin_addr.s_addr = INADDR_ANY;
    this->server_address.sin_port = htons(this->port);

    if (bind(this->server_socket, reinterpret_cast<struct sockaddr*>(&this->server_address), sizeof(this->server_address)) == -1)
        write_error("Error binding"); //error al asociar el socket a la direccion del servidor

    if (listen(this->server_socket, MAX_CLIENTS) == -1)
        write_error("Error listening"); //error al escuchar conexiones entrantes

    this->fd_array[0].fd = this->server_socket;
    this->fd_array[0].events = POLLIN;

    this->num_fds = 1;

    //std::vector<int> vec_clients;
    std::cout << "Listening on port " << port << std::endl;
}

void Communications::run(void)
{
    while (42)
    {
        if (poll(fd_array, num_fds, -1) == -1)
        {
            std::cerr << "Error poll" << std::endl;
            continue;
        }

        for (int i = 0; i < num_fds; i++)
        {
            if (fd_array[i].revents == 0)
                continue;

            // check nueva conexion
            if (fd_array[i].fd == server_socket)
            {
                int client_fd = accept(server_socket, nullptr, nullptr);
                if (client_fd == -1)
                {   
                    std::cerr << "Error accepting incoming connection" << std::endl;
                    continue;
                }
                if (num_fds == MAX_CLIENTS)
                {
                    std::string welcome_msg = "The server is full. Please try again later.\n";
                    send(client_fd, welcome_msg.c_str(), welcome_msg.length(), 0);
                    close(client_fd);
                    continue;
                }
                vec_clients.push_back(client_fd);
                fd_array[num_fds].fd = client_fd;
                fd_array[num_fds].events = POLLIN;
                num_fds++;
                std::string welcome_msg = "Bienvenido al servidor IRC\n";
                send(client_fd, welcome_msg.c_str(), welcome_msg.length(), 0);

                std::cout << "New client FD = " << client_fd << std::endl;
            }
            else 
            {
                char buffer[512];
                memset(buffer, 0, sizeof(buffer));
                int bytes_received = recv(fd_array[i].fd, buffer, sizeof(buffer), 0);
                buffer[bytes_received] = '\0';

                if (bytes_received == -1) 
                {
                    std::cerr << "Error receiving customer data FD = " << fd_array[i].fd << std::endl;
                    continue;
                }

                if (bytes_received == 0) //si un cliente se desconecta se cierra su socket, se elimina del vector y se elimina el evento de la estructura
                {
                    vec_clients.erase(std::remove(vec_clients.begin(), vec_clients.end(), fd_array[i].fd), vec_clients.end());
                    std::cout << "Client disconnected FD = " << fd_array[i].fd << std::endl;
                    close(fd_array[i].fd);
                    for (int j = i; j < num_fds; j++)
                    {
                        fd_array[j].fd = fd_array[j + 1].fd;
                        fd_array[j].events = fd_array[j + 1].events;
                    }
                    num_fds--;
                }
                else
                {
                    std::cout << buffer;
                    //send(fd_array[i].fd, buffer, bytes_received, 0);
                }
            }
        }
    }
}
