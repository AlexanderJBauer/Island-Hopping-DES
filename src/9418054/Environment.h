// This class was originally made to make Super.cpp
// look nicer by holding a very large string, but its
// illegal to do what I was trying. Ended up keeping some
// constants in this class.

class Environment
{
	public:
		static const int           TIME_STEP = 100;
		static const long long int MAX_TIME  = 8640000000;
		static const int           LATENCY   = 100;
};
