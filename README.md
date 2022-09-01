This demonstrates a problem with updating the canvas through Emscripten on Pthreads.


Instructions:

(Sorry I am a Windows user, so I am providing a .bat file)

1. Clone this repository 
2. Run the build.bat which is located in Emscripten folder
3. Run Chrome using special flags as follows: chrome --enable-features=SharedArrayBuffer --allow-file-access-from-files
4. Open CanvasFailExample.html from the Emscripten folder
5. 
