void Tudo(Input *input, f32 dt){
    if (Pressed(BUTTON_ESCAPE)) running = false;
    if (Pressed(BUTTON_GRAPH)) graphMode = !graphMode;
    if (Pressed(BUTTON_PAUSE)) paused = !paused;
    
    ClearScreen(0x778fbf);//nao tirar
    
    if(!paused){
        for(int i = 0; i < 2; i++){ 
            tersio.speed[i] += tersio.acceleration[i] * dt;
            tersio.position[i] += tersio.speed[i] * dt; 
            
            if(tersio.position[0] >= 960) tersio.position[0] = 960;
            if(tersio.position[1] + tersio.height >= 600) tersio.position[1] = 600 - tersio.height;
            if(tersio.position[0] <= 20) tersio.position[0] = 20;
            if(tersio.position[1] <= 0) tersio.position[1] = 0;
        }
        
        mola.deformation = mola.x0 - tersio.position[0];
        tersio.acceleration[0] = mola.deformation * mola.kel / tersio.mass;
    } else {
        int direction = IsDown(BUTTON_LEFT) * (-1) + IsDown(BUTTON_RIGHT);
        tersio.position[0] += direction * 5; 
        
        for(int i = 0; i < 2; i++){ 
            if(direction){
                tersio.speed[i] = 0;
                tersio.acceleration[i] = 0;
            }
        }
    }
    
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
    }//mola
    DrawRectInPixels(tersio.position[0], tersio.position[1], tersio.width, tersio.height, tersio.color);//tersio
    DrawLineInPixels(mola.x0, tersio.position[1] - tersio.height/2,
                     mola.x0, tersio.position[1] + tersio.height*1.5,
                     1, 0xff0000);//linha do x0 da mola
    DrawRectInPixels(0, 270, xs[0], 331, 0x361b03);//parede
    DrawRectInPixels(0, 0, 960, 280, 0x111111);//chao
    
    if(!graphMode){
        DrawLineInPixels(310, 190, 910, 190, 1, 0xaa0000);
        DrawLineInPixels(310, 120, 910, 120, 1, 0xaa0000);
        DrawLineInPixels(310, 20, 910, 20, 1, 0xaa0000);
        
        for(int i = 599; i >= 1; i--){
            if(!paused){
                xAccelerationMemory[i] = xAccelerationMemory[i - 1];
                xSpeedMemory[i] = xSpeedMemory[i - 1];
                xPositionMemory[i] = xPositionMemory[i - 1];
            }
            
            DrawPixel(910-i, 190 + xAccelerationMemory[i] * 0.0166, 0xff0000);
            DrawPixel(910-i, 120 + xSpeedMemory[i] * 0.0166, 0xff0000);
            DrawPixel(910-i, 20 + xPositionMemory[i] * 0.10, 0xff0000);
        }
        
        xAccelerationMemory[0] = tersio.acceleration[0];
        xSpeedMemory[0] = tersio.speed[0];
        xPositionMemory[0] = tersio.position[0];
        
        DrawPixel(910, 190 + xAccelerationMemory[0] * 0.0166, 0xff0000);
        DrawPixel(910, 120 + xSpeedMemory[0] * 0.0166, 0xff0000);
        DrawPixel(910, 20 + xPositionMemory[0] * 0.10, 0xff0000);
        
        DrawHollowRectInPixels(310, 10, 601, 240, 2, 0xff0000);
    } else {
        DrawRectInPixels(48, 32, 864, 576, 0x0f0f0f);
        
        DrawLineInPixels(50, 464, 908, 464, 1, 0xaa0000);
        DrawLineInPixels(50, 320, 908, 320, 1, 0xaa0000);
        DrawLineInPixels(50, 42, 908, 42, 1, 0xaa0000);
        
        for(int i = 599; i >= 1; i--){
            if(!paused){
                xAccelerationMemory[i] = xAccelerationMemory[i - 1];
                xSpeedMemory[i] = xSpeedMemory[i - 1];
                xPositionMemory[i] = xPositionMemory[i - 1];
            }
            
            DrawPixel(910-i, 464 + xAccelerationMemory[i] * 0.0166 * 3, 0xff0000);
            DrawPixel(910-i, 320 + xSpeedMemory[i] * 0.0166 * 3, 0xff0000);
            DrawPixel(910-i, 42 + xPositionMemory[i] * 0.3, 0xff0000);
        }
        
        xAccelerationMemory[0] = tersio.acceleration[0];
        xSpeedMemory[0] = tersio.speed[0];
        xPositionMemory[0] = tersio.position[0];
        
        DrawPixel(910, 464 + xAccelerationMemory[0] * 0.0166 * 3, 0xff0000);
        DrawPixel(910, 320 + xSpeedMemory[0] * 0.0166 * 3, 0xff0000);
        DrawPixel(910, 42 + xPositionMemory[0] * 0.3, 0xff0000);
        
        DrawHollowRectInPixels(50, 34, 858, 570, 2, 0xff0000);
    }
    
    DrawString(100, 100, "the quick brown fox jumped over the lazy dog 1234567890", 1, 0x00ff00);
}