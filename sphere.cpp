#include "sphere.h"
#include <cmath>
#include <cstdio>
#include <glm/glm.hpp>

Sphere::Sphere(float r, int sl, int st):
        slices(sl), stacks(st), radius(r), buffersReady(false)
{
    if( slices < 3 ) slices = 3;
    if( stacks < 3 ) stacks = 3;

    if( radius < 0 ) radius = 0;

    nVerts = slices * (stacks + 1);
    elements = (slices * 2 * (stacks-1) ) * 3;
}

void Sphere::drawGL() {
    if( ! buffersReady ) buildBuffersGL();

    glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEX]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[NORMAL]);
    glNormalPointer(GL_FLOAT,0,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[ELEMENT]);
    glDrawElements(GL_TRIANGLES,elements,GL_UNSIGNED_INT,0);
}

void Sphere::buildBuffersGL() {

    if( buffersReady ) return;

    // Allocate the temporary arrays for the vertex data
    GLfloat *verts = new GLfloat[nVerts*3];
    GLfloat *norms = new GLfloat[nVerts*3];
    GLuint * el = new GLuint[elements];

    // Generate positions and normals
    GLfloat theta, phi;
    GLfloat thetaFac = (2.0 * M_PI) / slices;
    GLfloat phiFac = M_PI / stacks;
    glm::vec3 p, n;
    GLuint idx = 0;
    for( int i = 0; i < slices; i++ ) {
        theta = i * thetaFac;
        for( int j = 0; j <= stacks; j++ ) {
            phi = j * phiFac;
            p.x = radius * sinf(phi) * cosf(theta);
            p.y = radius * sinf(phi) * sinf(theta);
            p.z = radius * cosf(phi);
            n = glm::normalize(p);
            verts[idx] = p.x; verts[idx+1] = p.y; verts[idx+2] = p.z;
            norms[idx] = n.x; norms[idx+1] = n.y; norms[idx+2] = n.z;
            idx += 3;
        }
    }

    // Generate the element list
    idx = 0;
    for( int i = 0; i < slices; i++ ) {
        GLuint stackStart = i * (stacks + 1);
        GLuint nextStackStart = ((i+1) % slices) * (stacks+1);
        for( int j = 0; j < stacks; j++ ) {
            if( j == 0 ) {
                el[idx] = stackStart;
                el[idx+1] = stackStart + 1;
                el[idx+2] = nextStackStart + 1;
                idx += 3;
            } else if( j == stacks - 1) {
                el[idx] = stackStart + j;
                el[idx+1] = stackStart + j + 1;
                el[idx+2] = nextStackStart + j;
                idx += 3;
            } else {
                el[idx] = stackStart + j;
                el[idx+1] = stackStart + j + 1;
                el[idx+2] = nextStackStart + j + 1;
                el[idx+3] = nextStackStart + j;
                el[idx+4] = stackStart + j;
                el[idx+5] = nextStackStart + j + 1;
                idx += 6;
            }
        }
    }

    // Generate our vertex buffers
    glGenBuffers(3, buffers);

    // Set up buffers with vertex data
    glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL]);
    glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(GLfloat), norms, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(GLuint), el, GL_STATIC_DRAW);

    // Delete our vertex data, we don't need it anymore
    delete [] verts;
    delete [] norms;
    delete [] el;

    buffersReady = true;
}
