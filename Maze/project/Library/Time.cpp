#include "time.h"
#include <Windows.h>

namespace {
	LARGE_INTEGER freq;
	LARGE_INTEGER current;
	float deltaTime;
	const int BUF_SIZE = 20;
	struct RingBuffer {
		float buf[BUF_SIZE];
		int read;
		int write;

		RingBuffer() {
			read = 0;
			write = 0;
		}

		void Push(float rec) {
			buf[write] = rec;
			write = (write+1) % BUF_SIZE;
			if (write==read) {
				read = (read+1) % BUF_SIZE;
			}
		}
		
		float Average() {
			float sum = 0;
			int n = 0;
			for (int i = read; i != write; i=(i+1)%BUF_SIZE) {
				sum+= buf[i];
				n++;
			}
			if (n == 0) {
				return 1.0f/60.0f;
			}
			return sum/n;
		}
	};
	RingBuffer timeRecord;
};

void Time::Init()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&current);
}

void Time::Refresh()
{
	LARGE_INTEGER last = current;
	QueryPerformanceCounter(&current);
	deltaTime = static_cast<float >(current.QuadPart - last.QuadPart) / freq.QuadPart;
	float ave = timeRecord.Average();
	if (deltaTime > ave * 2.0f) {
		deltaTime = ave * 2.0f;
	}
	timeRecord.Push(deltaTime);
}

float Time::DeltaTime()
{
	return deltaTime;
}

void Time::Release()
{
}