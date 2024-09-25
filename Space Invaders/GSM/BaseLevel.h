#pragma once
#include <iostream>

namespace GSM
{
	class BaseLevel
	{
	public:
		virtual ~BaseLevel() {
			std::cout << __FUNCTION__ << std::endl;
		};
		//Init
		virtual void Init() = 0;
		//Update
		virtual void Update() = 0;
		//Exit
		virtual void Exit() = 0;
	};
}