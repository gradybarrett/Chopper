#ifndef CYLINDER_H
#define CYLINDER_H

#include <QtGlobal>

#ifdef Q_OS_MAC
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

/**
  * A Cylinder using vertex buffer objects.  When drawing with this
  * object, GL_VERTEX_ARRAY and GL_NORMAL_ARRAY must be enabled using
  * glEnableClientState.
  */
class Cylinder
{
private:
    enum Buffer { VERTEX, NORMAL, ELEMENT };
    int slices, stacks, nVerts;
    float base, top, height;
    GLuint elements;
    GLuint buffers[3];
    bool buffersReady;

    // Private copy constructor to disallow copying
    Cylinder( const Cylinder & );
    // Private assignment operator to disallow copying
    Cylinder & operator=(const Cylinder & );

public:

    /**
      * Constructs the vertex and normal data for this Cylinder.  The
      * cylinder is oriented along the z axis.  The base of the cylinder
      * is at z = 0, the top of the cylinder is at z = height.
      *
      * @param base the radius of the base of the cylinder (at z = 0)
      * @param top the radius of the top of the cylinder (at z = height)
      * @param height the height of the cylinder (extent in the z direction)
      * @param slices the number of subdivisions along the z axis.  This must be
      *               greater than or equal to one.
      * @param stacks the number of subdivisions around the z axis.  This must be
                      greater than or equal to three.
      */
    Cylinder(float base, float top, float height, int slices, int stacks);

    /**
      * Draws the cylinder using vertex buffer objects.  This must
      * be called from a current OpenGL context, and GL_VERTEX_ARRAY
      * and GL_NORMAL_ARRAY must be enabled via glEnableClientState.
      */
    void drawGL();

    /**
      * Builds the OpenGL vertex buffer objects needed to draw this
      * torus.  This is automatically called when drawGL is called the
      * first time.  However, if desired, you can call this earlier to
      * initialize the buffers so that they are not initialized when
      * drawing.  It only needs to be called once.  If called multiple
      * times, it does nothing after the first time.
      */
    void buildBuffersGL();
};

#endif // CYLINDER_H
