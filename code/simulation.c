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
                         1, 0x333333);
        DrawLineInPixels((xs[i] + xs[i - 1])/2, tersio.position[1] + tersio.height / 2 + 20,
                         xs[i], tersio.position[1] + tersio.height / 2 - 20,
                         1, 0x333333);
    }//mola
    DrawRectInPixels(tersio.position[0], tersio.position[1], tersio.width, tersio.height, tersio.color);//tersio
    DrawLineInPixels(mola.x0, tersio.position[1] - tersio.height/2,
                     mola.x0, tersio.position[1] + tersio.height*1.5,
                     1, 0xff0000);//linha do x0 da mola
    DrawRectInPixels(0, 270, xs[0], 331, 0x361b03);//parede
    DrawRectInPixels(0, 0, 960, 280, 0x111111);//chao
}