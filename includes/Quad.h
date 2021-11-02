class Quad
{
private:
    float x, y, z, scale;
    bool visible;
public:
    bool isVisible();
    float getPosX();
    float getPosY();
    float getPosZ();
    float getScale();
    void setPosX(float x);
    void setPosY(float y);
    void setPosZ(float z);
    void setScale(float scale);
    void draw(float r, float g, float b);
    Quad(float x, float y, float z, float scale);
    ~Quad();
};
