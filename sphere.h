#ifndef SPHERE_H
#define SPHERE_H

#include <QtGlobal>

#ifdef Q_OS_MAC
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

class Sphere
{
private:
    enum Buffer { VERTEX, NORMAL, ELEMENT };
    int slices, stacks, nVerts;
    float radius;
    GLuint elements;
    GLuint buffers[3];
    bool buffersReady;

    // Private copy constructor to disallow copying
    Sphere( const Sphere & );
    // Private assignment operator to disallow copying
    Sphere & operator=(const Sphere & );

public:

    /**
      * Constructs the vertex and normal data for this Sphere.  The
      * sphere is oriented along the z axis.  The poles are at z = radius
      * and z = -radius.
      *
      * @param radius the radius of the sphere
      * @param slices the number of subdivisions along the z axis (like lines of
      *               longitude).  This must be greater than or equal to three.
      * @param stacks the number of subdivisions around the z axis (like lines of
      *               latitude).  This must be greater than or equal to three.
      */
    Sphere(float radius, int slices, int stacks);

    /**
      * Draws the Sphere using vertex buffer objects.  This must
      * be called from a current OpenGL context, and GL_VERTEX_ARRAY
      * and GL_NORMAL_ARRAY must be enabled via glEnableClientState.
      */
    void drawGL();

    /**
      * Builds the OpenGL vertex buffer objects needed to draw this
      * Sphere.  This is automatically called when drawGL is called the
      * first time.  However, if desired, you can call this earlier to
      * initialize the buffers so that they are not initialized when
      * drawing.  It only needs to be called once.  If called multiple
      * times, it does nothing after the first time.
      */
    void buildBuffersGL();
};

#endif // SPHERE_H
