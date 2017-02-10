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
		virtual void perform( )
		{
			

	private:
		int sourceNum;
};

}
#endif
