#pragma once

#include "../includes.hpp"

namespace irc
{

class Server;

/**
 * @brief Have all information of a user and allow to send a message
 * at the user
 */
class User
{
	private:
		int			_socketFd;
		std::string	_username; // unique
		std::string	_nickname; // pseudo
		std::string	_realname; // visual
		std::string	_hostname;
		std::string	_servername;
		UserMode	_mode;
		bool		_pass;
	public:
		User(void);
		User(int fd);
		User(const User& ref);
		~User(void);

		// getter

		int			getSocketFd(void) const;
		std::string	getUsername(void) const;
		std::string	getNickname(void) const;
		std::string	getRealname(void) const;
		std::string	getHostname(void) const;
		std::string	getServername(void) const;
		bool		getPass(void) const;
		// getter modes

		bool	isInvisible(void) const;
		bool	isServerNotice(void) const;
		bool	isWallOps(void) const;
		bool	isOperatorServer(void) const;


		// setter

		User&	setSocketFd(const int socketFd);
		User&	setUsername(const std::string& val);
		User&	setNickname(const std::string& val);
		User&	setRealname(const std::string& val);
		User&	setHostname(const std::string& val);
		User&	setServername(const std::string& val);
		User&	setPass(const bool val);
		// setter modes

		User&	beInvisible(const bool boolean);
		User&	beServerNotice(const bool boolean);
		User&	beWallOps(const bool boolean);
		User&	beOperatorServer(const bool boolean);
		// utility

		int		sendCommand(const std::string& command) const;
}; // class User

/**
 * @brief Checck the respect requirements of the registration
 * 
 * @param user the user
 * @return true if user respect requirements of the registration, else false
 */
bool	isRegister(const User& user);

} // namespace irc


