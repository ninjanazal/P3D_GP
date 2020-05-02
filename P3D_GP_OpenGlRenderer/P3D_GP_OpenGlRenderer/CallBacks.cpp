#pragma once
#include "CallBacksDeff.h"

// utiliza�ao do namespace
namespace P3D
{
	// callback para erros do
	void DisplayErrorCallback(int error, const char* desc)
	{
		// imprime o erro passado
		std::cout << "Error: " << error<< " -> "  << desc << std::endl;
	}
}