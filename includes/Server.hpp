#pragma once

#include "includes.hpp"


// ** User

// type of a list of User class
typedef std::list<irc::User>				listUser;
// type of iterator on listUser
typedef listUser::iterator					listUserIterator;
// type of const_iterator on listUser
typedef listUser::const_iterator			listUserConstIterator;
// type of a map of <fd - User class>
typedef std::map<int, irc::User>			mapUser;
// type of iterator on mapUser
typedef mapUser::iterator					mapUserIterator;
// type of const_iterator on mapUser
typedef mapUser::const_iterator				mapUserConstIterator;
// type of a pair of the mapUser
typedef std::pair<int, irc::User>			pairUser;

// ** Parsing

// type of a map of <fd - Parsing class>
typedef std::map<int, irc::Parsing>			mapParse;
// type of an iterator on mapParse
typedef mapParse::iterator					mapParseIterator;

// ** Command

// type of function pointer for a command
typedef void (*functionPtr)(irc::Server&, irc::User&, irc::Command&);
// type of a map of <command - function pointers on commands>
typedef std::map<std::string, functionPtr>	mapCommand;
// type of a const iterator on a mapCommand
typedef mapCommand::const_iterator			mapCommandConstIterator;
// type of a pair of the mapCommand
typedef std::pair<std::string, functionPtr>	pairCommand;


namespace irc
{
	/**
	 * @brief General class of ft_irc.
	 * Contain all users and channel.
	 * Manage connections of clients.
	 * Execute commands received.
	 */
	class Server 
	{
		private:
			// Server infos
			
			// Server port
			u_int32_t			_port;
			// Server port
			std::string			_portString;
			// Server password
			std::string			_pwd;
			// socket infos
			struct sockaddr_in	_sockAddr;
			// fd of the server socket
			int					_sockServ;
			// map with all the command
			const mapCommand	_commands;

			// User infos

			// online users
			listUser			_onlineUsers;
			// offline users
			listUser			_offlineUsers;
			// online users not register
			mapUser				_waitingUsers;
			// parsing per fd
			mapParse			_Parse;
			// Debug
			Log					_log;

			void		createServer(void);
			void		runServer(void) const;
			void		acceptNewConnection(fd_set&	currentSocket, int& max_fd);
			void		handleClient(fd_set& currentSocket, const int fd, int& max_fd);
			void		killSocket(fd_set& currentSocket, const int fd, int& max_fd);
            void        ExecuteCmd(int fd);

			static mapCommand	initCmd(void);
		public:
			Server(const std::string& port, const std::string& pwd);
			~Server(void);
			listUser&	getOnlineUsers();
			listUser&	getOfflineUsers();
			mapUser&	getWaitingUsers();
			Log		    getLog();
			void		connect(void);
            void    	SendClient(int fd, const std::string &msg);
			void    	display(void);
			User*		getUser(int fd);
	};
} // namespace irc











































































































































































































































































































































































