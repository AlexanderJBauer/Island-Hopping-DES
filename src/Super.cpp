#include <iostream> /* cout, endl */
#include <math.h>   /* log10 */
#include <stdlib.h> /* atoi, rand, srand */
#include <string.h> /* strlen */
#include <stdio.h>  /* NULL */
#include <time.h>   /* time */
#include <vector>

#include "Environment.h"
#include "Event.h"
#include "MinBinHeap.h"
#include "Computer.h"
#include "Fix.h"
#include "Notify.h"
#include "Attack.h"

static void AttackerPerform( long long int currentTime,
			     int           percentSuccess,
			     int           percentDetect,
			     int           numComputers,
			     MinBinHeap *& eventQueue    )
{

	if ( (rand()%100 + 1) <= percentSuccess )
	{
		int targetNum = rand()%numComputers + 1;

		Event* newAttack = new Attack
			( currentTime + Environment::LATENCY, targetNum, -1 );

		eventQueue->insert( newAttack );
	}

}

void Notify::SysAdminPerform( long long int   currentTime,
			      long long int & lastFixTime,
			      int             targetNum,
			      int             sourceNum,
			      MinBinHeap *&   eventQueue   )
{
	if ( lastFixTime > currentTime )
	{
		Event* newFix = new Fix( lastFixTime + 10000, targetNum );

		eventQueue->insert( newFix );

		if ( sourceNum != -1 )
		{
			Event* newFix2= new Fix(lastFixTime + 10000, sourceNum);
			eventQueue->insert( newFix2 );
		}

		lastFixTime = lastFixTime + 10000;
	}
	else
	{
		Event* newFix = new Fix( currentTime + 10000, targetNum );
		eventQueue->insert( newFix );

		if ( sourceNum != -1 )
		{
			Event* newFix2= new Fix(currentTime + 10000, sourceNum);
			eventQueue->insert( newFix2 );
		}

		lastFixTime = currentTime + 10000;
	}
}


static void ComputerPerform( long long int   currentTime,
                             int             sourceNum,
                             int             percentSuccess,
                             int             numComputers,
                             MinBinHeap *&   eventQueue   )
{
	if ( (rand()%100 + 1) <= percentSuccess )
	{
		int targetNum = sourceNum;
		while (targetNum == sourceNum)
			targetNum = rand()%numComputers + 1;

		Event* newAttack = new Attack
			( currentTime + Environment::LATENCY, targetNum,
							      sourceNum );

		eventQueue->insert( newAttack );
	}

}

int main( int argc, char* argv[] )
{

	srand(time(NULL));
	const char*         COMMAND_LINE_ERROR_MESSAGE =
			"This program takes in 3 command line arguments.\n"
			"The order of the arguments is as follows:\n\n"

			"numComputers:\nDescribes the number of computers\n"
			"connected to the simulated corporate network\n"
			"under attack. The computers are split into two\n"
			"subgroups controlled by switches under the IDS."
			"\n**Argument is an integer x such that x > 1.\n\n"

			"percentSuccess:\nDescribes the chance an attacker\n"
			"conducts a successful attack on a network node\n"
			"(Computer)\n**Argument is an integer x such that "
			"0 <= x <= 100.\n\n"

			"percentDetect:\nDescribes the chance that the\n"
			"IDS (Intrusion Detection System) detects an\n"
			"attack. The attack can only be detected across\n"
			"network switches when a compromised node attacks\n"
			"another node. If the attacker attacks a node,\n"
			"there is always a chance the attack gets\n"
			"detected.\n**Argument is an integer x shuch that "
			"0 <= x <= 100.\n\n";

///////////////////////////////////////////////////////////////////////////////
	int numComputers   = 0;
	int percentSuccess = 0;
	int percentDetect  = 0;

	if ( argc != 4 )
	{
		std::cout << COMMAND_LINE_ERROR_MESSAGE;
		return 0;
	}
	else
	{
		numComputers   = atoi(argv[1]);
		percentSuccess = atoi(argv[2]);
		percentDetect  = atoi(argv[3]);

		if (numComputers < 1 || percentSuccess < 0
				     || percentDetect  < 0
				     || percentSuccess > 100
				     || percentDetect  > 100 )
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}

		if ( percentSuccess == 0 && strlen( argv[2] ) != 1 )
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}
		else if (percentSuccess    != 0 &&
			 strlen( argv[2] ) != (int)(log10(percentSuccess) + 1 ))
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}

		if ( percentDetect == 0 && strlen( argv[3] ) != 1 )
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}
		else if (percentDetect     != 0 &&
			 strlen( argv[3] ) != (int)(log10(percentDetect) + 1 ))
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}

		if ( strlen( argv[1] ) != (int)(log10(numComputers) + 1 ))
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}
	}
		std::cout << numComputers   << std::endl
			  << percentSuccess << std::endl
			  << percentDetect  << std::endl;
///////////////////////////////////////////////////////////////////////////////

	std::vector<Computer*> computerList;
	for( int i = 0; i <= numComputers; i++ )
		computerList.push_back(new Computer(i));

	MinBinHeap* eventQueue = new MinBinHeap(300);

	long long int currentTime    = 1000;
	long long int lastFixTime    = 0;
	long long int nextExec       = 0;
	int           numCompromised = 0;
	int           numPopped      = 0;
	Event*        lastDelete;

	while ( currentTime <= Environment::MAX_TIME )
	{
		numCompromised = 0;

		if ( currentTime % 1000 == 0 )
			AttackerPerform( currentTime, percentSuccess,
					 percentDetect, numComputers,
					 eventQueue                  );

		for( int i = 1; i <= numComputers; i++ )
		{
			if ( computerList[i]->isCompromised() )
			{
				if ( ((currentTime
                                      -computerList[i]->getTimeCompromised())
				      %1000) == 0 )
				{
					ComputerPerform( currentTime,
							 i,
							 percentSuccess,
							 numComputers,
							 eventQueue  );
				}
				numCompromised++;
			}
		}

		if ( numCompromised >= numComputers/2)
		{
			std::cout << "Attacker wins\n";
			return 0;
		}

		if ( numPopped > 0 && numCompromised == 0 )
		{
			std::cout << "System Administrator wins\n";
			return 0;
		}

		if ( eventQueue->getCurrentSize() != 0 )
		{

			nextExec = eventQueue->findMin()->getExecutionTime();
			while ( nextExec == currentTime
				&& eventQueue->getCurrentSize() != 0 )
			{
				lastDelete = eventQueue->deleteMin( );

				if (lastDelete->getEventNum() == 1)
				{
					dynamic_cast<Attack*>(lastDelete)->
						perform(currentTime,
						    lastFixTime,
						    percentSuccess,
						    percentDetect, numComputers,
						    computerList, eventQueue);
				}

				if (lastDelete->getEventNum() == 2)
				{
					dynamic_cast<Notify*>(lastDelete)->
						perform(currentTime,
						    lastFixTime,
						    percentSuccess,
						    percentDetect, numComputers,
						    computerList, eventQueue);
				}

				if (lastDelete->getEventNum() == 3)
				{
					dynamic_cast<Fix*>(lastDelete)->
						perform(currentTime,
						    lastFixTime,
						    percentSuccess,
						    percentDetect, numComputers,
						    computerList, eventQueue);
				}

				nextExec =
				     eventQueue->findMin()->getExecutionTime();

				numPopped ++;
			}
		}

		currentTime = currentTime + Environment::TIME_STEP;
	}
	std::cout << "Its a draw\n";
	return 0;

}
