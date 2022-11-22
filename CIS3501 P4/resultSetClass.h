//Program Name: resultSetClass.h
//Programmer Name: Anthony Vettraino
//Description: resultSetClass class header for declaration and implementation
//Date Created: 8/3/2021

#pragma once

class resultSetClass
{
public:
	int parent;
	int weight;
	resultSetClass();
};

//Description: constructor
//Pre-condition: resultSetClass object has been created
//Post-condition: assings -1 to parent and weight
resultSetClass::resultSetClass()
{
	parent = -1;
	weight = -1;
}