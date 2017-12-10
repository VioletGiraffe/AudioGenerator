#pragma once


template <class T>
static T& singletonInstance()
{
	static char memory[sizeof(T)];
	static T *instance = nullptr;
	if (!instance)
		instance = new(memory) T();

	return *instance;
}

template <class T>
const T& singletonConstInstance()
{
	static char memory[sizeof(T)];
	static T *instance = nullptr;
	if (!instance)
		instance = new(memory) T();

	return *instance;
}