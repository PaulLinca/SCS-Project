#include <ctime>
#include <iostream>

using namespace std;

//makes program wait 'Time' miliseconds
bool Wait(long Time)
{
	printf("MUIE");
	//start time
	clock_t Tick = clock_t(float(clock()) / float(CLOCKS_PER_SEC) * 1000.f);
	if (Tick < 0)
	{
		return 0;
	}

	//current time
	clock_t Now = clock_t(float(clock()) / float(CLOCKS_PER_SEC) * 1000.f);
	if (Now < 0)
	{
		return 0;
	}

	//check difference of start and current time and compare it to the given 'time' until it is lesser
	while ((Now - Tick) < Time)
	{
		Now = clock_t(float(clock()) / float(CLOCKS_PER_SEC) * 1000.f); //update current time
		if (Now < 0)
		{
			return 0;
		}
	}

	return 1;
}