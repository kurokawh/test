
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
//		friend class Data; // XXX
//		friend class GenericData<int64_t>; // NG for string ID.
		friend class GenericData<ID>;

	public:
		typedef std::vector<ID> IDList;

		GenericContainer();
		// https://stackoverflow.com/questions/8246117/compiling-error-on-template-method-return-is-instance-from-inner-class
		GenericContainer(const typename IDList::allocator_type& al); // 'typname' keyword is needed.
		virtual ~GenericContainer();
		ID GetId(int32_t index);
		Data* GetData(ID id);

	private:
		IDList m_idlist;

	};

	typedef GenericContainer<int64_t> Container;
}

#endif  //_TEMPLATE_H
