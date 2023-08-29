#include "stdafx.h"
#include "RectA.h"


RectA::RectA()
{
}


RectA::~RectA()
{
}

HRESULT RectA::init()
{
	

	return S_OK;
}

void RectA::release()
{
}

void RectA::update()
{
	if (KEYMANAGER->StayKeyDown(VK_LEFT))
	{
		a++;
	}
	if (KEYMANAGER->StayKeyDown(VK_RIGHT))
	{
		a--;
	}
	if (KEYMANAGER->StayKeyDown(VK_UP))
	{
		b += 0.01f;
	}
	if (KEYMANAGER->StayKeyDown(VK_DOWN))
	{
		b -= 0.01f;
	}
}

void RectA::render()
{

}
