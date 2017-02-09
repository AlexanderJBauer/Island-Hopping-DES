#ifndef Bauer_Attack_H
#define Bauer_Attack_H

#include "Agent.h"

namespace Bauer
{

class Attack : public Event
{

	public:
		// CONSTRUCTORS
		Attack( int initialTime, Bauer::Agent    & initialSource,
					 Bauer::Computer & initialTarget );

		// ACCESSORS
		const Bauer::Agent    & getSource( ) const;
		const Bauer::Computer & getTarget( ) const;

		// MUTATORS
		void setSource( Bauer::Agent & newSource );
		void setTarget( Bauer::Computer & newTarget );

		// VIRTUAL FUNCTION OVERRIDE
		virtual void perform( );

	private:
		Bauer::Agent    & source;
		Bauer::Computer & target;
};

}
#endif
