#ifndef Bauer_Attack_H
#define Bauer_Attack_H

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

class Attack : public Event
{

	public:
		// CONSTRUCTORS
		Attack( long long int newExecutionTime,
			int           newTargetNum,
			int           newSourceNum     )
		{
			executionTime = newExecutionTime;
			targetNum     = newTargetNum;
			sourceNum     = newSourceNum;
		}

		// ACCESSORS
		int getSourceNum( ) const { return sourceNum; }

		// VIRTUAL FUNCTION OVERRIDE
		virtual void perform( long long int            currentTime,
				      long long int &          lastFixTime,
				      int                      percentSuccess,
				      int                      percentDetect,
				      int                      numComputers,
				      std::vector<Computer*> & computerList,
				      MinBinHeap *&            eventQueue  );
		{
			if ( !computerList[targetNum]->isCompromised() )
			{
				computerList[targetNum]->setCompromised(true);
				computerList[targetNum]->
					setTimeCompromised(currentTime);
			}

			IDSPerform( currentTime, percentDetect, targetNum,
						 sourceNum,     eventQueue );

			std::cout << "ATTACK: " << executionTime << ", "
				  << sourceNum << ", " << targetNum << "\n";
		}

	private:
		int sourceNum;

};

}
#endif
