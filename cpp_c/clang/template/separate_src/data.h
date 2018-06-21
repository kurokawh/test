
#if !defined(_DATA_H)
#define _DATA_H

#include <vector>
#include <string>
#include <stdint.h>


namespace test
{
	template<typename ID>
	class GenericData
	{
		friend class GenericContainer<ID>;
		friend class GenericContainer<std::string>; // needed so that GenericContainer<string> access to Data (GenericData<int64_t>).

	public:
		GenericData(ID val);
		virtual ~GenericData();

	private:
		ID m_value;

	};

	typedef GenericData<int64_t> Data;
}

#endif  //_DATA_H
