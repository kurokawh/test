#include <string>
#include <list>
#include <stdio.h>

// compile:
// % g++ -std=c++0x typedef.cpp

#if __cplusplus
namespace xxx {
	typedef char *String;
#else
namespace Xxx.Yyy.Updater
{
	using String = System.String;
	public class ExternalConstants
	{
#endif
		/// <summary>
		/// Key name of the np environment.
		/// </summary>
#if !__cplusplus
		public
#endif
			const String	UPDATER_ENVIRONMENTx = "np_environment";
			//const char* UPDATER_ENVIRONMENTx = "environment";

		/// <summary>
		/// Key name of the manifest revision for Music Unlimited.
		/// </summary>
#if !__cplusplus
		public
#endif
			const String	REVISION_MUx = "revision_mu";
};

void testlist(const std::list<std::string>& list)
{
		std::list<std::string>::const_iterator	it;

		for (it = list.begin(); it != list.end(); it++) {
			std::string key = *it;
			if (key.empty()) {
				printf("key is empty.\n");
				continue;
			}
			printf("key: %s\n", key.c_str());
		}


}
int main(int argc, char* argv[])
{
	int ret = 0;

	const std::initializer_list<std::string> list{
		{ xxx::UPDATER_ENVIRONMENTx },
		{ xxx::REVISION_MUx }
	};
	testlist(list);
	return 0;
}
