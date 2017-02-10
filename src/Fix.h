#ifndef Bauer_Fix_H
#define Bauer_Fix_H

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

class Fix : public Event
{

	public:
		// CONSTRUCTORS
		Fix( long long int newExecutionTime, int newTargetNum )
		{
			executionTime = newExecutionTime;
			targetNum     = newTargetNum;
		}

		// VIRTUAL FUNCTION OVERRIDE
		virtual void perform( long long int            currentTime,
				      long long int &          lastFixTime,
				      int                      percentSuccess,
				      int                      percentDetect,
				      int		       numComputers,
				      std::vector<Computer*> & computerList,
				      MinBinHeap *&            eventQueue   )
		{
			computerList[targetNum]->setCompromised(false);
			computerList[targetNum]->setTimeCompromised(-1);
                        std::cout << "FIX: " << executionTime << ", "
                                  << targetNum << "\n";

		}


};

}
#endif
