#ifndef Bauer_Event_H
#define Bauer_Event_H


namespace Bauer
{

class Event
{
	public:
		// CONSTRUCTORS
		explicit Event( int initialTime );

		// ACCESSORS
		int getTime( ) const;

		// MUTATORS
		void decreaseTime( int decrement );
		void increaseTime( int increment );

		// VIRTUAL ACTION FUNCTION
		virtual void perform( );

	protected:
		// MEMBER VARIABLES
		int time; // Time until event happens/ changes environment state

};

}
#endif
