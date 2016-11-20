/** The context of a Game Scene. It contains all the components that every game scene needs to run successfully.*/
#ifndef SCENE_CONTEXT_H
#define SCENE_CONTEXT_H
/* System */
/* Third Party */
/* SushiEngine */
#include "Window.h"
#include "AbstractRenderer.h"
#include "OpenGLRenderer.h"
#include "InputManager.h"
#include "Debug.h"
#include "Macros.h"
/* ---- */
namespace SushiEngine
{
	struct SceneContext
	{
		/* Constructor */
		SceneContext(const char * pTitle, const int pWidth, const int pHeight);
		~SceneContext();
		NO_COPY_CONSTRUCTORS(SceneContext)

		/* Instance fields */
		InputManager * input;
		AbstractRenderer * renderer;
		Window * window;

		/* Instance methods */
		void destroy();
	};
}
#endif
