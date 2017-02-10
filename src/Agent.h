#ifndef Bauer_Agent_H
#define Bauer_Agent_H

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

namespace Bauer
{

class Agent
{
	public:
		static void AttackerPerform( long long int   currentTime,
					     int             percentSuccess,
					     int             percentDetect,
					     int             numComputers
					     MinBinHeap *&   eventQueue   );

		static void SysAdminPerform( long long int   currentTime,
                			     long long int & lastFixTime,
                			     int             targetNum,
					     int             sourceNum,
                        		     MinBinHeap *&   eventQueue   );

		static void IDSPerform     ( long long int   currentTime,
			                     int             percentDetect,
                   			     int             targetNum,
                   			     int             sourceNum,
                   			     MinBinHeap *&   eventQueue   );

		static void ComputerPerform( long long int   currentTime,
			                     int             sourceNum,
                   			     int             percentSuccess,
                   			     int             numComputers,
                   			     MinBinHeap *&   eventQueue   );

};

}

#endif
