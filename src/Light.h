#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

class Light
{
private:
public:
    virtual int getType() = 0;
    virtual ~Light() {}
};



#endif