#ifndef Bauer_Fix_H
#define Bauer_Fix_H

#include "Computer.h"

namespace Bauer
{

class Fix : public Event
{

	public:
		// CONSTRUCTORS
		Fix( int initialTime, Bauer::Computer & initialTarget );

		// ACCESSORS
		const Bauer::Computer & getTarget( ) const;

		// MUTATORS
		void setTarget( Bauer::Computer & newTarget );

		// VIRTUAL FUNCTION OVERRIDE
		virtual void perform( );

	private:
		Bauer::Computer & target;
};

}
#endif
