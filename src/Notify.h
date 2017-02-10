#ifndef Bauer_Notify_H
#define Bauer_Notify_H

#include "Attack.h"

namespace Bauer
{

class Notify : public Event
{

	public:
		// CONSTRUCTORS
		Notify( long long int newExecutionTime,
			int           newTargetNum,
			int           newSourceNum      )
		{
			executionTime = newExecutionTime;
			targetNum     = newTargetNum;
			sourceNum     = newSourceNum;
		}

		// ACCESSORS
		int getSourceNum( ) const { return sourceNum; }

		// VIRTUAL FUNCTION OVERRIDE
		virtual void perform( );

	private:
		int sourceNum;
};

}
#endif
