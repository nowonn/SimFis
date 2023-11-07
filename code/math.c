#define PI 3.1415926535
#define DR 0.0174533

internal int
clamp(int min, int val, int max){
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

internal f32 DegToRad(f32 a) { return a * PI/180.0;}
internal f32 FixAng(f32 a){ if(a>2*PI){a-=2*PI;} if(a<0){ a+=2*PI;} return a;}

internal f32
dist(f32 x0, f32 y0, f32 x1, f32 y1, f32 ang){
    //return cos(ang) * (x1 - x0) - sin(ang) * (y1 - y0);
    return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}

struct{
    union{
        struct{
            f32 x;
            f32 y;
        };
        f32 e[2];
    };
} typedef v2;

internal u32
createRGB(u32 r, u32 g, u32 b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

internal u32
getRed(u32 hexValue)
{
    u32 r = ((hexValue >> 16) & 0xFF);  // Extract the RR byte
    
    return r; 
}

internal u32
getGreen(u32 hexValue)
{
    u32 g = ((hexValue >> 8) & 0xFF);   // Extract the GG byte
    
    return g; 
}

internal u32
getBlue(u32 hexValue)
{
    u32 b = ((hexValue) & 0xFF);        // Extract the BB byte
    
    return b; 
}