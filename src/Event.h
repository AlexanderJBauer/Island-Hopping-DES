#ifndef Bauer_Event_H
#define Bauer_Event_H


namespace Bauer
{

class Event
{
	public:
		// ACCESSORS
		int getExecutionTime( ) const { return executionTime; }

		int getTargetNum( ) const { return targetNum; }

		// VIRTUAL ACTION FUNCTION
		virtual void perform( );

	protected:
		// MEMBER VARIABLES
		long long int executionTime; // Time when event happens
		int           targetNum; // Number corresponding to target node
};

}
#endif
