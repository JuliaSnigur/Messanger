#pragma once

namespace Data
{
    enum request {Info, Connection, Registration, Authorization, Message, File, FileBlock, GetListOfFriends,GetID, GetFriend};
    enum stateMessage {Send, Get};
    enum file {SendFile,  Finish};
}
