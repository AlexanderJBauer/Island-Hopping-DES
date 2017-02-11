class Event
{
	public:
		// CONSTRUCTOR
		Event( long long int newExecutionTime, int newTargetNum)
		{
			executionTime = newExecutionTime;
			targetNum     = newTargetNum;
			eventNum      = 0;
		}

		// ACCESSORS
		long long int getExecutionTime( ) const {return executionTime;}

		int getTargetNum( ) const { return targetNum; }

		int getEventNum( ) const { return eventNum; }
		// MUTATORS
		void setExecutionTime( long long int newExecutionTime )
			{ executionTime = newExecutionTime; }

		// VIRTUAL ACTION FUNCTION
		virtual void perform( ){return;}

	protected:
		// MEMBER VARIABLES
		long long int executionTime; // Time when event happens
		int           targetNum; // Number corresponding to target node
		int           eventNum; //USED TO DIFFERENTIATE FOR CASTING
};
