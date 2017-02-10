#ifndef Bauer_Event_H
#define Bauer_Event_H


namespace Bauer
{

class Event
{
	public:
		// ACCESSORS
		long long int getExecutionTime( ) const {return executionTime;}

		int getTargetNum( ) const { return targetNum; }

		// MUTATORS
		void setExecutionTime( long long int newExecutionTime )
			{ executionTime = newExecutionTime; }

		// VIRTUAL ACTION FUNCTION
		virtual void perform( );

	protected:
		// MEMBER VARIABLES
		long long int executionTime; // Time when event happens
		int           targetNum; // Number corresponding to target node
};

}
#endif
