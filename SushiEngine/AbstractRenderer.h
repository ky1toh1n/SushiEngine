/* AbstractRenderer - A base renderer which can be extended to use any graphics API. */
#ifndef ABSTRACT_RENDERER_H
#define ABSTRACT_RENDERER_H
/* SushiEngine */
#include "Window.h"
#include "Camera.h"
#include "SuGameObject.h"
/* ---- */
namespace SushiEngine
{
	class AbstractRenderer
	{
	public:
		/* Constructor */
		AbstractRenderer(Window*);
		virtual ~AbstractRenderer() = 0;

		/* Instance methods */
		virtual void render(SuGameObject* gameObject) = 0;
		void setCamera(Camera*);
	protected:
		/* Instance fields */
		Window* mWindow;
		Camera* mCamera;
	};
}
#endif
