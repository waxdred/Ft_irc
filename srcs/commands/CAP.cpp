#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command COPA
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	CAP(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 2 || cmd.params[0] != "LS" || cmd.params[1] != "302") {
			std::cerr << RED << serv.getLog() << "CAP: error" << NC << std::endl;
			user.sendCommand(":Please change your client \n go to hell");
			return;
		}
		user.setCap(true);
	}
} // namespace irc
