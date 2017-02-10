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
		virtual void perform( long long int            currentTime,
				      long long int &          lastFixTime,
				      int                      percentSuccess,
				      int                      percentDetect,
				      int                      numComputers,
				      std::vector<Computer*> & computerList,
				      MinBinHeap *&            eventQueue  )
		{
			SysAdminPerform( currentTime, lastFixTime, targetNum,
						      sourceNum,   eventQueue);
                        std::cout << "NOTIFY: " << executionTime << ", "
                                  << sourceNum << ", " << targetNum << "\n";
		}

	private:
		int sourceNum;
};

}
#endif
