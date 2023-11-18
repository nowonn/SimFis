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

void DrawHollowRectInPixels(int x0, int y0, int width, int height, int lineWidth, u32 color){
    DrawLineInPixels(x0, y0, x0 + width, y0, lineWidth, color);
    DrawLineInPixels(x0 + width, y0, x0 + width, y0 + height, lineWidth, color);
    DrawLineInPixels(x0 + width, y0 + height, x0, y0 + height, lineWidth, color);
    DrawLineInPixels(x0, y0 + height, x0, y0, lineWidth, color);
}

void DrawPixel(int x, int y, u32 color){
    y += 40; //39 is an offset that exists for some reason
    u32 *pixel = renderBuffer.pixels + x + renderBuffer.width*y;
    *pixel = color;
}

void DrawChar(int x0, int y0, char c, int size, u32 color){
    if(c == ' ') return;
    
    int index = c - (c > 96) * 97 - !(c > 96) * 22;
    if(c == ',') index = 37;
    else if(c == '.') index = 38;
    
    for(int j = 0; j < 12; j++){
        for(int i = 0; i < 7; i++){
            if(fontmap[77 - (7 * j) + i + 84 * index])
                DrawRectInPixels(x0 + i * size, y0 + j * size, size, size, color);
        }
    }
}

void DrawString(int x0, int y0, char s[137], int size, u32 color){
    for(int i = 0; i < 136 && s[i] != '\0'; i++){
        DrawChar(x0 + 7 * size * i, y0, s[i], size, color);
    }
}

void DrawSpring(){
    float xs[50];
    xs[0] = mola.startX;
    for(int i = 1; i < mola.segments + 1; i++){
        xs[i] = xs[0] + i * (tersio.position[0] - xs[0])/mola.segments;
        DrawLineInPixels(xs[i - 1], tersio.position[1] + tersio.height / 2 - 20,
                         (xs[i] + xs[i - 1])/2, tersio.position[1] + tersio.height / 2 + 20,
                         2, 0x444444);
        DrawLineInPixels((xs[i] + xs[i - 1])/2, tersio.position[1] + tersio.height / 2 + 20,
                         xs[i], tersio.position[1] + tersio.height / 2 - 20,
                         2, 0x222222);
    }
}

void DrawGraphMeasurements(int x0, int y0, int x1, int y1, int originX, int originY, int fontSize, float scale, int step, char unit[5], u32 color){
    int pixelStep = step * 100 * scale;
    for(int i = (x0 - originX) / pixelStep; i < (x1 - originX) / pixelStep + 1; i++){
        DrawLineInPixels(originX + pixelStep * i, y0,
                         originX + pixelStep * i, y1, 1, color);
        //DrawChar(originX + pixelStep * i + 3, originY - 12, '0' + i, 1, 0x00ff00);
        //DrawChar(originX + pixelStep * i + 10, originY - 12, 's', 1, 0x00ff00);
    }
    for(int i = (y0 - originY) / pixelStep; i < (y1 - originY) / pixelStep + 1; i++){
        DrawLineInPixels(x0, originY + pixelStep * i, x1, originY + pixelStep * i, fontSize, color);
        if(i < 0) DrawChar(originX + 3 + (i * step > -10) * 7, originY + pixelStep * i  + 3, '0' + 10, fontSize, 0x00ff00);
        if(i * i * step * step > 81) {
            DrawChar(originX + 3 + fontSize * 7, originY + pixelStep * i + 3, '0' + ((i - (i < 0) * 2 * i) * step) / 10, fontSize, 0x00ff00);
            DrawChar(originX + 3 + fontSize * 14, originY + pixelStep * i + 3, '0' + ((i - (i < 0) * 2 * i) * step) % 10, fontSize, 0x00ff00);
        } else{
            DrawChar(originX + 3 + fontSize * 14, originY + pixelStep * i + 3, '0' + ((i - (i < 0) * 2 * i) * step), fontSize, 0x00ff00);
        }
        DrawString(originX + 3 + fontSize * 21, originY + pixelStep * i + 3, unit, fontSize, 0x00ff00);
    }
    
    DrawLineInPixels(x0, originY, x1, originY, 2, color);
    DrawLineInPixels(originX, y0, originX, y1, 2, color);
}
