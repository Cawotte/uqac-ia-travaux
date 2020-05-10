#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_ImInTheSaloon,
  Msg_StartingAFight
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

      return "ImInTheSaloon";

  case 3:

      return "StartingAFight";

  default:

    return "Not recognized!";
  }
}

#endif