void Tudo(Input *input, f32 dt){
    if(Pressed(BUTTON_ESCAPE)) running = false;
    if(Pressed(BUTTON_GRAPH)) graphMode = !graphMode;
    if(Pressed(BUTTON_PAUSE)) paused = !paused;
    if(Pressed(BUTTON_UP)) graphType++;
    if(Pressed(BUTTON_DOWN)) graphType--;
    if(graphType > ALL) graphType = ACCELERATION;
    else if(graphType < ACCELERATION) graphType = ALL;
    
    ClearScreen(0x778fbf);
    
    DrawRectInPixels(65, 550, 80, 80, 0xffed2b);
    
    DrawRectInPixels(50, 520, 150, 48, 0xffffff);
    DrawRectInPixels(120, 550, 110, 48, 0xffffff);
    DrawRectInPixels(160, 510, 160, 60, 0xffffff);
    
    DrawRectInPixels(450, 460, 150, 48, 0xffffff);
    DrawRectInPixels(520, 490, 110, 48, 0xffffff);
    DrawRectInPixels(560, 450, 160, 60, 0xffffff);
    
    DrawRectInPixels(850, 490, 110, 48, 0xffffff);
    DrawRectInPixels(920, 520, 40, 48, 0xffffff);
    
    if(!paused){
        for(int i = 0; i < 2; i++){ 
            tersio.velocity[i] += tersio.acceleration[i] * dt;
            tersio.position[i] += tersio.velocity[i] * dt; 
            
            if(tersio.position[0] >= 960 - tersio.width) {
                tersio.position[0] = 960 - tersio.width;
                tersio.velocity[0] = 0;
                tersio.acceleration[0] = 0;
            }
            if(tersio.position[0] <= 20) {
                tersio.position[0] = 20;
                tersio.velocity[0] = 0;
                tersio.acceleration[0] = 0;
            }
        }
        
        mola.deformation = mola.x0 - tersio.position[0];
        tersio.acceleration[0] = mola.deformation * mola.kel / tersio.mass;
    } else {
        int direction = IsDown(BUTTON_LEFT) * (-1) + IsDown(BUTTON_RIGHT);
        tersio.position[0] += direction * 5; 
        if(tersio.position[0] >= 960 - tersio.width) {
            tersio.position[0] = 960 - tersio.width;
            tersio.velocity[0] = 0;
            tersio.acceleration[0] = 0;
        }
        if(tersio.position[0] <= 20) {
            tersio.position[0] = 20;
            tersio.velocity[0] = 0;
            tersio.acceleration[0] = 0;
        }
        
        for(int i = 0; i < 2; i++){ 
            if(direction){
                tersio.velocity[i] = 0;
                tersio.acceleration[i] = 0;
            }
        }
    }
    
    DrawSpring();
    
    DrawRectInPixels(tersio.position[0], tersio.position[1], tersio.width, tersio.height, tersio.color);//tersio
    DrawLineInPixels(mola.x0, tersio.position[1] - tersio.height/2,
                     mola.x0, tersio.position[1] + tersio.height*1.5,
                     1, 0x000000);//linha do x0 da mola
    DrawString(mola.x0 - 28, tersio.position[1] + tersio.height*1.5 + 2, "spring x0", 1, 0x000000);
    DrawRectInPixels(0, 270, mola.startX, 370, 0x111111);//parede
    DrawRectInPixels(0, 0, 960, 280, 0x111111);//chao
    
    DrawString(818, 620, "all rights reserved", 1, 0xffffff);
    DrawString(818, 608, " to ti, gi and ana", 1, 0xffffff);
    DrawString(818, 596, "bcc ufscar sorocaba", 1, 0xffffff);
    
    if(!graphMode){
        switch(graphType){
            case ACCELERATION:
            DrawGraphMeasurements(310, 10, 910, 248,
                                  340, 130,
                                  1, 0.03, 10, "mpsps", 0x555555);
            DrawString(738, 13, "acceleration", 2, 0x00ff00);
            break;
            case VELOCITY:
            DrawGraphMeasurements(310, 10, 910, 248,
                                  340, 130,
                                  1, 0.03, 10, "mps", 0x555555);
            DrawString(794, 13, "velocity", 2, 0x00ff00);
            break;
            case POSITION:
            DrawGraphMeasurements(310, 10, 910, 248,
                                  340, 30,
                                  1, 0.25, 1, "m", 0x555555);
            DrawString(794, 13, "position", 2, 0x00ff00);
            break;
            default:
            DrawLineInPixels(310, 200, 910, 200, 1, 0x555555);
            DrawLineInPixels(310, 130, 910, 130, 1, 0x555555);
            DrawLineInPixels(310, 30, 910, 30, 1, 0x555555);
            DrawString(138, 193, "acceleration", 2, 0x00ff00);
            DrawString(194, 123, "velocity", 2, 0x00ff00);
            DrawString(194, 53, "position", 2, 0x00ff00);
        }
        
        for(int i = 599; i >= 0; i--){
            if(!i && !paused){
                xAccelerationMemory[0] = tersio.acceleration[0];
                xSpeedMemory[0] = tersio.velocity[0];
                xPositionMemory[0] = tersio.position[0] - 20;//-20 pra colocar origem na parede
            } else if(!paused){
                xAccelerationMemory[i] = xAccelerationMemory[i - 1];
                xSpeedMemory[i] = xSpeedMemory[i - 1];
                xPositionMemory[i] = xPositionMemory[i - 1];
            }
            
            switch(graphType){
                case ACCELERATION:
                DrawPixel(909-i, 130 + xAccelerationMemory[i] * 0.03, 0xff0000);
                break;
                case VELOCITY:
                DrawPixel(909-i, 130 + xSpeedMemory[i] * 0.03, 0xff0000);
                break;
                case POSITION:
                DrawPixel(909-i, 30 + xPositionMemory[i] * 0.25, 0xff0000);
                break;
                default:
                DrawPixel(909-i, 200 + xAccelerationMemory[i] * 0.01, 0xff0000);
                DrawPixel(909-i, 130 + xSpeedMemory[i] * 0.01, 0xff0000);
                DrawPixel(909-i, 30 + xPositionMemory[i] * 0.1, 0xff0000);
            }
        }
        
        DrawHollowRectInPixels(310, 10, 600, 240, 2, 0xff0000);
        
        for(int i = 0; i < 9; i++){
            DrawLineInPixels(mola.startX + 100 * i, 279, mola.startX + 100 * i, 260,
                             1, 0xff0000);
            DrawChar(mola.startX + 100 * i + 5, 256, '0' + i, 2, 0xff0000);
            DrawChar(mola.startX + 100 * i + 5 + 14, 256, 'm', 2, 0xff0000);
        }//regua
    } else {
        DrawRectInPixels(48, 32, 864, 576, 0x0f0f0f);
        
        switch(graphType){
            case ACCELERATION:
            DrawGraphMeasurements(48, 32, 912, 608,
                                  258, 320,
                                  1, 0.1, 5, "mpsps", 0x555555);
            DrawString(75, 55, "acceleration", 2, 0x00ff00);
            break;
            case VELOCITY:
            DrawGraphMeasurements(48, 32, 912, 608,
                                  258, 320,
                                  1, 0.1, 5, "mps", 0x555555);
            DrawString(75, 50, "velocity", 3, 0x00ff00);
            break;
            case POSITION:
            DrawGraphMeasurements(48, 32, 912, 608,
                                  258, 70,
                                  1, 0.5, 1, "m", 0x555555);
            DrawString(75, 50, "position", 3, 0x00ff00);
            break;
            default:
            DrawLineInPixels(310, 494, 911, 494, 1, 0x555555);
            DrawLineInPixels(310, 350, 911, 350, 1, 0x555555);
            DrawLineInPixels(310, 42, 911, 42, 1, 0x555555);
            DrawString(138, 486, "acceleration", 2, 0x00ff00);
            DrawString(194, 342, "velocity", 2, 0x00ff00);
            DrawString(194, 140, "position", 2, 0x00ff00);
        }
        
        for(int i = 599; i >= 0; i--){
            if(!i && !paused){
                xAccelerationMemory[0] = tersio.acceleration[0];
                xSpeedMemory[0] = tersio.velocity[0];
                xPositionMemory[0] = tersio.position[0] - 20;//-20 pra colocar origem na parede
            } else if(!paused){
                xAccelerationMemory[i] = xAccelerationMemory[i - 1];
                xSpeedMemory[i] = xSpeedMemory[i - 1];
                xPositionMemory[i] = xPositionMemory[i - 1];
            }
            
            switch(graphType){
                case ACCELERATION:
                DrawPixel(911-i, 320 + xAccelerationMemory[i] * 0.1, 0xff0000);
                break;
                case VELOCITY:
                DrawPixel(911-i, 320 + xSpeedMemory[i] * 0.1, 0xff0000);
                break;
                case POSITION:
                DrawPixel(911-i, 70 + xPositionMemory[i] * 0.5, 0xff0000);
                break;
                default:
                DrawPixel(911-i, 494 + xAccelerationMemory[i] * 0.03, 0xff0000);
                DrawPixel(911-i, 350 + xSpeedMemory[i] * 0.03, 0xff0000);
                DrawPixel(911-i, 42 + xPositionMemory[i] * 0.3, 0xff0000);
            }
        }
        
        DrawHollowRectInPixels(48, 32, 864, 576, 2, 0xff0000);
    }
}