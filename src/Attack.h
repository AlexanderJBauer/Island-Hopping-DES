class Attack : public Event
{
	private:
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

		static void IDSPerform( long long int currentTime,
				        int           percentDetect,
				        int           targetNum,
				        int           sourceNum,
				        MinBinHeap *& eventQueue    )
		{
			if ( (rand()%100 + 1) <= percentDetect )
			{
				Event* newNote =
		        	  new Notify(currentTime + Environment::LATENCY,
				             targetNum, sourceNum );
				eventQueue->insert( newNote );
			}


		}

		// VIRTUAL FUNCTION OVERRIDE
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
						 sourceNum,     eventQueue );

			std::cout << "ATTACK: " << executionTime << ", "
				  << sourceNum << ", " << targetNum << "\n";
		}

};
