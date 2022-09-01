// Emscripten7ZCompression.cpp : Defines the functions for the static library.
//

#include "EmscriptenProcessGameMessages.h"
extern "C" {


EMSCRIPTEN_KEEPALIVE
void StartWorkers() {
	ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker::GetCanvasWorker()->Init(2, 320, 200, &ScummWeb::WebFrontEnd::Wasm::Emscripten::EmscriptenCanvasWorker::DrawToCanvas, &ScummWeb::WebFrontEnd::Wasm::Emscripten::EmscriptenCanvasWorker::InitCanvas, &ScummWeb::WebFrontEnd::Wasm::Emscripten::EmscriptenCanvasWorker::OnThreadStart);
    ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker::GetCanvasWorker()->Start();
}


EMSCRIPTEN_KEEPALIVE
void EnqueueMessageOnWorker() {
	const int size = 320 * 200 * 4;
	
	byte* data = new byte[size];
	
	for(int i = 0; i < size; i++) //Real system would actually pass in data
	{
		data[i] = 0;
	}
	
	ScummWeb::WebFrontEnd::Wasm::Workers::CanvasCallbackData* canvasData = new ScummWeb::WebFrontEnd::Wasm::Workers::CanvasCallbackData();
	
	canvasData->data = data;
	canvasData->highestX = 320;
	canvasData->highestY = 200;
	canvasData->size = size;
	canvasData->lowestIndex = 0;
	
	
	ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker::GetCanvasWorker()->Enqueue(canvasData);
}
}
