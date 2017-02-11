//This class holds the implementation for a Computer object
//It has three values. Its node number, whether or not it
// is compromised and the time at which it got compromised if
// compromised.

class Computer
{
	public:
		// CONSTRUCTORS
		Computer( int newComputerNum )
		{
			computerNum = newComputerNum;
			compromised = false;
			timeCompromised = -1;
		}

		//ACCESSORS
		bool isCompromised( ) const { return compromised; }

		long long int getTimeCompromised( ) const
					    { return timeCompromised; }

		//MUTATORS
		void setCompromised( bool newVal ) { compromised = newVal; }

		void setTimeCompromised(long long int t) {timeCompromised = t;}

	private:
		int  computerNum;
		bool compromised;
		long long int timeCompromised;
};
