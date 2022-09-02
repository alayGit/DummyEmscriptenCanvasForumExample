This demonstrates a problem with updating the canvas through Emscripten on Pthreads.


Instructions:

1. Clone this repository 
2. Run the build.bat (Windows) or build.sh (Linux) file which is located in Emscripten folder
3. Run Chrome using special flags as follows: chrome --enable-features=SharedArrayBuffer --allow-file-access-from-files
4. Open CanvasFailExample.html from the Emscripten folder using this Chrome session
5. The canvas on the screen should alternate from grey to white every 3 seconds but it does not :(
6. Open the dev tools and go to the sources tab
7. Click on the very bottom thread (should be the bottom 'EmscriptenProcessGameMessage.worker.js')
8. Hit the pause button lots of times and notice that the canvas actually changes sometimes.

This example requires lots of boilerplate, so here are the key points

Key Points:
1. Canvas is transfered to Pthread in EmscriptenCanvasWorker.cpp line 8
2. Canvas is retrieved by the PThread in EmscriptenCanvasWorker.cpp line 12 and put into the module for retrieval EmscriptenCanvasWorker.cpp line 12
3. Drawing takes place EmscriptenCanvasWorker.cpp line 20
4. Data is queued. CanvasFailExample.html line 12. Note in the real application data is actually enqueued, here we are passing nothing and generating nonsense data. 

The version of Emscripten I am using is 3.1.17
