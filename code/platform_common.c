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

struct
{
    int type;
    int texture;
    b32 exists;
    f32 x, y, z;
    int size;
}typedef sprite; sprite sp[420]; 

#define Pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define Released(b) (!input->buttons[b].isDown && input->buttons[b].changed)
#define IsDown(b) (input->buttons[b].isDown)