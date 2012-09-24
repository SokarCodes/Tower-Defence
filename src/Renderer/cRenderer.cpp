/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include "cRenderer.h"
#include "../common.h"

#include "../GameLogic/cGameEntity.h"
#include "../GameLogic/entityEnums.h"

float camX, camY, camZ;
float rotX, rotY, rotZ;
namespace renderer {

bool cRenderer::instanceFlag_ = false;
cRenderer* cRenderer::thisPointer_ = NULL;
gamelogic::cMapper* cRenderer::mapper_ = gamelogic::cMapper::getInstance();

// Shader sources
const char* vertexSource =
        "#version 150\n"
        "in vec2 position;"
        "in vec3 color;"
        "out vec3 Color;"
        "void main() {"
        "	Color = color;"
        "	gl_Position = vec4( position, 0.0, 1.0 );"
        "}";
const char* fragmentSource =
        "#version 150\n"
        "in vec3 Color;"
        "out vec4 outColor;"
        "void main() {"
        "	outColor = vec4( Color, 1.0 );"
        "}";

cRenderer* cRenderer::getInstance()
{
    if (instanceFlag_)
    {
        return thisPointer_;
    }
    else
    {
        thisPointer_ = new cRenderer();
        instanceFlag_ = true;
        return thisPointer_;
    }
}

cRenderer::cRenderer()
{
    try
    {
        window_ = new sf::Window(sf::VideoMode(800,600,32), "Tower-Defence experimental build!", sf::Style::Close);
    }
    catch (std::bad_alloc&)
    {
        window_ = NULL;
        std::cout << "Renderwindow creation failure!\n";
        return;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers( 1, &vbo );

    float vertices[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
        0.5f,  0.5f, 0.0f, 0.6f, 0.0f, // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 0.7f, 1.0f  // Bottom-left
    };

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    // Create an element array
    GLuint ebo;
    glGenBuffers( 1, &ebo );

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexSource, NULL );
    glCompileShader( vertexShader );

    GLint status;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &status );

    // Check vertex shader status if compiled correctly
    if (status == GL_TRUE)
        std::cout << "Vertex shader compile: OK!\n";
    else
    {
        char buffer[513];
        glGetShaderInfoLog( vertexShader, 512, NULL, buffer );
        std::cout << "Vertex shader compile: FAILED!\n";
        std::cout << "ShaderInfoLog: " << buffer << "\n";
    }

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentSource, NULL );
    glCompileShader( fragmentShader );

    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &status );
    if (status == GL_TRUE)
        std::cout << "Fragment shader compile: OK!\n";
    else
    {
        char buffer[513];
        glGetShaderInfoLog( vertexShader, 512, NULL, buffer );
        std::cout << "Fragment shader compile: FAILED!\n";
        std::cout << "ShaderInfoLog: " << buffer << "\n";
    }

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glBindFragDataLocation( shaderProgram, 0, "outColor" );
    glLinkProgram( shaderProgram );
    glUseProgram( shaderProgram );

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation( shaderProgram, "position" );
    glEnableVertexAttribArray( posAttrib );
    glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), 0 );

    GLint colAttrib = glGetAttribLocation( shaderProgram, "color" );
    glEnableVertexAttribArray( colAttrib );
    glVertexAttribPointer( colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void*)( 2 * sizeof( float ) ) );

    //    // Set color and depth clear value
    //    glClearDepth(1.f);
    //    glClearColor(0.f, 0.f, 0.f, 0.f);

    //    // Enable Z-buffer read and write
    //    glEnable(GL_DEPTH_TEST);
    //    glDepthMask(GL_TRUE);

    //    // Setup a perspective projection
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    gluPerspective(90.f, 800/600, 1.f, 2000.f);
    //    glViewport (0, 0, (GLsizei)800, (GLsizei)600);
    //    window_->SetActive();
    //    camY = 300;
    //    camX = -400;
    //    camZ = -400.f;
    //    rotX = 0;
    //    rotY = 0;
    //    rotZ = 0;
}

void cRenderer::update(float frametime)
{
    // Clear the screen to black
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    // Draw a rectangle from the 2 triangles using 6 indices
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

    // Swap buffers
    window_->Display();

    /*    //window_->PreserveOpenGLStates(true);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(camX, camY, camZ);
    glRotatef(rotX, 1.0, 0.f, 0.f);
    glRotatef(rotY, 0.f, 1.f, 0.f);
    glRotatef(rotZ, 0.f, 0.f, 1.f);

    glBegin(GL_QUADS);
//    glVertex3f(-350.f, -350.f, -1.f);
//    glVertex3f(-350.f,  350.f, -1.f);
//    glVertex3f( 350.f,  350.f, -1.f);
//    glVertex3f( 350.f, -350.f, -1.f);

//    glVertex3f(-50.f, -50.f, 50.f);
//    glVertex3f(-50.f,  50.f, 50.f);
//    glVertex3f( 50.f,  50.f, 50.f);
//    glVertex3f( 50.f, -50.f, 50.f);

//    glVertex3f(-50.f, -50.f, -50.f);
//    glVertex3f(-50.f,  50.f, -50.f);
//    glVertex3f(-50.f,  50.f,  50.f);
//    glVertex3f(-50.f, -50.f,  50.f);

//    glVertex3f(50.f, -50.f, -50.f);
//    glVertex3f(50.f,  50.f, -50.f);
//    glVertex3f(50.f,  50.f,  50.f);
//    glVertex3f(50.f, -50.f,  50.f);

//    glVertex3f(-50.f, http://www.youtube.com/watch?v=lbqxkS2ssUI&feature=related#t=5m05s-50.f,  50.f);
//    glVertex3f(-50.f, -50.f, -50.f);
//    glVertex3f( 50.f, -50.f, -50.f);
//    glVertex3f( 50.f, -50.f,  50.f);

//    glVertex3f(-50.f, 50.f,  50.f);
//    glVertex3f(-50.f, 50.f, -50.f);
//    glVertex3f( 50.f, 50.f, -50.f);
//    glVertex3f( 50.f, 50.f,  50.f);
    glEnd();

    std::vector<gamelogic::cGameEntity*> towerList = mapper_->getTowerEntities();
    std::vector<gamelogic::cGameEntity*>::iterator iter = towerList.begin();

    for (;iter < towerList.end(); iter++)
    {
        sf::Vector3f position = (*iter)->getPosition();
        glPointSize(2);
        glColor3f(0,0.8,0);
        glBegin(GL_POINTS);
        glVertex3f(position.x, position.y, position.z);
        glEnd();
        //window_->Draw(*towerShape_);
    }

    std::vector<gamelogic::cGameEntity*> enemyList = mapper_->getEnemyEntities();
    iter = enemyList.begin();
    for (;iter < enemyList.end(); iter++)
    {
        sf::Vector3f position = (*iter)->getPosition();
        glColor3f(0.9,0,0.8);
        glBegin(GL_POINTS);
        glVertex3f(position.x, position.y, position.z);
        glEnd();
        //window_->Draw(*enemyShape_);
    }

    std::vector<gamelogic::cGameEntity*> projectileList = mapper_->getProjectileEntities();
    iter = projectileList.begin();
    for (;iter < projectileList.end(); iter++)
    {
        sf::Vector3f position = (*iter)->getPosition();
        glColor3f(0.9,0.9,0.9);
        glBegin(GL_POINTS);
        glVertex3f(position.x, position.y, position.z);
        glEnd();
        //window_->Draw(*projectile_);
    }
*/
}
sf::Window* cRenderer::getRenderwindow()
{
    return window_;
}

// Not implemented properly.
void cRenderer::drawFPS(float spentTime)
{
    std::ostringstream frametimer;
    frametimer << std::fixed << std::setprecision(1);
    frametimer << spentTime;
}

}
