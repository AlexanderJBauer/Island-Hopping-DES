#ifndef Bauer_Computer_H
#define Bauer_Computer_H

#include "Agent.h"       /* AttackerPerform, IDSPerform, SysAdminPerform */
#include "Attack.h"
#include "Computer.h"
#include "Environment.h" /* TIME_STEP, MAX_TIME, COMMAND_LINE_ERROE_MESSAGE */
#include "Event.h"
#include "Fix.h"
#include "MinBinHeap.h"
#include "Notify.h"
#include <iostream> /* cout, endl */
#include <math.h>   /* log10 */
#include <stdlib.h> /* atoi, rand, srand */
#include <string.h> /* strlen */
#include <stdio.h>  /* NULL */
#include <time.h>   /* time */
#include <vector>

namespace Bauer {

class Computer
{
	public:
		Computer( int newComputerNum )
		{
			computerNum = newComputerNum;
			compromised = false;
			timeCompromised = -1;
		}

		bool isCompromised( ) const { return compromised; }

		long long int getTimeCompromised( ) const
					    { return timeCompromised; }

		void setCompromised( bool newVal ) { compromised = newVal; }

		void setTimeCompromised(long long int t) {timeCompromised = t;}

	private:
		int  computerNum;
		bool compromised;
		long long int timeCompromised;
};

}

#endif
