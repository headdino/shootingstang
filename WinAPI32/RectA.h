#pragma once
#include "GameNode.h"


class RectA :public GameNode
{
private:
	int a = 0;
	float b = 1.0f;
public:
	RectA();
	~RectA() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

