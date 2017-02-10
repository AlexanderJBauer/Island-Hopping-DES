#ifndef Bauer_Fix_H
#define Bauer_Fix_H


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
