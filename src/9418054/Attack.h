// This class holds the implementation for an Attack obj.
// Only successful attacks are passed to the queue.
// When the attack reaches execution time, it performs.
// This involves compromisig a certain computer and 
// possibly triggering a notify event.

class Attack : public Event
{
	private:
	//Number of source. -1 for the attacker and
	//integer for a computer
		int sourceNum;

	public:
		// CONSTRUCTORS
		Attack( long long int newExecutionTime,
			int           newTargetNum,
			int           newSourceNum     )
		: Event(newExecutionTime, newTargetNum)
		{
			sourceNum     = newSourceNum;
			eventNum      = 1;
		}

		// ACCESSORS
		int getSourceNum( ) const { return sourceNum; }

	//This class also holds the method for IDS action.
	//Only successful Notifications are sent to admin
		static void IDSPerform( long long int currentTime,
				        int           percentDetect,
				        int           targetNum,
				        int           sourceNum,
				        int           numComputers,
					MinBinHeap *& eventQueue    )
		{
		//Check if attaacker is attacking or if computers cross
		//switches in tree.
		   if(sourceNum == -1 || (targetNum <= numComputers/2
		   		       && sourceNum > numComputers/2)
				      || (targetNum > numComputers/2
				       && sourceNum <= numComputers/2))
		   {
			if ( (rand()%100 + 1) <= percentDetect )
			{
				Event* newNote =
		        	  new Notify(currentTime + Environment::LATENCY,
				             targetNum, sourceNum );
				eventQueue->insert( newNote );
			}
                   }

		}

		// Perform function for attack. Compromise computer and
		// trigger IDS possibility for notification.
		virtual void perform( long long int            currentTime,
				      long long int &          lastFixTime,
				      int                      percentSuccess,
				      int                      percentDetect,
				      int                      numComputers,
				      std::vector<Computer*> & computerList,
				      MinBinHeap *&            eventQueue  )
		{
			if ( !computerList[targetNum]->isCompromised() )
			{
				computerList[targetNum]->setCompromised(true);
				computerList[targetNum]->
					setTimeCompromised(currentTime);
			}

			IDSPerform( currentTime, percentDetect, targetNum,
				    sourceNum,   numComputers,  eventQueue );
			//Output message
			std::cout << "ATTACK: " << executionTime << ", "
				  << sourceNum << ", " << targetNum << "\n";
		}

};
