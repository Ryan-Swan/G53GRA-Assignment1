#include "Q1_Modelling.h"

void setup()
{
    width  = 600;                                   // initialise global window variables
    height = 400;                                   // define in your header: int width, height;
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
    glutInitWindowSize(width, height); 		    // set window size
    glutCreateWindow("My Scene"); 		    // create and show window (named MyScene)
}

void draw()
{
    glClearColor(1.f, 1.f, 1.f, 1.f);                   // set background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
    glMatrixMode(GL_MODELVIEW);                         // set for model and viewing operations
    glLoadIdentity();                                   // reset drawing

    glTranslatef(0.f, 0.f, -100.f);                     // move drawing further back in the scene

    drawCube();						// custom draw function to draw cube from triangles
    drawTetrahedron();					// custom draw function to draw tetrahedron from triangles

    checkGLError();
    glutSwapBuffers();                                  // execute all commands, swap buffers
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);          // Initialise GL environment
    setup();                        // Call additional initialisation commands
    glutDisplayFunc(draw);          // Register scene to render contents of draw() function
    glutReshapeFunc(reshape);
    checkGLError();                 // Check any OpenGL errors in initialisation
    glutMainLoop();                 // Begin rendering sequence
    return 0;
}

void checkGLError()
{
    int e = 0;                      // Error count
    GLenum error = glGetError();    // Get first glError
    while (GL_NO_ERROR != error)    // Loop until no errors found
    {   
        e++;
        printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
        error = glGetError();                                  // Get next glError
    }
}

void reshape(int _width, int _height)
{
    // update global dimension variables
    width  = _width;
    height = _height;
    // calculate new aspect ratio
    GLdouble aspect = static_cast<GLdouble>(width) / static_cast<GLdouble>(height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();     // reset matrix
    gluPerspective(45.0, aspect, 1, 1000);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW); // return matrix mode to modelling and viewing
}

void drawCube()
{
    glColor3f(0.f, 0.f, 0.f);
    float r = 10.f;
   // glBegin(GL_TRIANGLES);
    glBegin(GL_LINE_LOOP);	 
       // Near face
	// Left Triangle
	glVertex3f(-r, -r, r);
        glVertex3f(r, r, r);
        glVertex3f(-r, r, r);
    glEnd();
    glBegin(GL_LINE_LOOP);
        // Right Triangle
	glVertex3f(-r, -r, r);
        glVertex3f(r, -r, r);
        glVertex3f(r, r, r);
    glEnd();
    glBegin(GL_LINE_LOOP);
	// Right face
	// Near Triangle
        glVertex3f(r, -r, r);
        glVertex3f(r, r, -r);
        glVertex3f(r, r, r);
    glEnd();
    glBegin(GL_LINE_LOOP);
	
	// Back Triangle
	glVertex3f(r, -r, r);
        glVertex3f(r, -r, -r);
        glVertex3f(r, r, -r);
    glEnd();
    glBegin(GL_LINE_LOOP);

        // Back face
	// Left (if viewed from face) Triangle (Right if viewed from/through near face)
        glVertex3f(r, -r, -r);
        glVertex3f(-r, -r, -r);
        glVertex3f(r, r, -r);
    glEnd();
    glBegin(GL_LINE_LOOP);
	// Right (if viewed from face) Triangle (Left if viewed from/through near face)
        glVertex3f(-r, -r, -r);
        glVertex3f(-r, r, -r);
        glVertex3f(r, r, -r);
    glEnd();
    glBegin(GL_LINE_LOOP);

        // Left face
	// Back triangle
        glVertex3f(-r, -r, -r);
        glVertex3f(-r, -r, r);
        glVertex3f(-r, r, -r);
    glEnd();
    glBegin(GL_LINE_LOOP);
	// Near triangle
        glVertex3f(-r, -r, r);
        glVertex3f(-r, r, r);
        glVertex3f(-r, r, -r);
    glEnd();
    glBegin(GL_LINE_LOOP);

        // Top face
	// Left triangle
        glVertex3f(-r, r, r);
        glVertex3f(r, r, -r);
        glVertex3f(-r, r, -r);
    glEnd();
    glBegin(GL_LINE_LOOP);
        // Right triangle
        glVertex3f(-r, r, r);
        glVertex3f(r, r, r);
        glVertex3f(r, r, -r);
    glEnd();
    glBegin(GL_LINE_LOOP);

        // Bottom face
	// Right triangle (if viewed from bottom face)
        glVertex3f(r, -r, -r);
	glVertex3f(r, -r, r);
	glVertex3f(-r, -r, r);
    glEnd();
    glBegin(GL_LINE_LOOP);
	// Left triangle (if viewed from bottom face)
        glVertex3f(-r, -r, -r);
        glVertex3f(r, -r, -r);
        glVertex3f(-r, -r, r);
    glEnd();
}

void drawTetrahedron()
{

}
