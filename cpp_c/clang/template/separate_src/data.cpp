
#include "template.h"
#include "data.h"

namespace test {
	template<typename ID>
	GenericData<ID>::GenericData(ID val)
	{
		m_value = val;
	}

	template<typename ID>
	GenericData<ID>::~GenericData() 
	{
	}

	template class GenericData<int64_t>;
//	template class GenericData<std::string>;



	template<typename ID>
	GenericSubData<ID>::GenericSubData(ID val)
	{
		// https://qiita.com/kaityo256/items/2f24662a9ab8341ad6f4
//		m_value = val; // XXX error. need this->
		this->m_value = val;
	}

	template<typename ID>
	GenericSubData<ID>::~GenericSubData() 
	{
	}
}
