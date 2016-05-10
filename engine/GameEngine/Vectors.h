//
//  Vectors.hpp
//  GameEngine
//
//  Created by David Lively on 2/10/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef VECTORS_H
#define VECTORS_H

#include <cmath>

struct Vector2
{
    float X;
    float Y;
    
    Vector2() : X(0), Y(0)
    {
    }
    
    Vector2(float x, float y) : X(x), Y(y)
    {
        
    }
    
};

struct Vector3 : public Vector2
{
    float Z;
    
    Vector3() : Vector2(), Z(0)
    {
        
    }
    
    Vector3(float x, float y, float z) : Vector2(x,y), Z(z)
    {
        
    }
    
    template<typename T>
    inline Vector3 operator* (const T& multiplier) const
    {
        return Vector3(X * multiplier, Y * multiplier, Z * multiplier);
    }
    
    inline Vector3& operator*=(const float& rval)
    {
        X *= rval;
        Y *= rval;
        Z *= rval;
        
        return *this;
    }
    
    inline Vector3& operator*=(const Vector3& rval)
    {
        X *= rval.X;
        Y *= rval.Y;
        Z *= rval.Z;
        
        return *this;
    }
    
    template<typename T>
    inline Vector3& operator+=(const T& rval)
    {
        X += rval.X;
        Y += rval.Y;
        Z += rval.Z;
        
        return *this;
    }
    
    inline Vector3& normalize()
    {
        float length = sqrt(this->dot(*this));
        X /= length;
        Y /= length;
        Z /= length;
        
        return *this;
    }
    
    inline float magnitude()
    {
        return sqrt(dot(*this));
    }

    template<typename T>
    inline Vector3& operator-=(const T& rval)
    {
        X -= rval.X;
        Y -= rval.Y;
        Z -= rval.Z;
        
        return *this;
    }
    
    template<typename T>
    inline Vector3 cross(const T& rval)
    {
        Vector3 v;
        v.X = Y*rval.Z - Z*rval.Y;
        v.Y = Z*rval.X - X*rval.Z;
        v.Z = X*rval.Y - Y*rval.X;
        
        return v;
    }
    
    inline float dot(const Vector3& rval)
    {
        return (X * rval.X) + (Y * rval.Y) + (Z * rval.Z);
    }
    
    template<typename T>
    inline Vector3& operator=(const T& rval)
    {
        X = rval;
        Y = rval;
        Z = rval;
        
        return *this;
    }
    
    template<typename T>
    float distance(const T& other)
    {
        float pythagorean =
        pow((X - other.X),2) +
        pow((Y - other.Y),2) +
        pow((Z - other.Z),2);
        
        return sqrt(pythagorean);
    }
    
    inline Vector3 operator- (Vector3 other) const
    {
        return Vector3(X - other.X, Y - other.Y, Z - other.Z);
    }
    
    inline Vector3 operator+ (Vector3 other) const
    {
        return Vector3(X + other.X, Y + other.Y, Z + other.Z);
    }
};

struct Vector4 : public Vector3
{
    float W;
    
    Vector4() : Vector3(), W(0)
    {
        
    }
    
    Vector4(float x, float y, float z, float w) : Vector3(x,y,z)
    {
        
    }
    
    inline Vector4 operator+= (Vector4 other) const
    {
        return Vector4(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
    }
};


#endif /* Vectors_hpp */
