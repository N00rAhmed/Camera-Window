# Camera Window

### Introduction
This project accesses your laptops built in webcam and displays it in a window. I made this using C and SDL3 so its a pretty lightweight application. It's a very simple project because it was meant to address a problem that I was having. For creating the `.exe` InnoSetup was used.

### The Problem
Existing recording software like OBS have a feature which allows the webcam to be displayed in a separate window but with their feature if you click on any web page or software then the window will go behind the web page or software instead of staying on top of the page. My Camera Window stays on top of the page at all times including when the cursor is clicked.

### Languages/Tools
C, SDL3, Visual Studio, CLion, CMakeLists, Linux, InnoSetup

### Demo
<img width="1920" height="1080" alt="2026-11-25 01-49-47" src="https://github.com/user-attachments/assets/1bf45a1e-9203-4c1d-85f0-51352bf9494f" />

### Features
- [x] Webcam Access
- [x] Window Stays on Top
- [x] Resizable Window
- [ ] Draggable from Window Area 
- [ ] Borderless Window

### TroubleShooting
i was getting this error when opening exe on diffrent laptop `the code execution cannot proceed because Ucrtbased.dll was not found`. realised reason for this was that I compiled project in Debug Mode in Visual Studio. In Debug Mode this dependency is used `Ucrtbased.dll`. This dependencies isnt installed by default on windows machines which is why the error was caused. In order to fix this issue you need to switch to Release. In Release `ucrt.dll` is used which is found by default on all windows machines.

<img width="622" height="261" alt="image" src="https://github.com/user-attachments/assets/b38e798f-b1b1-4d92-8537-0dca9de80e2c" /> 

and rebuild solution 

<img width="1350" height="697" alt="image" src="https://github.com/user-attachments/assets/3a235612-a9e1-4b82-ae3f-52aeb85325e4" /> 

This should have created a `Release` folder where the new exe will be present. Use this new exe file to compile the exe for distribution.

### Links

https://www.youtube.com/watch?v=nvDLBM0l7nA

https://www.youtube.com/watch?v=l1p2GQxcP54

https://discourse.libsdl.org/t/creating-an-easily-distributable-executable-file/24413/2

https://wiki.libsdl.org/SDL3/SDL_SetWindowAlwaysOnTop

https://wiki.libsdl.org/SDL3/SDL_SetWindowResizable

https://stackoverflow.com/questions/79386427/resizing-a-borderless-window-is-not-working-in-sdl3

https://wiki.libsdl.org/SDL2/SDL_SetWindowBordered

https://stackoverflow.com/questions/80016665/sdl3-camera-api-unable-to-access-window-shows-green-screen-on-linux

https://discourse.libsdl.org/t/sdl3-camera/50347
