#ifndef Bauer_MinBinHeap_H
#define Bauer_MinBinHeap_H


namespace Bauer
{

class MinBinHeap
{
	public:
		// CONSTRUCTORS
		explicit MinBinHeap( int newCapacity = 100 )
		{
			currentSize = 0;
			capacity    = newCapacity;
			eventArray  = new Event*[newCapacity];
			Event* falseEvent = new Attack(-1, 0, 0);
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
		void insert( const Event* newEvent )
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
		void resizeArray(newCapacity)
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
					eventArray[hole] = enevtArray[child];
				else
					break;
			}
			eventArray[hole] = tmp;
		}
};

}
#endif
