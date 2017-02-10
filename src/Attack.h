#ifndef Bauer_Attack_H
#define Bauer_Attack_H

#include "Agent.h"
#include <iostream>

namespace Bauer
{

class Attack : public Event
{

	public:
		// CONSTRUCTORS
		Attack( long long int newExecutionTime,
			int           newTargetNum
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
