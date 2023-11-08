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
void DrawLineInPixels(int x0, int y0, int x1, int y1, int width, u32 color){
    y0 += 39; //39 is an offset that I don't know why it exists
    y1 += 39; //Assuming the offset is required for y1 as well
    
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = (dx > dy ? dx : -dy) / 2, e2;
    
    while(1){
        for(int i = 0; i < width; i++){
            if(dx > dy){
                if(y0+i < renderBuffer.height){
                    u32 *pixel = renderBuffer.pixels + x0 + renderBuffer.width*(y0+i);
                    *pixel = color;
                }
            } else {
                if(x0+i < renderBuffer.width){
                    u32 *pixel = renderBuffer.pixels + (x0+i) + renderBuffer.width*y0;
                    *pixel = color;
                }
            }
        }
        
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void DrawPixel(int x, int y, u32 color){
    y += 40; //39 is an offset that exists for some reason
    u32 *pixel = renderBuffer.pixels + x + renderBuffer.width*y;
    *pixel = color;
}
