// This class holds the representation of a Notify event

class Notify : public Event
{

	public:
		// CONSTRUCTORS
		Notify( long long int newExecutionTime,
			int           newTargetNum,
			int           newSourceNum      )
		: Event( newExecutionTime, newTargetNum )
		{
			sourceNum     = newSourceNum;
			eventNum      = 2;
		}

		// ACCESSORS
		int getSourceNum( ) const { return sourceNum; }

		// Method for SysAdminAction defined in Super.cpp
		static void SysAdminPerform( long long int   currentTime,
			     		     long long int & lastFixTime,
			     		     int             targetNum,
			     		     int             sourceNum,
			     		     MinBinHeap *&   eventQueue   );

		// Perform function for notify event
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
