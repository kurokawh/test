
#include "template.h"
#include "data.h"

namespace test {
	template<typename ID>
	GenericContainer<ID>::GenericContainer()
	{
		ID x;
		m_idlist.push_back(x);
	}
/*
	template<typename ID>
	GenericContainer<ID>::GenericContainer(const IDList::allocator_type& al)
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
		Data* d = new Data(1);
		d->m_value = 2;
		return d;
	}


	template class GenericContainer<int64_t>;
//	template class GenericContainer<std::string>;
}
