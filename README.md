# Camera Window

### Introduction
This project creates a window that accesses your laptops camera. It's a very simple project because it was meant to address a problem that I was having with OBS. For creating the `.exe` InnoSetup was used.

i was getting this error when opening exe on diffrent laptop `the code execution cannot proceed because Ucrtbased.dll was not found`. realised reason for this was that I compiled project in Debug Mode in Visual Studio. In Debug Mode the Ucrtbased.dll isnt present for EXE but for Releases it is present. Switch to Release 

<img width="622" height="261" alt="image" src="https://github.com/user-attachments/assets/b38e798f-b1b1-4d92-8537-0dca9de80e2c" /> 

and rebuild solution 

<img width="1350" height="697" alt="image" src="https://github.com/user-attachments/assets/3a235612-a9e1-4b82-ae3f-52aeb85325e4" /> 

This should have created a `Release` folder where the new exe will be present. Use this new exe file to compile the exe for distribution.



### Languages/Tools
C, SDL3, Visual Studio

### Demo
https://github.com/user-attachments/assets/1ad55b65-1c1c-4773-9ee5-00284807b2e2

### Links

https://www.youtube.com/watch?v=nvDLBM0l7nA

https://www.youtube.com/watch?v=l1p2GQxcP54

https://discourse.libsdl.org/t/creating-an-easily-distributable-executable-file/24413/2

https://wiki.libsdl.org/SDL3/SDL_SetWindowAlwaysOnTop

https://wiki.libsdl.org/SDL3/SDL_SetWindowResizable

https://stackoverflow.com/questions/79386427/resizing-a-borderless-window-is-not-working-in-sdl3

https://wiki.libsdl.org/SDL2/SDL_SetWindowBordered
