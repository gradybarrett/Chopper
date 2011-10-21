#include "cylinder.h"
#include <cmath>
#include <glm/glm.hpp>

Cylinder::Cylinder(float b, float t, float h, int sl, int st):
        slices(sl), stacks(st), base(b), top(t), height(h),
        buffersReady(false)
{
    buffers[VERTEX] = 0;
    buffers[NORMAL] = 0;
    buffers[ELEMENT] = 0;

    if( slices < 3 ) slices = 3;
    if( stacks < 1 ) stacks = 1;

    if( base < 0 ) base = 0;
    if( top < 0 ) top = 0;
    if(height < 0) height = 0;

    nVerts = slices * (stacks + 1);
    elements = (slices * stacks) * 6;
}

void Cylinder::drawGL() {
    if( !buffersReady ) buildBuffersGL();

    glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEX]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[NORMAL]);
    glNormalPointer(GL_FLOAT,0,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[ELEMENT]);
    glDrawElements(GL_TRIANGLES,elements,GL_UNSIGNED_INT,0);
}

void Cylinder::buildBuffersGL() {

    // If buffers have already been set up, do nothing
    if( buffersReady ) return;

    // Allocate temporary space for the vertex data
    GLfloat * verts;
    GLfloat * normals;
    GLuint * el;
    verts = new GLfloat[ nVerts * 3 ];
    normals = new GLfloat[ nVerts * 3 ];
    el = new GLuint[ elements ];

    glm::vec3 p, n;

    // Generate the points
    GLuint vIdx = 0;
    float sliceFac = 2.0 * M_PI / slices;
    float stackFac = height / stacks;
    float angle = 0.0f, alpha = 0.0f, r = 0.0f;
    float normZ = (base - top) / height;
    for( int i = 0; i <= stacks ; i++ ) {
        p.z = i * stackFac;
        alpha = p.z / height;
        r = (1 - alpha) * base + alpha * top;
        for( int j = 0; j < slices; j++ ) {
            angle = sliceFac * j;
            p.x = cosf(angle);
            p.y = sinf(angle);
            n = glm::vec3(p.x, p.y, normZ);
            n = glm::normalize(n);
            p.x = p.x * r;
            p.y = p.y * r;
            verts[vIdx] = p.x;
            verts[vIdx+1] = p.y;
            verts[vIdx+2] = p.z;
            normals[vIdx] = n.x;
            normals[vIdx+1] = n.y;
            normals[vIdx+2] = n.z;
            vIdx += 3;
        }
    }

    // Generate the element indexes for triangles
    GLuint elIdx = 0, stackStart, nextStackStart;
    for( int i = 0; i < stacks; i++ ) {
        stackStart = i * slices;
        nextStackStart = (i+1) * slices;
        for( int j = 0; j < slices; j++ ) {
            // Triangle one
            el[elIdx] = stackStart + j;
            el[elIdx+1] = nextStackStart + j;
            el[elIdx+2] = nextStackStart + ((j+1) % slices);
            // Triangle 2
            el[elIdx+3] = stackStart + j;
            el[elIdx+4] = nextStackStart + ((j+1) % slices);
            el[elIdx+5] = stackStart + ((j+1) % slices);
            elIdx += 6;
        }
    }

    // Create the buffer objects
    glGenBuffers(3, buffers);

    // Load the data into buffer objects
    glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX]);
    glBufferData(GL_ARRAY_BUFFER,nVerts * 3 * sizeof(GLfloat),verts,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL]);
    glBufferData(GL_ARRAY_BUFFER,nVerts * 3 * sizeof(GLfloat),normals,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,elements*sizeof(GLuint),el,GL_STATIC_DRAW);

    // Delete the local arrays, we don't need them anymore.
    delete [] verts;
    delete [] normals;
    delete [] el;

    buffersReady = true;
}
