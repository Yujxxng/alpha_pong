#pragma once

namespace GSM
{
	class BaseLevel
	{
	public:
		//Init
		virtual void Init() = 0;
		//Update
		virtual void Update() = 0;
		//Exit
		virtual void Exit() = 0;
	};
}