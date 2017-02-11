// This class holds the implementation of a FIX event.
// Similar to Attack and Notify

class Fix : public Event
{

	public:
		// CONSTRUCTORS
		Fix( long long int newExecutionTime, int newTargetNum )
		: Event( newExecutionTime, newTargetNum ) //super constructor
		{  eventNum = 3; }

		// Perform function for fix. Uncompromises computers and 
		// outputs message.
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

