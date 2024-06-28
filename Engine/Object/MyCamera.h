#pragma once
#include "MyActor.h"

namespace MyProject
{
	class MyCamera : public MyActor
	{
	public:
		const mat3 GetViewMat() const;

		void ZoomIn(const float _scale);
		void ZoomOut(const float _scale);

		void LookAtObject(MyObject & _obj);

		virtual void Update(const float _deltaTime) override;
		virtual void Render(const mat3& _viewMat) override;
	};
}

