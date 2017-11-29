//
// Created by Mike Smith on 16/10/2017.
//

#ifndef LEARNING_OPENGL_BUFFER_H
#define LEARNING_OPENGL_BUFFER_H

class Buffer
{
private:
    unsigned int _id;
    unsigned int _type;
    unsigned int _dataType;
    unsigned int _ptrDiff;

public:
    explicit Buffer(unsigned int type, unsigned int dataType, unsigned int ptrDiff);
    virtual ~Buffer();
    unsigned int id() const;
    unsigned int type() const;
    unsigned int dataType() const;
    unsigned int ptrDiff() const;
    void bind() const;
    void setData(const void *data, unsigned int size, unsigned int usage);
    void setSubData(unsigned int offset, unsigned int size, const void *data);
};

#endif  // LEARNING_OPENGL_BUFFER_H
