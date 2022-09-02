This demonstrates a problem with updating the canvas through Emscripten on Pthreads.


Instructions:

1. Clone this repository 
2. Run the build.bat (Windows) or build.sh (Linux) file which is located in Emscripten folder
3. Run Chrome using special flags as follows: chrome --enable-features=SharedArrayBuffer --allow-file-access-from-files
4. Open CanvasFailExample.html from the Emscripten folder using this Chrome session
5. The canvas on the screen should alternate from grey to white every 5 seconds but it does not :(
6. Open the dev tools and go to the sources tab
7. Click on the very bottom thread (should be the bottom 'EmscriptenProcessGameMessage.worker.js')
8. Hit the pause button lots of times and notice that the canvas actually changes sometimes.
