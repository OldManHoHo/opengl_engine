

class TGLInputHandler
{
public:
    std::map <char, bool> key_states;
    double mouse_x, mouse_y;
    TGLInputHandler();
    void tick(double time_delta);
};