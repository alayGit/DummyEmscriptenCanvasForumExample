#include "../JSWasm/CanvasWorker.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/threading.h>
#include <string.h>
typedef unsigned char byte;
namespace ScummWeb {
namespace WebFrontEnd {
namespace Wasm {
namespace Emscripten {
class EmscriptenCanvasWorker {
public:
	static void InitCanvas(char *canvasName, pthread_attr_t *attr);
		static void DrawToCanvas(ScummWeb::WebFrontEnd::Wasm::Workers::CanvasCallbackData * drawToCanvas, int drawingAreaWidth, int drawingAreaHeight);
		static void OnThreadStart(char* canvasName);
	};
} // namespace Emscripten
} // namespace Wasm
} // namespace WebFrontEnd
} // namespace ScummWeb
