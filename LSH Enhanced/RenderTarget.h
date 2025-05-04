#pragma once

#include <string>
#include "script.h"

namespace UI
{
	class RenderTarget
	{
	public:
		int Handle;

		std::string Name;

		int Model;

		bool IsRegistered();

		bool IsLinked();

		RenderTarget(std::string name, int model)
		{
			Name = name;
			Model = model;
			if (!IsRegistered())
			{
				UI::REGISTER_NAMED_RENDERTARGET((char*)name.c_str(), 0);
			}
			if (!IsLinked())
			{
				UI::LINK_NAMED_RENDERTARGET(model);
			}
			if (IsRegistered())
			{
				Handle = UI::GET_NAMED_RENDERTARGET_RENDER_ID((char*)name.c_str());
			}
		}

		~RenderTarget()
		{
			Release();
		}

		void Release();
	};
}