// map::find
#include <iostream>
#include <new>
#include <map>
#include <memory>

//#include "def.h"
#define	ID_PREVIEW "PREVIEW"
#define	ID_STORE "STORE"
#define	ID_DATA "DATA"
#define	ID_SETTINGS "SETTINGS"
#define	ID_NEW "NEW"     
#define	ID_BROWSER "BROWSER"   
#define	ID_LIBRARY "LIBRARY"


	#define POSITION_LEFT_PREVIEW	5
	#define POSITION_LEFT_STORE			6
	#define POSITION_LEFT_DATA	8
	#define POSITION_LEFT_SETTINGS	9
	#define POSITION_LEFT_NEW		10
	#define POSITION_MIDDLE	100
	#define POSITION_RIGHT_BROWSER		999
	#define POSITION_RIGHT_LIBRARY			1000



typedef std::map<int, int> ContentInfo;
typedef std::shared_ptr<ContentInfo>		ContentInfoPtr;
typedef std::map<std::string, int> PositionTable;

static const PositionTable POSITION_TABLE = {
	// left
	{ID_PREVIEW, POSITION_LEFT_PREVIEW},
	{ID_STORE, POSITION_LEFT_STORE},
	{ID_DATA, POSITION_LEFT_DATA},
	{ID_SETTINGS, POSITION_LEFT_SETTINGS},
	{ID_NEW, POSITION_LEFT_NEW},
	// right
	{ID_BROWSER, POSITION_RIGHT_BROWSER}, // Capture Gallery
	{ID_LIBRARY, POSITION_RIGHT_LIBRARY},
};
void setPosition( const std::string& title_id, ContentInfoPtr& app_info )
{
	
	int32_t position = POSITION_MIDDLE; // default value. this value is used if title-id is not listed in table.
	PositionTable::const_iterator it = POSITION_TABLE.find(title_id);
	if (it != POSITION_TABLE.end()) {
		// found. use value in table
		position = it->second;
	}
	app_info->insert(ContentInfo::value_type(/*KEY_POSITION*/0, position));
	std::cout << "id: " << title_id << ", position: " << position << '\n';
}


int main ()
{
	ContentInfoPtr p(new ContentInfo());

	setPosition(ID_PREVIEW, p);
	setPosition(ID_STORE, p);      
	setPosition(ID_DATA, p); 
	setPosition(ID_SETTINGS, p);
	setPosition(ID_NEW, p);     
	setPosition(ID_BROWSER, p);   
	setPosition(ID_LIBRARY, p);       


	return 0;
}
