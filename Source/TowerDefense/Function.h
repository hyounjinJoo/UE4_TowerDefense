#pragma once

#include "global.h"

#define ENUM_TO_NAME(ENUM_TYPE) static FName EnumToName(ENUM_TYPE _type)\
	{\
		const UEnum* TYPE = FindObject<UEnum>(ANY_PACKAGE, TEXT(#ENUM_TYPE), true);\
		FName strType = TYPE->GetNameByValue((int64)_type);\
		return strType;\
	}


#define ENUM_TO_STRING(ENUM_TYPE) static FString EnumToString(ENUM_TYPE _type)\
	{\
		const UEnum* TYPE = FindObject<UEnum>(ANY_PACKAGE, TEXT(#ENUM_TYPE), true);\
		FString strType = TYPE->GetNameStringByValue((int64)_type);\
		return strType;\
	}

class Function
{
public:
	ENUM_TO_NAME(EEFFECT_TYPE)
	ENUM_TO_STRING(EEFFECT_TYPE)
	ENUM_TO_NAME(ETOWER_SKEL)
	ENUM_TO_STRING(ETOWER_SKEL)
	ENUM_TO_NAME(ETOWER_ABP)
	ENUM_TO_STRING(ETOWER_ABP)
};

