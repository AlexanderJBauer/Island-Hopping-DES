#include "Agent.h"
#include <stdlib.h> /* rand */

namespace Bauer{

void Agent::AttackerPerform( long long int currentTime,
			     int           percentSuccess,
			     int           percentDetect,
			     int           numComputers,
			     MinBinHeap &  eventQueue       )
{

	if ( (rand()%100 + 1) <= percentSuccess )
	{
		targetNum = rand()%numComputers + 1;

		Attack newAttack =
		    new Attack( currentTime + Environment::LATENCY, targetNum );
		eventQueue.insert( newAttack );

		Agent::IDSPerform( currentTime + Environment::LATENCY,
				   percentDetect, targetNum, -1, eventQueue )
	}
}

void Agent::SysAdminPerform( long long int   currentTime,
			     long long int & lastFixTime,
			     int             targetNum,
			     int             sourceNum,
			     MinBinHeap &    eventQueue   )
{
	if ( lastFixTime > currentTime )
	{
		Fix newFix = new Fix( lastFixTime + 10000, targetNum );
		eventQueue.insert( newFix );

		if ( sourceNum != -1 )
		{
			Fix newFix2 = new Fix( lastFixTime + 10000, sourceNum );
			eventQueue.insert( newFix2 );
		}

		lastFixTime = lastFixTime + 10000;
	}
	else
	{
		Fix newFix = new Fix( currentTime + 10000, targetNum );
		eventQueue.insert( newFix );

		if ( sourceNum != -1 )
		{
			Fix newFix2 = new Fix( currentTime + 10000, sourceNum );
			eventQueue.insert( newFix2 );
		}

		lastFixTime = currentTime + 10000;
	}
}

void Agent::IDSPerform( long long int currentTime,
		        int           percentDetect,
		        int           targetNum,
		        int           sourceNum,
		        MinBinHeap &  eventQueue    )
{
	if ( (rand()%100 + 1) <= percentDetect )
	{
		Notify newNote =
		        new Notify(currentTime + Environment::LATENCY,
				   targetNum, sourceNume );
		eventQueue.insert( newNote );
	}

}

}