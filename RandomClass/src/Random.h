#pragma once

/*------------------------------------------

 Generates random numbers using mt19937 engine.


 Calling Random::Next() or Random::operator() generates a random number between
 'min'(inclusive) and 'max'(exclusive).


------------------------------------------*/

#include <random>
#include <memory>

// (2^32-1)
#define MAX_U32_BIT_INTEGER_LIMIT (uint32_t)-1


class Random
{
public: // Public Constructor/Destructors
	Random(size_t min = 0, size_t max = MAX_U32_BIT_INTEGER_LIMIT);
	~Random();

public: // Getters
	static inline const size_t GetObjectCount() { return s_ObjectCount; }
	inline const uint32_t GetSeed() const { return m_Seed; }
	inline const uint32_t GetMin() const { return m_Min; }
	inline const uint32_t GetMax() const { return m_Max; }

public: // Non-static public functions
	inline const void Seed();
	inline const void Seed(uint32_t seed);
	inline const uint32_t Next() const;
	
public: // Setters
	const void SetRange(uint32_t min, uint32_t max);

public: // Operator Overloads
	const uint32_t operator()() const;


private: // Non-static variables
	std::unique_ptr<std::mt19937> m_RandEngine;
	uint32_t m_Seed;
	uint32_t m_Min;
	uint32_t m_Max;

private: // Static variables
	static std::unique_ptr<std::random_device> s_SeedGenerator;
	static size_t s_ObjectCount;


private: // Non-static private methods
	void Impl_Init();
	inline const uint32_t Impl_Next() const;
	inline const uint32_t Impl_Distribute(uint32_t _In) const;
	inline const void Impl_Seed(uint32_t seed);
	inline const uint32_t Impl_GenerateNumber(size_t in, size_t max, size_t min) const;
};

