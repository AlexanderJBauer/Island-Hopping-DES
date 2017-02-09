#ifndef Bauer_Notify_H
#define Bauer_Notify_H

#include "Attack.h"

namespace Bauer
{

class Notify : public Event
{

	public:
		// CONSTRUCTORS
		Notify( int initialTime, Bauer::Attack & initialAttackRef );

		// ACCESSORS
		const Bauer::Attack & getAttackRef( ) const;

		// MUTATORS
		void setAttackRef( Bauer::Attack & newAttackRef );

		// VIRTUAL FUNCTION OVERRIDE
		virtual void perform( );

	private:
		Bauer::Attack & attackRef;
};

}
#endif
