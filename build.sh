#!/bin/sh
em++ -O0 -g ^
-o EmscriptenProcessGameMessages.js ^
EmscriptenCanvasWorker.cpp ^
EmscriptenProcessGameMessages.cpp ^
..\JSWasm\CanvasWorker.cpp ^
-pthread -v -s MODULARIZE=1  ^
--no-entry -s "EXPORTED_RUNTIME_METHODS='getValue', 'setValue', 'cwrap', 'ccall', 'printErr', 'EmVal'" ^
-s PTHREAD_POOL_SIZE=3  -s "EXPORT_NAME='ScummWebModule'" -s"LLD_REPORT_UNDEFINED" -s"TOTAL_MEMORY=1024MB" ^
-s OFFSCREENCANVAS_SUPPORT=1 --bind
