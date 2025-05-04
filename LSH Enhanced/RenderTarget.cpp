#include "RenderTarget.h"

bool UI::RenderTarget::IsRegistered()
{
	return UI::IS_NAMED_RENDERTARGET_REGISTERED((char*)Name.c_str());
}

bool UI::RenderTarget::IsLinked()
{
	return UI::IS_NAMED_RENDERTARGET_LINKED(Model);
}

void UI::RenderTarget::Release()
{
	if (IsRegistered())
	{
		UI::RELEASE_NAMED_RENDERTARGET((Any*)(char*)Name.c_str());
	}
}