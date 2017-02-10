#ifndef Bauer_Agent_H
#define Bauer_Agent_H


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
