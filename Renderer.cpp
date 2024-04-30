#include "Renderer.h"

using namespace std;
Renderer::Renderer() {
}


Renderer::~Renderer() {

}

void Renderer::draw(const VertexArray* va, const IndexBuffer* ib) const {
	va->bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(ArObject* arObject) {
	Model model = arObject->getModel();
	for (int i = 0; i < model.getMeshes().size(); i++) {
		Mesh mesh = model.getMeshes().at(i);
		draw(mesh.getVA(), mesh.getIB());
	}
}

void Renderer::clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}