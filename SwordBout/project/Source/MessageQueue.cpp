#include "MessageQueue.h"
#include <assert.h>

MessageQueue::MessageQueue()
{
}

MessageQueue::~MessageQueue()
{
}

bool MessageQueue::ReceiveMessage(int command, Param param)
{
    Node node;
    node.command = command;
    node.param = param;

    //Queue‚ª‚¢‚Á‚Ï‚¢‚È‚çAfalse‚É‚·‚é
    if ((writeIdx + 1) % 32 == readIdx) {
        assert(false);
        return false;
    }
    queue[writeIdx] = node;
    if (++writeIdx >= 32)
        writeIdx = 0;
    return true;
}

int MessageQueue::PopMessage(Param* param)
{
    if (readIdx == writeIdx)
        return -1;
    int ret = queue[readIdx].command;
    if (param!=nullptr)
        *param = queue[readIdx].param;
    readIdx = (readIdx + 1) % 32;
    return ret;
}
