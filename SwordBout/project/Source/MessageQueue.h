#pragma once
// MessageQueue.h
#include <array>

class MessageQueue {
public:
	MessageQueue();
	~MessageQueue();
	union Param {
		int intVal;
		float floatVal;
		void* ptrVal;
	};
	bool ReceiveMessage(int command, Param param);
	int PopMessage(Param* param = nullptr);
private:
	struct Node {
		int command;
		Param param;
	};

	std::array<Node, 32> queue;
	int writeIdx;
	int readIdx;
};