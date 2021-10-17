#include "Random.h"

size_t Random::s_ObjectCount = 0;
std::unique_ptr<std::random_device> Random::s_SeedGenerator = std::make_unique<std::random_device>();

/*
* \param Min : (default = 0) : Minimum number generated (inclusive)
* \param Max : (default = 2^32-1) : Maximum number generated (exclusive)
*/
Random::Random(size_t min/*= 0*/, size_t max/*= (2^32-1)*/)
	: m_RandEngine(std::make_unique<std::mt19937>()), m_Seed(0), m_Min(min), m_Max(max)
{
	s_ObjectCount++;
	
	Impl_Init();
}

Random::~Random()
{
	s_ObjectCount--;
}

/*
* Seeds mt19937 engine using std::random_device
*/
const void Random::Seed()
{
	Impl_Seed((*s_SeedGenerator)());
}

/*
* Seeds using custom seed
* \param Seed : Custom seed chosen by user
*/
const void Random::Seed(uint32_t seed)
{
	Impl_Seed(seed);
}

/*
* Generates a new random number
*/
const uint32_t Random::Next() const
{
	return Impl_Next();
}

/*
* Sets the range of numbers generated
*
* \param Min : Minimum number generated (inclusive)
* \param Max : Maximum number generated (exlusive)
*/
const void Random::SetRange(uint32_t min, uint32_t max)
{
	Impl_SetRange(min, max);
}

/*
* Generates a new random number (Calls Random::Next())
*/
const uint32_t Random::operator()() const
{
	return Next();
}


//==========PRIVATE FUNCTION DEFINITIONS==========

void Random::Impl_Init()
{
	Impl_Seed((*s_SeedGenerator)());
}

inline const uint32_t Random::Impl_Next() const
{
	return Impl_Distribute((*m_RandEngine)());
}

inline const uint32_t Random::Impl_Distribute(uint32_t in) const
{
	return Impl_GenerateNumber(in, m_Min, m_Max);
}

inline const void Random::Impl_Seed(uint32_t seed)
{
	m_Seed = seed;
	m_RandEngine->seed(seed);
}

inline const uint32_t Random::Impl_GenerateNumber(size_t in, size_t min, size_t max) const
{
	return in % (max - min) + min; // Converts 'in' between 'min' and 'max'
}

inline const void Random::Impl_SetRange(uint32_t min, uint32_t max)
{
	m_Min = min;
	m_Max = max;
}
