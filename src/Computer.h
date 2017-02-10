#ifndef Bauer_Computer_H
#define Bauer_Computer_H

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
