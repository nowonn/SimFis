struct
{
    b32 isDown;
    b32 changed;
} typedef Button;

enum
{
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_GRAPH,
    BUTTON_ESCAPE,
    BUTTON_PAUSE,
    BUTTON_COUNT,
};

typedef struct
{
    int mouseX;
    int mouseY;
    Button buttons[BUTTON_COUNT];
} Input;

typedef struct {
    float position[2];
    float velocity[2];
    float acceleration[2];
    float mass;
    float width;
    float height;
    u32 color;
} Object;

typedef struct {
    float kel;
    float deformation;
    float x0;
    int segments;
    float startX;
} Mola;

enum GraphType {
    ACCELERATION, VELOCITY, POSITION, ALL
};

#define Pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define Released(b) (!input->buttons[b].isDown && input->buttons[b].changed)
#define IsDown(b) (input->buttons[b].isDown)