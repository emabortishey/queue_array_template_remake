#pragma once
#include <iostream>
#include <exception>

using namespace std;

class ContaineerIsEmpty : public exception
{
	string msg;
public:
	ContaineerIsEmpty(const string msg_P) : msg{msg_P} { }

	const virtual char* what() const override { return msg.c_str(); }
};