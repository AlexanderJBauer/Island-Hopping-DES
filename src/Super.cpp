#include <iostream> /* cout, endl */
#include <math.h>   /* log10 */
#include <stdlib.h> /* atoi, rand, srand */
#include <string.h> /* strlen */
#include <stdio.h>  /* NULL */
#include <time.h>   /* time */
#include <vector>

class Environment
{
	public:
		static const int           TIME_STEP = 100;
		static const long long int MAX_TIME  = 8640000000;
		static const int           LATENCY   = 100;
};

class Event
{
	public:
		// CONSTRUCTOR
		Event( long long int newExecutionTime, int newTargetNum)
		{
			executionTime = newExecutionTime;
			targetNum     = newTargetNum;
			eventNum      = 0;
		}

		// ACCESSORS
		long long int getExecutionTime( ) const {return executionTime;}

		int getTargetNum( ) const { return targetNum; }

		int getEventNum( ) const { return eventNum; }
		// MUTATORS
		void setExecutionTime( long long int newExecutionTime )
			{ executionTime = newExecutionTime; }

		// VIRTUAL ACTION FUNCTION
		virtual void perform( ){return;}

	protected:
		// MEMBER VARIABLES
		long long int executionTime; // Time when event happens
		int           targetNum; // Number corresponding to target node
		int           eventNum; //USED TO DIFFERENTIATE FOR CASTING
};

class MinBinHeap
{
	public:
		// CONSTRUCTORS
		explicit MinBinHeap( int newCapacity = 100 )
		{
			currentSize = 0;
			capacity    = newCapacity;
			eventArray  = new Event*[newCapacity];
			Event* falseEvent = new Event(-1, 0);
			eventArray[0] = falseEvent;
		}

		// ACCESSORS
		bool  isEmpty() const
		{
			if( currentSize == 0)
				return true;
			else
				return false;
		}

		const Event* findMin() const
		{
			if ( currentSize != 0 )
				return eventArray[1];
			else
				return eventArray[0];
		}

		const Event* getPosition( int position ) const
			{ return eventArray[position]; }

		int getCurrentSize() const { return currentSize; }

		// MUTATORS
		void insert( Event* newEvent )
		{
			if ( currentSize == capacity -1 )
				resizeArray(capacity * 2);

			if ( currentSize == 0 )
			{
				eventArray[1] =  newEvent;
				currentSize = 1;
			}

			// Percolate up
			int hole = currentSize + 1;
			while ( newEvent->getExecutionTime()
				< eventArray[hole / 2]->getExecutionTime() )
			{
				eventArray[hole] = eventArray[hole / 2];
				hole = hole / 2;
			}
			eventArray[hole] = newEvent;

			// Update size
			currentSize = currentSize + 1;
		}

		Event* deleteMin( )
		{
			Event* min = eventArray[1];
			eventArray[1] = eventArray[currentSize];
			currentSize = currentSize - 1;
			percolateDown( 1 );
			return min;
		}

		void decreaseKey( int position, int delta )
		{
			long long int newExecTime =
				eventArray[position]->getExecutionTime()-delta;

			eventArray[position]->setExecutionTime( newExecTime );
			Event* tmp = eventArray[position];
			// Percolate up
			int hole = position;
			while ( tmp->getExecutionTime()
				< eventArray[hole/2]->getExecutionTime() )
			{
				eventArray[hole] = eventArray[hole /2];
				hole = hole / 2;
			}
			eventArray[hole] = tmp;
		}

		void increaseKey( int position, int delta )
		{
			long long int newExecTime =
				eventArray[position]->getExecutionTime()+delta;

			eventArray[position]->setExecutionTime( newExecTime );
			percolateDown( position );
		}


	private:
		// MEMBER VARIABLES
		int     currentSize;
		int     capacity;
		Event** eventArray;

		// HELPER FUNCTIONS
		void resizeArray(int newCapacity)
		{
			Event** newEventArray = new Event*[newCapacity];
			for( int i = 0; i < currentSize; i++ )
				newEventArray[i] = eventArray[i];

			delete [] eventArray;
			eventArray = newEventArray;
			capacity   = newCapacity;
		}

		void percolateDown( int hole )
		{
			int child;
			Event* tmp = eventArray[hole];
			for( ; hole * 2 <= currentSize; hole = child )
			{
				child = hole * 2;
				if( child != currentSize &&
				    eventArray[child+1]->getExecutionTime()
				    < eventArray[child]->getExecutionTime() )
					++child;
				if( eventArray[child]->getExecutionTime()
				    < tmp->getExecutionTime() )
					eventArray[hole] = eventArray[child];
				else
					break;
			}
			eventArray[hole] = tmp;
		}
};

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

class Fix : public Event
{

	public:
		// CONSTRUCTORS
		Fix( long long int newExecutionTime, int newTargetNum )
		: Event( newExecutionTime, newTargetNum )
		{  eventNum = 3; }

		// VIRTUAL FUNCTION OVERRIDE
		virtual void perform( long long int            currentTime,
				      long long int &          lastFixTime,
				      int                      percentSuccess,
				      int                      percentDetect,
				      int		       numComputers,
				      std::vector<Computer*> & computerList,
				      MinBinHeap *&            eventQueue   )
		{
			computerList[targetNum]->setCompromised(false);
			computerList[targetNum]->setTimeCompromised(-1);
                        std::cout << "FIX: " << executionTime << ", "
                                  << targetNum << "\n";

		}


};

class Notify : public Event
{

	public:
		// CONSTRUCTORS
		Notify( long long int newExecutionTime,
			int           newTargetNum,
			int           newSourceNum      )
		: Event( newExecutionTime, newTargetNum )
		{
			sourceNum     = newSourceNum;
			eventNum      = 2;
		}

		// ACCESSORS
		int getSourceNum( ) const { return sourceNum; }

		static void SysAdminPerform( long long int   currentTime,
			     		     long long int & lastFixTime,
			     		     int             targetNum,
			     		     int             sourceNum,
			     		     MinBinHeap *&   eventQueue   );

		// VIRTUAL FUNCTION OVERRIDE
		virtual void perform( long long int            currentTime,
				      long long int &          lastFixTime,
				      int                      percentSuccess,
				      int                      percentDetect,
				      int                      numComputers,
				      std::vector<Computer*> & computerList,
				      MinBinHeap *&            eventQueue  )
		{
			SysAdminPerform( currentTime, lastFixTime, targetNum,
						      sourceNum,   eventQueue);
                        std::cout << "NOTIFY: " << executionTime << ", "
                                  << sourceNum << ", " << targetNum << "\n";
		}

	private:
		int sourceNum;
};

class Attack : public Event
{
	private:
		int sourceNum;

	public:
		// CONSTRUCTORS
		Attack( long long int newExecutionTime,
			int           newTargetNum,
			int           newSourceNum     )
		: Event(newExecutionTime, newTargetNum)
		{
			sourceNum     = newSourceNum;
			eventNum      = 1;
		}

		// ACCESSORS
		int getSourceNum( ) const { return sourceNum; }

		static void IDSPerform( long long int currentTime,
				        int           percentDetect,
				        int           targetNum,
				        int           sourceNum,
				        MinBinHeap *& eventQueue    )
		{
			if ( (rand()%100 + 1) <= percentDetect )
			{
				Event* newNote =
		        	  new Notify(currentTime + Environment::LATENCY,
				             targetNum, sourceNum );
				eventQueue->insert( newNote );
			}


		}

		// VIRTUAL FUNCTION OVERRIDE
		virtual void perform( long long int            currentTime,
				      long long int &          lastFixTime,
				      int                      percentSuccess,
				      int                      percentDetect,
				      int                      numComputers,
				      std::vector<Computer*> & computerList,
				      MinBinHeap *&            eventQueue  )
		{
			if ( !computerList[targetNum]->isCompromised() )
			{
				computerList[targetNum]->setCompromised(true);
				computerList[targetNum]->
					setTimeCompromised(currentTime);
			}

			IDSPerform( currentTime, percentDetect, targetNum,
						 sourceNum,     eventQueue );

			std::cout << "ATTACK: " << executionTime << ", "
				  << sourceNum << ", " << targetNum << "\n";
		}

};



static void AttackerPerform( long long int currentTime,
			     int           percentSuccess,
			     int           percentDetect,
			     int           numComputers,
			     MinBinHeap *& eventQueue    )
{

	if ( (rand()%100 + 1) <= percentSuccess )
	{
		int targetNum = rand()%numComputers + 1;

		Event* newAttack = new Attack
			( currentTime + Environment::LATENCY, targetNum, -1 );

		eventQueue->insert( newAttack );
	}

}

void Notify::SysAdminPerform( long long int   currentTime,
			      long long int & lastFixTime,
			      int             targetNum,
			      int             sourceNum,
			      MinBinHeap *&   eventQueue   )
{
	if ( lastFixTime > currentTime )
	{
		Event* newFix = new Fix( lastFixTime + 10000, targetNum );

		eventQueue->insert( newFix );

		if ( sourceNum != -1 )
		{
			Event* newFix2= new Fix(lastFixTime + 10000, sourceNum);
			eventQueue->insert( newFix2 );
		}

		lastFixTime = lastFixTime + 10000;
	}
	else
	{
		Event* newFix = new Fix( currentTime + 10000, targetNum );
		eventQueue->insert( newFix );

		if ( sourceNum != -1 )
		{
			Event* newFix2= new Fix(currentTime + 10000, sourceNum);
			eventQueue->insert( newFix2 );
		}

		lastFixTime = currentTime + 10000;
	}
}


static void ComputerPerform( long long int   currentTime,
                             int             sourceNum,
                             int             percentSuccess,
                             int             numComputers,
                             MinBinHeap *&   eventQueue   )
{
	if ( (rand()%100 + 1) <= percentSuccess )
	{
		int targetNum = sourceNum;
		while (targetNum == sourceNum)
			targetNum = rand()%numComputers + 1;

		Event* newAttack = new Attack
			( currentTime + Environment::LATENCY, targetNum,
							      sourceNum );

		eventQueue->insert( newAttack );
	}

}

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
		std::cout << numComputers   << std::endl
			  << percentSuccess << std::endl
			  << percentDetect  << std::endl;
///////////////////////////////////////////////////////////////////////////////

	std::vector<Computer*> computerList;
	for( int i = 0; i <= numComputers; i++ )
		computerList.push_back(new Computer(i));

	MinBinHeap* eventQueue = new MinBinHeap(300);

	long long int currentTime    = 1000;
	long long int lastFixTime    = 0;
	long long int nextExec       = 0;
	int           numCompromised = 0;
	int           numPopped      = 0;
	Event*        lastDelete;

	while ( currentTime <= Environment::MAX_TIME )
	{
		numCompromised = 0;

		if ( currentTime % 1000 == 0 )
			AttackerPerform( currentTime, percentSuccess,
					 percentDetect, numComputers,
					 eventQueue                  );

		for( int i = 0; i <= numComputers; i++ )
		{
			if ( computerList[i]->isCompromised() )
			{
				if ( ((currentTime
                                      -computerList[i]->getTimeCompromised())
				      %1000) == 0 )
				{
					ComputerPerform( currentTime,
							 i,
							 percentSuccess,
							 numComputers,
							 eventQueue  );
				}
				numCompromised++;
			}
		}

		if ( numCompromised >= numComputers/2)
		{
			std::cout << "Attacker wins\n";
			return 0;
		}

		if ( numPopped > 0 && numCompromised == 0 )
		{
			std::cout << "System Administrator wins\n";
			return 0;
		}

		if ( eventQueue->getCurrentSize() != 0 )
		{

			nextExec = eventQueue->findMin()->getExecutionTime();
			while ( nextExec == currentTime
				&& eventQueue->getCurrentSize() != 0 )
			{
				lastDelete = eventQueue->deleteMin( );

				if (lastDelete->getEventNum() == 1)
				{
				dynamic_cast<Attack*>(lastDelete)->
						perform(currentTime,
						    lastFixTime,
						    percentSuccess,
						    percentDetect, numComputers,
						    computerList, eventQueue);
				}

				if (lastDelete->getEventNum() == 2)
				{
				dynamic_cast<Notify*>(lastDelete)->
						perform(currentTime,
						    lastFixTime,
						    percentSuccess,
						    percentDetect, numComputers,
						    computerList, eventQueue);
				}

				if (lastDelete->getEventNum() == 3)
				{
				dynamic_cast<Fix*>(lastDelete)->
						perform(currentTime,
						    lastFixTime,
						    percentSuccess,
						    percentDetect, numComputers,
						    computerList, eventQueue);
				}

				nextExec =
				     eventQueue->findMin()->getExecutionTime();

				numPopped ++;
			}
		}

		currentTime = currentTime + Environment::TIME_STEP;
	}
	std::cout << "Its a draw\n";
	return 0;

}
