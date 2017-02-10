#ifndef Bauer_Event_H
#define Bauer_Event_H

#include "Agent.h"       /* AttackerPerform, IDSPerform, SysAdminPerform */
#include "Attack.h"
#include "Computer.h"
#include "Environment.h" /* TIME_STEP, MAX_TIME, COMMAND_LINE_ERROE_MESSAGE */
#include "Event.h"
#include "Fix.h"
#include "MinBinHeap.h"
#include "Notify.h"
#include <iostream> /* cout, endl */
#include <math.h>   /* log10 */
#include <stdlib.h> /* atoi, rand, srand */
#include <string.h> /* strlen */
#include <stdio.h>  /* NULL */
#include <time.h>   /* time */
#include <vector>

namespace Bauer
{

class Event
{
	public:
		// ACCESSORS
		long long int getExecutionTime( ) const {return executionTime;}

		int getTargetNum( ) const { return targetNum; }

		// MUTATORS
		void setExecutionTime( long long int newExecutionTime )
			{ executionTime = newExecutionTime; }

		// VIRTUAL ACTION FUNCTION
		virtual void perform( long long int            currentTime,
				      long long int &          lastFixTime,
				      int                      percentSuccess,
				      int                      percentDetect,
				      int                      numComputers,
				      std::vector<Computer*> & computerList
				      MinBinHeap *&            eventQueue  );

	protected:
		// MEMBER VARIABLES
		long long int executionTime; // Time when event happens
		int           targetNum; // Number corresponding to target node
};

}
#endif
