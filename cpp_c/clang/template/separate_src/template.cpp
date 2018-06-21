
//#include <algorithm>
#include "template.h"

namespace test {
	template<typename ID>
	GenericContainer<ID>::GenericContainer()
	{
		ID x;
		m_idlist.push_back(x);
	}
/*
	template<typename ID>
	TContainer<ID>::TContainer(const IDList::allocator_type& al): m_rowid_idx(-1), m_idlist(al)
	{
	}
*/
	template<typename ID>
	GenericContainer<ID>::~GenericContainer() 
	{
	}



	template<typename ID>
	ID GenericContainer<ID>::GetId(int index) 
	{
		ID id = 0;
		id = (index < 0 || (int)(m_idlist.size()) < index)? 0:m_idlist[index];
		return id;
	}

	template<typename ID>
	Data* GenericContainer<ID>::GetData(ID id)
	{
		return nullptr;
	}


	template class GenericContainer<int64_t>;
//	template class GenericContainer<std::string>;
}
