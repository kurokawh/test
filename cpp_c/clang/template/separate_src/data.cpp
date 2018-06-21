
#include "data.h"

namespace test {
	template<typename ID>
	GenericData<ID>::GenericData(ID val)
	{
//		m_data = val;
	}

	template<typename ID>
	GenericData<ID>::~GenericData() 
	{
	}

	template class GenericData<int64_t>;
//	template class GenericData<std::string>;
}
