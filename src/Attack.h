#ifndef Bauer_Attack_H
#define Bauer_Attack_H

#include "Agent.h"

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
				      std::vector<Computer*> & computerList )
		{
			if ( !computerList[targetNum]->isCompromised() )
			{
				computerList[targetNum]->setCompromised(true);
				computerList[targetNum]->
					setTimeCompromised(currentTime);
			}
		}
	private:
		int sourceNum;
};

}
#endif
