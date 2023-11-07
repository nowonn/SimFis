void Tudo(f32 dt){
    ClearScreen(0x778fbf);//nao tirar
    
    for(int i = 0; i < 2; i++){ 
        tersio.speed[i] += tersio.acceleration[i] * dt;
        tersio.position[i] += tersio.speed[i] * dt; 
        
        if(tersio.position[0] >= 960) tersio.position[0] = 960;
        if(tersio.position[1] + tersio.height >= 600) tersio.position[1] = 600 - tersio.height;
        if(tersio.position[0] <= 0) tersio.position[0] = 0;
        if(tersio.position[1] <= 0) tersio.position[1] = 0;
    }
    
    mola.deformation = mola.x0 - tersio.position[0];
    tersio.acceleration[0] = mola.deformation * mola.kel / tersio.mass;
    
    DrawRectInPixels(0, tersio.position[1] + tersio.height / 2 - 3, mola.x0 - mola.deformation, 6, 0x333333);//mola
    DrawRectInPixels(tersio.position[0], tersio.position[1], tersio.width, tersio.height, tersio.color);//tersio
    DrawRectInPixels(mola.x0, tersio.position[1] - tersio.height/2, 1, tersio.height*2, 0xff0000);//linha do x0 da mola
    DrawRectInPixels(0, 270, 20, 331, 0x361b03);//parede
    DrawRectInPixels(0, 0, 960, 280, 0x111111);//chao
}