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
    BUTTON_INTERACT,
    BUTTON_ESCAPE,
    BUTTON_SPRINT,
    BUTTON_COUNT,
};

struct
{
    int mouseX;
    int mouseY;
    Button buttons[BUTTON_COUNT];
} typedef Input;

typedef struct {
    float position[2];
    float speed[2];
    float acceleration[2];
    float mass;
    float width;
    float height;
    u32 color;
} Objeto;

typedef struct {
    float kel;
    float deformation;
    float x0;
    int segments;
    float startX;
} Mola;

#define Pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define Released(b) (!input->buttons[b].isDown && input->buttons[b].changed)
#define IsDown(b) (input->buttons[b].isDown)