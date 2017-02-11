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

		static void SysAdminPerform( long long int   currentTime,
			     		     long long int & lastFixTime,
			     		     int             targetNum,
			     		     int             sourceNum,
			     		     MinBinHeap *&   eventQueue   );

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
