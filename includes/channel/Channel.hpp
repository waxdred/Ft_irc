#pragma once

#include "../includes.hpp"


 /*  A channel is a named group of one or more clients which will all
   receive messages addressed to that channel.  The channel is created
   implicitly when the first client joins it, and the channel ceases to					=> ft_join de la classe precedent implique constructeur si channel n existe pas
   exist when the last client leaves it.  While channel exists, any															=> sinon fonctionjoin de serveur de la classe channel
   client can reference the channel using the name of the channel 
*/

//        KICK    - Eject a client from the channel					reservé a l operator. modo?
//        MODE    - Change the channel's mode
//        INVITE  - Invite a client to an invite-only channel (mode +i)
//        TOPIC   - Change the channel topic in a mode +t channel





// creer classe mods
namespace irc { 
	class Channel {
		private:
			std::string		_channelName;//Channels names are strings (beginning with a '&' or '#' character) of length up to 200 characters. pas de ' ' , ',' ou ascii 7 (ctrl g)
			bool			_private;
			std::string		_password;

			int				_userLimits;

			std::list<int>	_users;		
			std::list<int>	_bans;		
			std::list<int>	_operators;	     

			void		sendMessage();
			bool		checkMessage();

			void		addToConnectedList();
			void		addToDeconnectedList();

			void		giveRights();
			void		changeMods();
			void		renameTopic();
			void		kickUser();

			bool		checkUserRights(); // => j utilise @ ou une autre variable?
			bool		checkPassword();

		public:
			std::string getChannelName();
			//	Mods			*getMods();
			bool		getPrivateBool();
			bool		isInChannel();
			bool		isInBanList();
			bool		isInOperatorList();

			void		addToOperatorList();
			void		addToBanList();  // if in channel => kik (fonction?)
			void		applyNewMods();
			void		joinChannel();
			void		inviteToChannel();
			void		expulse();
			// comment gerer le fait de leave le channel : check si tjrs connecté? ou appel d une fct de deconnection

			Channel( std::string name, bool privatebool, std::string password );
			~Channel();

	};
}


/*
 4.2 Channel operations

   This group of messages is concerned with manipulating channels, their
   properties (channel modes), and their contents (typically clients).
   In implementing these, a number of race conditions are inevitable
   when clients at opposing ends of a network send commands which will
   ultimately clash.  It is also required that servers keep a nickname
   history to ensure that wherever a <nick> parameter is given, the
   server check its history in case it has recently been changed.

4.2.1 Join message

      Command: JOIN
   Parameters: <channel>{,<channel>} [<key>{,<key>}]

   The JOIN command is used by client to start listening a specific
   channel. Whether or not a client is allowed to join a channel is
   checked only by the server the client is connected to; all other
   servers automatically add the user to the channel when it is received
   from other servers.  The conditions which affect this are as follows:

           1.  the user must be invited if the channel is invite-only;

           2.  the user's nick/username/hostname must not match any
               active bans;

           3.  the correct key (password) must be given if it is set.

   These are discussed in more detail under the MODE command (see
   section 4.2.3 for more details).

   Once a user has joined a channel, they receive notice about all
   commands their server receives which affect the channel.  This
   includes MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.	!!!!!!!!!!!!!!   
   The JOIN command needs to be broadcast to all servers so that each server
   knows where to find the users who are on the channel.  This allows
   optimal delivery of PRIVMSG/NOTICE messages to the channel.		!!!!!!!!!!!!!!

   If a JOIN is successful, the user is then sent the channel's topic
   (using RPL_TOPIC) and the list of users who are on the channel (using
   RPL_NAMREPLY), which must include the user joining.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
           ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
           ERR_CHANNELISFULL               ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
           RPL_TOPIC

   Examples:

   JOIN #foobar                    ; join channel #foobar.

   JOIN &foo fubar                 ; join channel &foo using key "fubar".

   JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
                                   and &bar using no key.

   JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
                                   and channel #bar using key "foobar".

*/