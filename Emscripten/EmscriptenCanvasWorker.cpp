#include "EmscriptenCanvasWorker.h"

EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;

bool value = true;

void ScummWeb::WebFrontEnd::Wasm::Emscripten::EmscriptenCanvasWorker::InitCanvas(char *canvasName, pthread_attr_t* attr) {
	emscripten_pthread_attr_settransferredcanvases(attr, "canvas");
}

void ScummWeb::WebFrontEnd::Wasm::Emscripten::EmscriptenCanvasWorker::OnThreadStart(char* canvasName) {
	EM_ASM(
		const canvas = findCanvasEventTarget("#canvas").offscreenCanvas;
		ScummWebModule['offScreenCanvas'] = canvas;
		ScummWebModule['imageData']= canvas.getContext('2d').createImageData(320, 200);
	);
}

void ScummWeb::WebFrontEnd::Wasm::Emscripten::EmscriptenCanvasWorker::DrawToCanvas(ScummWeb::WebFrontEnd::Wasm::Workers::CanvasCallbackData *drawToCanvas, int drawingAreaWidth, int drawingAreaHeight) {
	EM_ASM(
		{
			const data = $0;
			const size = $1;
			const value = $2;

			const imageData = ScummWebModule['imageData'];
			const ctx = ScummWebModule['offScreenCanvas'].getContext('2d');
			
			for (let i = 0; i <  size; i++) {
				if(value == 0)
				{
					imageData.data[i] = 0;
				}
				else
				{
					imageData.data[i] = 125;
				}
			}

			ctx.putImageData(imageData, 0, 0);
						
	},
		drawToCanvas->data, drawToCanvas->size, value);
		value = !value;
}
