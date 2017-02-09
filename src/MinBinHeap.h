#ifndef Bauer_MinBinHeap_H
#define Bauer_MinBinHeap_H

#include <vector>

namespace Bauer
{

template <typename Comparable>
class MinBinHeap
{
	public:
		// CONSTRUCTORS
		explicit MinBinHeap( int capacity = 100 );
		explicit MinBinHeap( const std::vector<Comparable> & initialArray );

		// ACCESSORS
		bool isEmpty() const;
		const Comparable & findMin() const;
		const Comparable & getPosition( int position ) const;

		// MUTATORS
		void insert( const Comparable & x );
		void insert( const Comparable & x );
		void deleteMin();
		void deleteMin( Comparable & minItem);
		void makeEmpty();
		void decreaseKey( int position, int delta );
		void increaseKey( int position, int delta );
		void remove( int position );

	private:
		// MEMBER VARIABLES
		int		   currentSize;
		vector<Comparable> array;

		// HELPER FUNCTIONS
		void buildHeap();
		void percolateDown( int hole );
};

}
#endif
