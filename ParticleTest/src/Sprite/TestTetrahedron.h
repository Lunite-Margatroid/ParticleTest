#pragma once
#include "TestCube.h"

namespace ptt
{
	class TestTetrahedron : public TestCube
	{
		void Init();
	public:
		TestTetrahedron();

		void Render(const glm::mat4& modelTrans) override;

	};
}