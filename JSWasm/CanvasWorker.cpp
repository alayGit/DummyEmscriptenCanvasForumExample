#pragma once
#include "CanvasWorker.h"

void ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker::PreStart(pthread_attr_t* attr) {
	_initCanvas(nullptr, attr);
}

void ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker::OnThreadStart() {
	_onThreadStart(nullptr);
}

void ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker::Init(int sleepMs, int width, int height, drawToCanvas drawToCanvas, initCanvas initCanvas, onThreadStart onThreadStart) {
	QueueWorker::Init(&CanvasWorkerWorkFunction, sleepMs);
	_fnDrawToCanvas = drawToCanvas;
	_width = width;
	_height = height;
	_initCanvas = initCanvas;
	_onThreadStart = onThreadStart;
}

ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker *ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker::GetCanvasWorker() {
	if (!_worker) {
		_worker = new CanvasWorker();
	}
	return _worker;
}

void ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker::CanvasWorkerWorkFunction(CanvasWorker *canvasWorker, CanvasCallbackData* cbd) {
	canvasWorker->_fnDrawToCanvas(cbd, canvasWorker->_width, canvasWorker->_height);

	delete[] cbd->data;
	delete cbd;
}

ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker* ScummWeb::WebFrontEnd::Wasm::Workers::CanvasWorker::_worker;
