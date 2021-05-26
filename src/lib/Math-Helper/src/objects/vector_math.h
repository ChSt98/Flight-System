#ifndef _VECTOR_MATH_H_
#define _VECTOR_MATH_H_


#include "math.h"


#ifdef Arduino_h
#include "WString.h"
#endif


#ifndef PI
#define PI 3.1415926541f
#endif

#ifndef DEGREES
#define DEGREES (PI/180.0f)
#endif


template <typename T = float>
class Vector {
    public:
    
        T x;
        T y;
        T z;

        Vector<T>() {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }

        /**
         * This constructor sets all components to n.
         */
        Vector<T>(const T &n) {
            x = n;
            y = n;
            z = n;
        }

        Vector<T>(const T &nx, const T &ny, const T &nz) {
            x = nx;
            y = ny;
            z = nz;
        }

        //Vector<T>(const Quaternion &quaternion);

        /**
         * Calculates the magnitude of the vector.
         *
         * @return magnitude of the vector.
         */
        inline T magnitude() const {

            T m = x*x + y*y + z*z;

            m = sqrt(m);
            
            if (m == m) { // NAN check
                return m;
            }
            return 0.0f;
        }

        /**
         * Copies the vector.
         *
         * @return copy of the vector.
         */
        inline Vector<T> copy() const {
            return Vector<T>(x, y, z);
        }

        /**
         * Normalizes the Vector.
         *
         * @return copy of the normalized vector.
         */
        inline Vector<T>& normalize() {

            T mag = magnitude();

            if (mag != 0.0f) {
                x /= mag;
                y /= mag;
                z /= mag;
            } else {
                x = 0.0f;
                y = 0.0f;
                z = 0.0f;
            }

            return *this;

        }

        /**
         * Checks if vector<T> is zero vector.
         *
         * @return true if vecter is zero vector.
         */
        inline bool isZeroVector() const {

            return magnitude() == 0.0f;

        }

        /**
         * Multiplies the vectors components to this scheme:
         * Vector<T>(x*x, y*y, z*z)
         *
         * @param vec vector<T> to multiply with
         * @return vector.
         */
        inline Vector<T> compWiseMulti(const Vector<T> &vec) const {
            return Vector<T>(x*vec.x, y*vec.y, z*vec.z);
        }

        /**
         * Adds the components of the vectors.
         *
         * @param values none.
         * @return copy of the vector.
         */
        inline Vector<T> operator + (const Vector<T> &b) const {
            return Vector<T>(x + b.x, y + b.y, z + b.z);
        }

        /**
         * Subtracts the components of the vectors.
         *
         * @param values none.
         * @return copy of the vector.
         */
        inline Vector<T> operator - (const Vector<T> &b) const {
            return Vector<T>(x - b.x, y - b.y, z - b.z);
        }

        /**
         * Negates the components of the vectors.
         *
         * @param values none.
         * @return copy of the vector.
         */
        inline Vector<T> operator - (void) const {
            return Vector<T>(-x, -y, -z);
        }

        /**
         * Scales the vector.
         *
         * @param c Value to scale with.
         * @return copy of scaled vector.
         */
        inline Vector<T> operator * (const auto &c) const {
            return Vector<T>(x*c, y*c, z*c);
        }

        /**
         * Divides the components of the vectors.
         *
         * @param values none.
         * @return copy of the vector.
         */
        inline Vector<T> operator / (const auto &c) const {
            return Vector<T>(x/c, y/c, z/c);
        }

        /**
         * Compound scaling.
         *
         * @param values none.
         * @return nothing.
         */
        inline void operator *= (const auto &c) {
            x *= c;
            y *= c;
            z *= c;
        }

        /**
         * Compound addition.
         *
         * @param values none.
         * @return nothing.
         */
        inline void operator += (const Vector<T> &b) {
            x += b.x;
            y += b.y;
            z += b.z;
        }

        /**
         * Vector<T> component wise multiplication.
         *
         * @param values none.
         * @return multiplication result in T.
         */
        inline Vector<T> operator * (const Vector<T> &b) const {
            return Vector<T>(x*b.x, y*b.y, z*b.z);
        }

        /**
         * Vector<T> component wise multiplication.
         *
         * @param values none.
         * @return multiplication result in T.
         */
        inline Vector<T> operator / (const Vector<T> &b) const {
            return Vector<T>(x/b.x, y/b.y, z/b.z);
        }

        /**
         * Vector<T> multiplication.
         * 
         * x1*x2 + y1*y2 + z1*z2
         *
         * @param values none.
         * @return multiplication result in T.
         */
        inline T operator ^ (const Vector<T> &b) const {
            return x*b.x + y*b.y + z*b.z;
        }

        /**
         * Vector<T> equals.
         * True is all components are equal
         *
         * @param values none.
         * @return bool.
         */
        inline bool operator == (const Vector<T> &b) const {
            return x==b.x && y==b.y && z==b.z;
        }

        /**
         * Vector<T> not equals.
         * true if any component not equal
         *
         * @param values none.
         * @return bool.
         */
        inline bool operator != (const Vector<T> &b) const {
            return !(x==b.x && y==b.y && z==b.z);
        }

        /**
         * @return bool.
         */
        inline bool operator < (const Vector<T> &b) const {
            return this->magnitude() < b.magnitude();
        }

        /**
         * @return bool.
         */
        inline bool operator > (const Vector<T> &b) const {
            return this->magnitude() > b.magnitude();
        }

        /**
         * Computes cross multiplication of 2 vectors.
         * 
         *
         * @param values none.
         * @return Vector.
         */
        inline Vector<T> cross(const Vector<T> &b) const {
            return Vector<T>(
                y*b.z-z*b.y,
                z*b.x-x*b.z,
                x*b.y-y*b.x
            );
        } 

        /**
         * Computes angle between 2 vectors.
         * 
         *
         * @param values none.
         * @return angle(T) in radians.
         */
        inline T getAngleTo(const Vector<T> &b) const {
            
            T ca = (*this)^b/(magnitude()*b.magnitude());

            return acos(ca);

        }


        /**
         * Computes the projection onto another vector.
         * 
         *
         * @param values none.
         * @return Vector.
         */
        inline Vector<T> getProjectionOn(const Vector<T> &b) const {

            b.normalize();

            return b*(*this*b);

        }

        #ifdef Arduino_h
        /**
         * Returns a String containing components.
         * Form:
         * x: ..., y: ..., z:...
         * Where ... is the value.
         * Default digits is 2.
         * 
         *
         * @param values digits.
         * @return String.
         */
        inline String toString(const uint8_t &digits = 2) const {
            return "x: " + String(x, digits) + ", y: " + String(y, digits) + ", z: " + String(z, digits);  
        }
        #endif


};


//Is a vector<T> with a z component of -9.81.
#define GRAVITY_VECTOR Vector<>(0,0,-9.81)

template <typename T = float>
inline Vector<T> sqrt(Vector<T> a)  {
    return Vector<T>(sqrt(a.x), sqrt(a.y), sqrt(a.z));
}

template <typename T = float>
inline Vector<T> operator / (const float &a, const Vector<T> &b)  {
    return Vector<T>(a/b.x, a/b.y, a/b.z);
}


#endif