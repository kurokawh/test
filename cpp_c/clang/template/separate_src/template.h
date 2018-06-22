
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

//	template<typename ID>
//	typedef std::vector<GenericContainer<ID>> GenericContainerList;
//	=> error: a typedef cannot be a template
//	https://cpprefjp.github.io/lang/cpp11/alias_templates.html
//	http://www.yasutomo57jp.com/2014/06/12/typedef%E3%82%92%E3%83%86%E3%83%B3%E3%83%97%E3%83%AC%E3%83%BC%E3%83%88%E5%8C%96%E3%81%97%E3%81%9F%E3%81%84%EF%BC%88%E3%82%A8%E3%82%A4%E3%83%AA%E3%82%A2%E3%82%B9%E3%83%86%E3%83%B3%E3%83%97%E3%83%AC/
	template<typename ID>
	using GenericContainerList = std::vector<GenericContainer<ID>>;
	typedef GenericContainerList<int64_t> Int64ContainerList;

}

#endif  //_TEMPLATE_H
