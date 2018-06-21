
#if !defined(_TEMPLATE_H)
#define _TEMPLATE_H

#include <vector>
#include <string>
#include <stdint.h>


namespace test
{
	// XXX
	template<typename ID>
	class GenericData;
	typedef GenericData<int64_t> Data;

	template<typename ID>
	class GenericContainer
	{
//		friend class Data;

	public:
		typedef std::vector<ID> IDList;

		GenericContainer();
//		GenericContainer(const IDList::allocator_type& al);
		virtual ~GenericContainer();
		ID GetId(int32_t index);
		Data* GetData(ID id);

	private:
		IDList m_idlist;

	};

	typedef GenericContainer<int64_t> Container;
}

#endif  //_TEMPLATE_H
