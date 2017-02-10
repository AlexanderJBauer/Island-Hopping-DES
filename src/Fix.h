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
		virtual void perform( );


};

}
#endif
