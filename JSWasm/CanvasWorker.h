#pragma once
#include "QueueWorker.h"

namespace ScummWeb {
namespace WebFrontEnd {
namespace Wasm {
namespace Workers {
typedef unsigned char byte;
struct CanvasCallbackData {
public:
	    byte *data;
		int highestX;
		int highestY;
		int lowestX;
		int lowestY;
		int size;
		int lowestIndex;
	};
typedef void(*drawToCanvas)(CanvasCallbackData *, int drawingAreaWidth, int drawingAreaHeight);
typedef void (*initCanvas)(char *canvasName, pthread_attr_t* attr);
typedef void (*onThreadStart)(char* canvasName);

class CanvasWorker : public QueueWorker<CanvasWorker, CanvasCallbackData> {
	static CanvasWorker *_worker;
	drawToCanvas _fnDrawToCanvas;
	initCanvas _initCanvas;
	onThreadStart _onThreadStart;
	int _width;
	int _height;

protected:
	void PreStart(pthread_attr_t* attr) override;
	void OnThreadStart() override;
public:
	void Init(int sleepMs, int width, int height, drawToCanvas drawToCanvas, initCanvas initCanvas, onThreadStart onThreadStart);
	static CanvasWorker *GetCanvasWorker();
	static void CanvasWorkerWorkFunction(CanvasWorker *queueWorker, CanvasCallbackData *callbackData);
};
} // namespace Workers
} // namespace Wasm
} // namespace WebFrontEnd
} // namespace ScummWeb
