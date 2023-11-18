#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "utils.c"
#include "math.c"
#include "platform_common.c"
#include "fontmap.c"

struct {
    int width, height;
    u32 *pixels;
    BITMAPINFO bitmapInfo;
} typedef RenderBuffer;

global_variable RenderBuffer renderBuffer;
global_variable enum GraphType graphType = ALL;
global_variable enum TargetValue targetValue = POS;
global_variable bool paused = false;
global_variable bool graphMode = false;
global_variable Object tersio;
global_variable Mola mola;
global_variable float xAccelerationMemory[600], xSpeedMemory[600], xPositionMemory[600];

#include "software_rendering.c"
#include "simulation.c"

#define fps 60
#define frameDelay (1000 / fps)

internal LRESULT CALLBACK windowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam){
    LRESULT result = 0;
    
    switch (message){
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        } break;
        case WM_SIZE:{ //Called when window is created or resized
            RECT rect;
            GetWindowRect(window, &rect);
            renderBuffer.width = rect.right - rect.left;
            renderBuffer.height = rect.bottom - rect.top;
            
            if(renderBuffer.pixels){
                VirtualFree(renderBuffer.pixels, 0, MEM_RELEASE);
            }
            renderBuffer.pixels = VirtualAlloc(0, sizeof(u32)*renderBuffer.width*renderBuffer.height, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
            renderBuffer.bitmapInfo.bmiHeader.biSize = sizeof(renderBuffer.bitmapInfo.bmiHeader);
            renderBuffer.bitmapInfo.bmiHeader.biWidth = renderBuffer.width;
            renderBuffer.bitmapInfo.bmiHeader.biHeight = renderBuffer.height;
            renderBuffer.bitmapInfo.bmiHeader.biPlanes = 1;
            renderBuffer.bitmapInfo.bmiHeader.biBitCount = 32;
            renderBuffer.bitmapInfo.bmiHeader.biCompression = BI_RGB;
        } break;
        
        default: result = DefWindowProcA(window, message, wParam, lParam);
    }
    
    return result;
};  

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    WNDCLASSA windowClass = {0};
    windowClass.style = CS_HREDRAW|CS_VREDRAW;
    windowClass.lpfnWndProc = windowCallback;
    
    windowClass.lpszClassName = "Simulator_Window_Class";
    
    RegisterClassA(&windowClass);
    
    HWND window = CreateWindowExA(0, "Simulator_Window_Class", "Simulador", WS_VISIBLE|WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 960 + 16, 640 + 39, 0, 0, 0, 0);
    
    HDC hdc = GetDC(window);
    
    //SetWindowOrgEx(hdc, 0, 0, NULL);
    
    Input input = {0};
    
    LARGE_INTEGER lastCounter;
    QueryPerformanceCounter(&lastCounter);
    
    LARGE_INTEGER frequencyCounter;
    QueryPerformanceFrequency(&frequencyCounter);
    
    f32 lastDt = 0.01666f;
    
    tersio.position[0] = 20;//M
    tersio.mass = 1;//M
    mola.kel = 5;//M
    
    mola.segments = 20;//limite de 50!! M
    
    tersio.position[1] = 280;
    tersio.velocity[0] = 0;
    tersio.velocity[1] = 0;
    tersio.acceleration[0] = 0;
    tersio.acceleration[1] = 0;
    tersio.width = 50;
    tersio.height = 50;
    tersio.color = 0xe6b720;
    
    mola.x0 = 420;
    mola.deformation = mola.x0 - tersio.position[0]; 
    mola.startX = 20;
    
    for(int i = 0; i < 600; i++){
        xAccelerationMemory[i] = 0;
        xSpeedMemory[i] = 0;
        xPositionMemory[i] = 0;
    }
    
    while (running){ //Main Loop!
        //Input
        for (int i = 0; i < BUTTON_COUNT; i++) input.buttons[i].changed = false;
        
        MSG message;
        while (PeekMessageA(&message, window, 0, 0, PM_REMOVE)){
            switch (message.message) {
                case WM_SYSKEYDOWN: 
                case WM_SYSKEYUP: 
                case WM_KEYDOWN: 
                case WM_KEYUP: {
                    u32 vkCode = (u32)message.wParam;
                    b32 wasDown = ((message.lParam & (1 << 30)) != 0);
                    b32 isDown = ((message.lParam & (1 << 31)) == 0);
                    
#define ProcessButton(vk, b)\
if (vkCode == vk){\
input.buttons[b].changed = isDown != input.buttons[b].isDown;\
input.buttons[b].isDown = isDown;\
}
                    ProcessButton(VK_LEFT, BUTTON_LEFT);
                    ProcessButton(VK_RIGHT, BUTTON_RIGHT);
                    ProcessButton(VK_UP, BUTTON_UP);
                    ProcessButton(VK_DOWN, BUTTON_DOWN);
                    ProcessButton(0x47, BUTTON_GRAPH);
                    ProcessButton(0x20, BUTTON_PAUSE);
                    ProcessButton(0x1B, BUTTON_ESCAPE);
                    ProcessButton(0x53, BUTTON_SHIFT);
                    
                } break;
                default: {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            }
        }
        
        //Simulation
        Tudo(&input, lastDt);
        
        //Render
        StretchDIBits(hdc, 0, 0, renderBuffer.width, renderBuffer.height, 0, 0, renderBuffer.width, renderBuffer.height, renderBuffer.pixels, &renderBuffer.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
        
        //Get frame time
        LARGE_INTEGER currentCounter;
        QueryPerformanceCounter(&currentCounter);
        
        lastDt = (f32)(currentCounter.QuadPart - lastCounter.QuadPart) / (f32)frequencyCounter.QuadPart;
        
        lastCounter = currentCounter;
        
        if (frameDelay > lastDt){
            Sleep(frameDelay - lastDt);
        }
    }
};
