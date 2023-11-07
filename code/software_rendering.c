void ClearScreen(u32 color){
    u32 *pixel = renderBuffer.pixels;
    
    for(int y = 0; y < renderBuffer.height; y++){
        for(int x = 0; x < renderBuffer.width; x++){
            *pixel++ = color;
        }
    }
}

void DrawRectInPixels(int x0, int y0, int width, int height, u32 color){
    y0 += 39;//39 eh um offset estranho q eu n sei pq existe
    for(int y = y0; y < y0 + height; y++){
        u32 *pixel = renderBuffer.pixels + x0 + renderBuffer.width*y;
        for(int x = x0; x < x0 + width; x++){
            *pixel++ = color;
        }
    }
}