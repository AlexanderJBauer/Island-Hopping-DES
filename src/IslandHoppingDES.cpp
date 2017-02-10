
/**
* This is the actually simullation. The main function here uses all of
* the other class files.
*/

#include "Agent.h"       /* AttackerPerform, IDSPerform, SysAdminPerform */
#include "Environment.h" /* TIME_STEP, MAX_TIME, COMMAND_LINE_ERROE_MESSAGE */
#include <iostream> /* cout, endl */
#include <math.h>   /* log10 */
#include <stdlib.h> /* atoi, rand, srand */
#include <string.h> /* strlen */
#include <stdio.h>  /* NULL */
#include <time.h>   /* time */

using namespace Bauer;

int main( int argc, char* argv[] )
{

	srand(time(NULL));
	const char*         COMMAND_LINE_ERROR_MESSAGE =
			"This program takes in 3 command line arguments.\n"
			"The order of the arguments is as follows:\n\n"

			"numComputers:\nDescribes the number of computers\n"
			"connected to the simulated corporate network\n"
			"under attack. The computers are split into two\n"
			"subgroups controlled by switches under the IDS."
			"\n**Argument is an integer x such that x > 1.\n\n"

			"percentSuccess:\nDescribes the chance an attacker\n"
			"conducts a successful attack on a network node\n"
			"(Computer)\n**Argument is an integer x such that "
			"0 <= x <= 100.\n\n"

			"percentDetect:\nDescribes the chance that the\n"
			"IDS (Intrusion Detection System) detects an\n"
			"attack. The attack can only be detected across\n"
			"network switches when a compromised node attacks\n"
			"another node. If the attacker attacks a node,\n"
			"there is always a chance the attack gets\n"
			"detected.\n**Argument is an integer x shuch that "
			"0 <= x <= 100.\n\n";

///////////////////////////////////////////////////////////////////////////////
	int numComputers   = 0;
	int percentSuccess = 0;
	int percentDetect  = 0;

	if ( argc != 4 )
	{
		std::cout << COMMAND_LINE_ERROR_MESSAGE;
		return 0;
	}
	else
	{
		numComputers   = atoi(argv[1]);
		percentSuccess = atoi(argv[2]);
		percentDetect  = atoi(argv[3]);

		if (numComputers < 1 || percentSuccess < 0
				     || percentDetect  < 0
				     || percentSuccess > 100
				     || percentDetect  > 100 )
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}

		if ( percentSuccess == 0 && strlen( argv[2] ) != 1 )
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}
		else if (percentSuccess    != 0 &&
			 strlen( argv[2] ) != (int)(log10(percentSuccess) + 1 ))
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}

		if ( percentDetect == 0 && strlen( argv[3] ) != 1 )
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}
		else if (percentDetect     != 0 &&
			 strlen( argv[3] ) != (int)(log10(percentDetect) + 1 ))
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}

		if ( strlen( argv[1] ) != (int)(log10(numComputers) + 1 ))
		{
			std::cout << COMMAND_LINE_ERROR_MESSAGE;
			return 0;
		}
	}
		std::cout << numComputers   << endl
			  << percentSuccess << endl
			  << percentDetect  << endl;
///////////////////////////////////////////////////////////////////////////////

// Set up computer tree
// Set up IDS
// Set up attacker
// Set up Sysadmin
	long long int currentTime = 0;
	long long int lastFixTime = 0;

	while ( currentTime <= MAX_TIME )
	{
		if ( currentTime % 1000 == 0 )
			AttackerPerform( currentTime, percentSuccess,
					 percentDetect, numComputers,
					 eventQueue                  );
		//update infected computers
		while ( eventQueue.getRootArrivalTime( ) == currentTime )
		{
			eventQueue.deleteMin( );
		}

		//Check num infected computers

		currentTime = currentTime + TIME_STEP;
	}
	return 0;

}
