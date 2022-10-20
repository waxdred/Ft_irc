#include "../../includes/includes.hpp"

namespace irc
{
	static void mode(Server& serv, User &user, Command& cmd, mapChannelIterator id, char c, MODE_FLAG flag){
		c = ::tolower(c);
		mapChannel channel = serv.getMapChannel();
		switch (c) {
			case 'k':
				changePassword(cmd, id->second, flag);
				break;
			case 'l':
				try{
					changeUserLimitMode(cmd, id->second, flag);
				}catch (const std::exception& ){
					user.sendCommand(ERR_UMODEUNKNOWNFLAG(cmd.params[0]));
				}
				break;
			case 'p':
				changePrivateFlag(id->second, flag);
				break;
			case 'b':
				changeBanList(cmd, id->second, flag);
				break;
			case 't':
				changeTopic(id->second, flag);
				break;
			case 'i':
				changeInvite(id->second, flag);
				break;
			case 's':
				changeSecret(id->second, flag);
				break;
			case 'o':
				changeOps(cmd, id->second, flag);
				break;
			default:
				std::cout << "Error flag not found" << std::endl;
			
		}
	}
	/**
	 * @brief apply command PASS
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	MODE(Server& serv, User& user, Command& cmd) {
		std::vector<std::string>                target;
		std::vector<std::string>::iterator      it;
		if (cmd.params.size() < 1) {
			std::cout << RED << serv.getLog() << "PASS: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS("PASS", ""));
			return;
		}else if (cmd.params[1].size() == 0 || cmd.params[1].size() > 2){
			std::cout << RED << serv.getLog() << "MODE: ERROR flag " << NC << std::endl;
			user.sendCommand(ERR_UMODEUNKNOWNFLAG(cmd.params[0]));
			return;
		}
		mapChannelIterator id = serv.getMapChannel().find(cmd.params[0]);
		if ((cmd.params[0].size() > 0 && serv.isInMapChannel(cmd.params[0]) && id->second.isInOperatorList(user.getNickname())) || 
				(cmd.params[0][0] == '#' || cmd.params[0][0] == '&')){
			if (cmd.params[1].size() > 1 && cmd.params[1][0] == '+'){
				mode(serv, user, cmd, id, cmd.params[1][1],  MORE);
			}else if (cmd.params[1].size() > 1 && cmd.params[1][0] == '-'){
				mode(serv, user, cmd, id, cmd.params[1][1],  LESS);
			}else if (cmd.params[1].size() == 1){
				mode(serv, user, cmd, id, cmd.params[1][1],  NORM);
			}
		}
	}
}
		/* if (cmd.params[0][0] == '#' || cmd.params[0][0] == '&'){ mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]); if(!it->second.isInOperatorList(user.getNickname())){ */
		/* 		std::cerr << "ERR_NOTINOPERLIST\n"; */
		/* 	} */
		/* 	else { */
		/* 		if (cmd.params[1][0] == 'k'){ */
		/* 			it->second.changeChanPassword(cmd.params[2]); */
		/* 		} */
		/* 		if (cmd.params[1][0] == 'p'){ */
		/* 			it->second.changePrivFlag(); */
		/* 		} */
		/* 		if (cmd.params[1][0] == 'l'){ */
		/* 			int val = stoi(cmd.params[2]); */
		/* 			if (val > 1) */
		/* 				it->second.changeUserLimit(val); */
		/* 			else */
		/* 				std::cerr << "ERR_WRONGARGmdr\n"; */
		/* 		} */
		/* 		if (cmd.params[1][0] == 'b'){ */
		/* 			User ban; */
		/* 			ban.setNickname(cmd.params[2]); */
		/* 			it->second.addToBanList(ban); */
		/* 		} */
		/* 		if (cmd.params[1][0] == 't'){ */
		/* 			it->second.getMods().changeTopicFlag(); */
		/* 		} */
		/* 		if (cmd.params[1][0] == 'i'){ */
		/* 			it->second.getMods().changeInviteFlag(); */
		/* 		} */
		/* 		if (cmd.params[1][0] == 's'){ */
		/* 			it->second.getMods().changeSecretFlag(); */
		/* 		} */
		/* 		if (cmd.params[1] == "+o"){ */
		/* 			User op; */
		/* 			op.setNickname(cmd.params[2]); */
		/* 			it->second.giveRights(op); */
		/* 		} */
		/* 		if (cmd.params[1] == "-o"){ */
		/* 			User op; */
		/* 			op.setNickname(cmd.params[2]); */
		/* 			it->second.delFromOperatorList(op); */
		/* 		} */
		/* 	} */
