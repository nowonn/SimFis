void Tudo(f32 dt){
    ClearScreen(0x778fbf);//nao tirar
    
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
    
    DrawLineInPixels(260, 30, 860, 30, 1, 0xaa0000);
    DrawLineInPixels(260, 100, 860, 100, 1, 0xaa0000);
    DrawLineInPixels(260, 170, 860, 170, 1, 0xaa0000);
    
    for(int i = 599; i >= 1; i--){
        xAccelerationMemory[i] = xAccelerationMemory[i - 1];
        xSpeedMemory[i] = xSpeedMemory[i - 1];
        xPositionMemory[i] = xPositionMemory[i - 1];
        
        DrawPixel(-i - 100, 30 + xAccelerationMemory[i] * 0.0166, 0xff0000);
        DrawPixel(-i - 100, 100 + xSpeedMemory[i] * 0.0166, 0xff0000);
        DrawPixel(-i - 100, 170 + xPositionMemory[i] * 0.05, 0xff0000);
    }
    
    xAccelerationMemory[0] = tersio.acceleration[0];
    xSpeedMemory[0] = tersio.speed[0];
    xPositionMemory[0] = tersio.position[0];
}