// Map.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "Map.h"

// Used specifically in this cpp file only

#include <memory>

class CClass
{
private:
	float mFloat;
	char mChar;
public:
	CClass() 
	{

	}

	CClass(float f, char c)
	{
		mFloat = f;
		mChar  = c;
	}

	const float GetFloat() const
	{
		return mFloat;
	}

	const char GetChar() const
	{
		return mChar;
	}

	// Allow two classes of the same type to compare their variables together
	bool operator==(const CClass &anotherObject)
	{
		return mFloat == anotherObject.GetFloat() || mChar == anotherObject.GetChar();
	}

	~CClass()
	{

	}
};

class CClass2
{
private:
	int mInt;
	std::string mString;
public:
	CClass2()
	{

	}

	CClass2(int i, std::string s)
	{
		mInt    = i;
		mString = s;
	}

	// Allow two classes of the same type to compare their variables together
	bool operator==(const CClass2 &anotherObject)
	{
		return mInt == anotherObject.GetInt() || mString == anotherObject.GetString();
	}

	const int GetInt() const
	{
		return mInt;
	}

	const std::string GetString() const
	{
		return mString;
	}

	~CClass2()
	{

	}
};

class SStruct
{
private:
	int mInt;
	std::string mString;
public:
	SStruct() 
	{

	}

	SStruct(int i, std::string s)
	{
		mInt    = i;
		mString = s;
	}

	bool operator==(const SStruct &anotherObject)
	{
		return mInt == anotherObject.GetInt() && mString == anotherObject.GetString();
	}

	const int GetInt() const
	{
		return mInt;
	}

	const std::string GetString() const
	{
		return mString;
	}

	~SStruct()
	{

	}
};

void PerformTests()
{
	// Declaration of classes, structures and maps

	// Classes declarations
	CClass  a = CClass(5.5f, 'a');
	CClass  b = CClass(10.5f, 'b');
	CClass2 c = CClass2(75, "C Class of 2");
	CClass2 d = CClass2(100, "D Class of 2");

	std::unique_ptr<CMap<int, CClass>>      intClassMap     = std::make_unique<CMap<int, CClass>>();
	std::unique_ptr<CMap<CClass, CClass>>   classClassMap   = std::make_unique<CMap<CClass, CClass>>();
	std::unique_ptr<CMap<CClass, CClass>>   classClassMap2  = std::make_unique<CMap<CClass, CClass>>();
	std::unique_ptr<CMap<CClass2, CClass2>> class2Class2Map = std::make_unique<CMap<CClass2, CClass2>>();

	// Struct declarations
	SStruct s1 = SStruct(15, "S1 Struct");
	SStruct s2 = SStruct(20, "S2 Struct");

	std::unique_ptr<CMap<SStruct, SStruct>> structStructMap = std::make_unique<CMap<SStruct, SStruct>>();

	// Simple data type declarations
	std::unique_ptr<CMap<int, float>>       intFloatMap   = std::make_unique<CMap<int, float>>();
	std::unique_ptr<CMap<int, std::string>> intStringMap  = std::make_unique<CMap<int, std::string>>();
	std::unique_ptr<CMap<char, int>>        charIntMap    = std::make_unique<CMap<char, int>>();
	std::unique_ptr<CMap<bool, double>>     boolDoubleMap = std::make_unique<CMap<bool, double>>();

	// Int Class Testing
	intClassMap->AddSet(10, a);

	std::cout << "Int Class Size: " << intClassMap->GetCurrentSize() << "\n";

	for (CIterator<int, CClass> it = intClassMap->Start(); it != intClassMap->End(); it++)
	{
		std::cout << "<INT, CLASS>: Key: " << (*it).key << " Float: " << (*it).value.GetFloat() << " Char:  " << (*it).value.GetChar() << "\n";
	}

	// Class Class Testing
	classClassMap->AddSet(a, b);
	classClassMap->AddSet(b, a);

	std::cout << "ClassClassMap Size: " << classClassMap->GetCurrentSize() << "\n";

	for (CIterator<CClass, CClass> it = classClassMap->Start(); it != classClassMap->End(); it++)
	{
		std::cout << "<CLASS, CLASS>: Float: " << (*it).value.GetFloat() << " Char:  " << (*it).value.GetChar() << "\n";
	}

	// Class2 Class2 Testing
	class2Class2Map->AddSet(c, d);
	class2Class2Map->AddSet(d, c);

	std::cout << "Class2Class2Map Size: " << class2Class2Map->GetCurrentSize() << "\n";

	for (CIterator<CClass2, CClass2> it = class2Class2Map->Start(); it != class2Class2Map->End(); it++)
	{
		std::cout << "<CLASS2, CLASS2>: Int: " << (*it).value.GetInt() << " String:  " << (*it).value.GetString() << "\n";
	}

	// Testing usage of == operator
	std::cout << "Testing usage of == operator\n";
	for (CIterator<CClass, CClass> it = classClassMap->Start(); it != classClassMap->End(); it++)
	{	// Usage of the == operator
		if (it == classClassMap->Start())
		{
			std::cout << "We are pointing at the first map entry\n";
		}
		std::cout << "MATCH! <CLASS, CLASS>: Float: " << (*it).value.GetFloat() << " Char:  " << (*it).value.GetChar() << "\n";	
	}

	// Testing setting one map with another
	std::cout << "Testing setting one <CLASS, CLASS> map to another\n";
	classClassMap2 = std::move(classClassMap);
	// Struct testing
	structStructMap->AddSet(s1, s2);
	structStructMap->AddSet(s2, s1);

	std::cout << "STRUCT Struct Size: " << structStructMap->GetCurrentSize() << "\n";

	for (CIterator<SStruct, SStruct> it = structStructMap->Start(); it != structStructMap->End(); it++)
	{
		std::cout << "<STRUCT, STRUCT>: String: " << (*it).value.GetString() << " Int:  " << (*it).value.GetInt() << "\n";
	}

	// Testing emptying an int struct map
	structStructMap->Reset();

	std::cout << "Reset the int struct map. New Size: " << structStructMap->GetCurrentSize() << "\n";
	std::cout << std::boolalpha << "Is the map we just reset empty? " << structStructMap->IsEmpty() << "\n";

	// Testing adding int float
	intFloatMap->AddSet(0, 0.5f);
	intFloatMap->AddSet(1, 1.5f);
	intFloatMap->AddSet(2, 2.5f);
	intFloatMap->AddSet(3, 3.5f);

	std::cout << "Int Float Map Size: " << intFloatMap->GetCurrentSize() << "\n";

	// Tests the != operator. This is done generally on any iteration of any map in this testing program
	for (CIterator<int, float> it = intFloatMap->Start(); it != intFloatMap->End(); it++)
	{
		std::cout << "<INT, FLOAT>: Key: " << (*it).key << " Value:  " << (*it).value << "\n";
	}

	// Tests KeyExists() 	
	std::cout << std::boolalpha << "Key 2 exists in intFloatMap? :   " << intFloatMap->KeyExists(2) << "\n";
	std::cout << std::boolalpha << "Key 100 exists in intFloatMap? : " << intFloatMap->KeyExists(100) << "\n";

	// Tests swapping two values from a map
	std::cout << "Attempting to swap key 0 and key 1 values.\n";
	intFloatMap->Swap(0, 1);

	for (CIterator<int, float> it = intFloatMap->Start(); it != intFloatMap->End(); it++)
	{
		std::cout << "<INT, FLOAT>: Key: " << (*it).key << " Value:  " << (*it).value << "\n";
	}

	// Tests swapping two values from a map that does not exist
	std::cout << "Attempting to swap key 50 and 60. Two keys that do not exist.\n";
	intFloatMap->Swap(50, 60);

	for (CIterator<int, float> it = intFloatMap->Start(); it != intFloatMap->End(); it++)
	{
		std::cout << "<INT, FLOAT>: Key: " << (*it).key << " Value:  " << (*it).value << "\n";
	}

	// Tests swapping the two values that were swapped back to what they were in the first place
	std::cout << "Attempting to swap key 1 and 0. Back to the original order.\n";
	intFloatMap->Swap(1, 0);

	for (CIterator<int, float> it = intFloatMap->Start(); it != intFloatMap->End(); it++)
	{
		std::cout << "<INT, FLOAT>: Key: " << (*it).key << " Value:  " << (*it).value << "\n";
	}

	// Tests removing a set from a map 
	std::cout << "Attempting to remove set with Key 1.\n";
	intFloatMap->Remove(1);

	for (CIterator<int, float> it = intFloatMap->Start(); it != intFloatMap->End(); it++)
	{
		std::cout << "<INT, FLOAT>: Key: " << (*it).key << " Value:  " << (*it).value << "\n";
	}
	// Tests removing a set from a map that does not exist
	std::cout << "Attempting to remove Key 10 set. (A key that does not exist)\n";
	intFloatMap->Remove(10);

	for (CIterator<int, float> it = intFloatMap->Start(); it != intFloatMap->End(); it++)
	{
		std::cout << "<INT, FLOAT>: Key: " << (*it).key << " Value: " << (*it).value << " \n";
	}

	std::cout << "Int Float Map Size: " << intFloatMap->GetCurrentSize() << "\n";
	// Testing adding int string
	intStringMap->AddSet(0, "adam");
	intStringMap->AddSet(1, "john");
	intStringMap->AddSet(2, "ben");
	intStringMap->AddSet(3, "Josh");

	for (CIterator<int, std::string> it = intStringMap->Start(); it != intStringMap->End(); it++)
	{
		std::cout << "<INT, STRING>: Key: " << (*it).key << " Value:  " << (*it).value << "\n";
	}

	std::cout << "Int String Map Size: " << intStringMap->GetCurrentSize() << "\n";

	// Testing adding duplicate value
	std::cout << "Attempting to add a duplicate key into the intString Map\n"; 
	intStringMap->AddSet(1, "adam");
	std::cout << "Int String Map Size: " << intStringMap->GetCurrentSize() << "\n";

	std::string* intStringLocator = intStringMap->Locate(10);

	if (intStringLocator != nullptr)
	{	
		std::cout << "Located Key 10 in int string: " << intStringLocator << "\n";
	}
	else
	{
		std::cout << "Key 10 does not exist.\n";
	}

	// Testing adding int char
	charIntMap->AddSet('r', 0);
	charIntMap->AddSet('u', 1);
	charIntMap->AddSet('s', 2);
	charIntMap->AddSet('h', 3);
	std::cout << "Int Char Map Size: " << charIntMap->GetCurrentSize() << "\n";

	for (CIterator<char, int> it = charIntMap->Start(); it != charIntMap->End(); it++)
	{
		std::cout << "<CHAR, INT>: Key: " << (*it).key << " Value:  " << (*it).value << "\n";
	}

	boolDoubleMap->AddSet(true, 10.5);
	boolDoubleMap->AddSet(false, 5.5);

	std::cout << "Bool Double Map Size: " << boolDoubleMap->GetCurrentSize() << "\n";

	for (CIterator<bool, double> it = boolDoubleMap->Start(); it != boolDoubleMap->End(); it++)
	{
		std::cout << std::boolalpha << "<BOOL, DOUBLE>: Key: " << (*it).key << " Value:  " << (*it).value << "\n";
	}

	// Testing GetMaxSize()
	std::cout << "Maximum size of intFloatMap: " << intFloatMap->GetMaxSize() << "\n";
	std::cout << "Adding more than the limit to the intFloapMap array\n";
	
	for (int i = 0; i < 5000; i++)
	{
		intFloatMap->AddSet(i, i * 5.0f);
	}

	std::cout << "Current Size of intFloatMap:      " << intFloatMap->GetCurrentSize() << "\n";
	std::cout << "New Maximum Size of intFloatMap:  " << intFloatMap->GetMaxSize()     << "\n";
	std::cout << "Index of key 1000 in intFloatMap: " << intFloatMap->GetIndex(1000)   << "\n";
}

int main()
{
	PerformTests();

	_CrtDumpMemoryLeaks();

	system("pause");
}
