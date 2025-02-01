/**
 * @file Nanosuit.h
 */

#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include "Object/ArObject.h"

namespace dotGLASS {
	namespace Object {

		/**
		 * @class Nanosuit Nanosuit.h "Object/Nanosuit.h"
		 */
		class Nanosuit : public ArObject {
			public:
				Nanosuit();
				~Nanosuit();
		};

	}
}
