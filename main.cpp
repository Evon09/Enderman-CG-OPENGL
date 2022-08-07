#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>

#include "SOIL/SOIL.h"

GLuint      texture[4];
GLuint  indiceTextura=0;
int olho = 1;

/////////   VARI�VEIS GLOBAIS PARA OS ANGULOS////////////
float ang = 0;
float ang2 = 0;
float ang3 = 0;

float chaoZ = -500;
float chaoAng = 0;


void display();

int LoadGLTextures() // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture ( "D:\\Jair\\Documents\\UTFPR\\Ender\\img\\face1.png",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texture[1] = SOIL_load_OGL_texture ( "D:\\Jair\\Documents\\UTFPR\\Ender\\img\\face2.png",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texture[2] = SOIL_load_OGL_texture ( "D:\\Jair\\Documents\\UTFPR\\Ender\\img\\face3.png",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texture[3] = SOIL_load_OGL_texture ( "D:\\Jair\\Documents\\UTFPR\\Ender\\img\\face3.png",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texture[4] = SOIL_load_OGL_texture ( "D:\\Jair\\Documents\\UTFPR\\Ender\\img\\grama.png",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);

    if(texture[0] == 0 ){
        return false;
    }
    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glEnable(GL_TEXTURE_2D);			    // Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);			    // Enable Smooth Shading
	glClearColor(0.135f, 0.379f, 0.591f, 1.0f);   // Black Background
	glClearDepth(1.0f);						// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);				// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);					// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    return true; // Return Success
}


class Osso
{
public:
    Osso(float a, float l): largura(l), altura(a), conexcao(0) {}
    void desenha();

    void setConexcao(Osso *osso, float ang)
    {
        conexcao = osso, angulo = ang;
    }

    void setAngulo(float ang)
    {
        angulo = ang;
    }
    float getAngulo()
    {
        return angulo;
    }

protected:
    float largura;
    float altura;

    float angulo;
    Osso *conexcao;
};

void Osso::desenha()
{
    glPushMatrix();  //salva o contexto(1)

    glTranslatef (0.0, altura/2.0, 0.0); //vai para o meio do osso

    glPushMatrix();   //salva o contexto(2)
    glScalef (2, altura, 2);  //escala para o tamanho do osso

    glutSolidCube (1);    //desenha o osso
    glPopMatrix();    //restaura o contexto(2)

    glTranslatef (0.0, altura/2.0, 0.0); // vai para a ponta do osso

    //glutSolidSphere(0.85*largura,8,8);        //desenha a bolinha

    if (conexcao)
    {
        glRotatef(angulo, 1.0, 0.0, 0.0); //rotaciona para o angulo da conexcao
        conexcao->desenha();              //desenha recursivamente
    }

    glPopMatrix();  //restaura o contexto(1)
};
////////////////////////////////////////////////////////////
class Membro
{
public:
    Membro(float comprimento, float largura);
    void desenha()
    {
        a.desenha();
    }
    void setCurvatura(float curvatura);
    void setCurvaturaA(float curvatura);
    void setCurvaturaB(float curvatura);
    float getCurvatura()
    {
        return a.getAngulo()*100/90;
    }
    float getCurvaturaB()
    {
        return b.getAngulo()*100/90;
    }

protected:
    Osso a,b,c;
};

Membro::Membro(float comprimento, float largura)
    : a(comprimento*0.4,largura), b(comprimento*0.35,largura), c(comprimento*0.25,largura)
{
    a.setConexcao(&b,0.0);
    b.setConexcao(&c,0.0);
}

void Membro::setCurvaturaA(float curvatura)
{
    a.setAngulo(curvatura*-0.9);
}

void Membro::setCurvaturaB(float curvatura)
{
    b.setAngulo(curvatura*-0.9);
}

void Membro::setCurvatura(float curvatura)
{
    a.setAngulo(curvatura*-0.9);
    b.setAngulo(curvatura*-0.9);
}

class Cabeca
{
public:
    Cabeca(float comprimento, float largura);
    void desenha()
    {
        a.desenha();
    }
    void setCurvatura(float curvatura);
    float getCurvatura()
    {
        return a.getAngulo()*100/90;
    }

protected:
    Osso a;
};

Cabeca::Cabeca(float comprimento, float largura)
    : a(1,1)
{
    //a.setConexcao(&b,0.0);
}

void Cabeca::setCurvatura(float curvatura)
{
    //a.setAngulo(curvatura*0.9);
}

void Chao()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture[4] );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTranslatef(-500, -50, chaoZ);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex3f(0, 0, 0);
        glTexCoord2f(0.0f, 800.0f);glVertex3f(0, 0, 10000);
        glTexCoord2f(800.0f, 800.0f);glVertex3f(10000, 0, 10000);
        glTexCoord2f(800.0f, 0.0f);glVertex3f(10000, 0, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


class Corpo
{
public:
    Corpo(float grossura);
    void desenha();
    void setCurvatura(int membro,float curv);
    void setCurvaturaA(int membro,float curv);
    void setCurvaturaB(int membro,float curv);
    float getCurvatura(int membro)
    {
        return curvatura[membro];
    }
    void abrir(bool tudoJunto = false);
    void fechar(bool tudoJunto = false);
    Membro getDedo(int membro)
    {
        switch (membro)
        {
        case 0:
            return mindinho;
            break;
        case 1:
            return anelar;
            break;
        case 2:
            return maior;
            break;
        case 3:
            return indicador;
            break;
        }
    }
    void tchau();
    void andar();
    void danca();

    void home();

protected:
    float grossura;

    Membro mindinho;
    Membro anelar;
    Membro maior;
    Membro indicador;
    Cabeca cabeca;
    float curvatura[5];
    float curvaturaZ[5];
};

Corpo::Corpo(float gros)
    : grossura(gros),
      mindinho(30,2),
      anelar(30,2),
      maior(30,2),
     indicador(30,2),
      cabeca(8,8)
{
    for (int i=0; i<5; i++)
    {
        curvatura[i] = 0;
        curvaturaZ[i] = 0;
    }
}

void Corpo::desenha()
{
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(0.0,1*grossura,0.0);
    glPushMatrix();


    //pe esqerdo
    glTranslatef(-2.5,-7.25,0);
    glRotatef(-180,0.0,0.0,1.0);
    //glRotatef(-180,0.0,1.0,0.0);
    //glutSolidSphere(grossura,8,8);
    glRotatef(curvatura[0]*0.9,1.0,0.0,0.0);
    glRotatef(curvaturaZ[0]*0.9,0.0,0.0,1.0);
    mindinho.desenha();

    //pe direito
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.5,-7.25,0.0);
    glRotatef(-180,0.0,0.0,1.0);
    //glRotatef(-180,0.0,1.0,0.0);
    //glutSolidSphere(grossura,8,8);
    glRotatef(curvatura[1]*0.9,1.0,0.0,0.0);
    glRotatef(curvaturaZ[1]*0.9,0.0,0.0,1.0);
    anelar.desenha();

    //braco
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-05,5,0.0);
    glRotatef(180,0.0,0.0,1.0);
    glRotatef(90,.0,1.0,0.0);
    //glutSolidSphere(grossura,8,8);
    glRotatef(curvatura[2]*0.9,1.0,0.0,0.0);
    glRotatef(curvaturaZ[2]*0.9,0.0,0.0,1.0);
    maior.desenha();

    //braco
    glPopMatrix();
    glPushMatrix();
    glTranslatef(05,5,0.0);
    glRotatef(-180,0.0,0.0,1.0);
    glRotatef(-90,.0,1.0,0.0);
    //glutSolidSpere(grossura,8,8);
    glRotatef(curvatura[3]*0.9,1.0,0.0,0.0);
    glRotatef(curvaturaZ[3]*0.9,0.0,0.0,1.0);

    indicador.desenha();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0,5,0);

    //glRotatef(-80,0.0,0.0,1.0);
    //glRotatef(-20,0.0,1.0,0.0);
    glRotatef(curvatura[4]*0.5,1.0,0.0,0.0);
    glRotatef(curvaturaZ[4]*0.9,0.0,0.0,1.0);
    glScalef(4,8,4);
    //glutSolidSphere(grossura,8,8);



    cabeca.desenha();

    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture[olho] );
    //glColor3f(0.22f, 0.22f, 0.22f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0,1.0);glVertex3f(-1.0,1,1.001);
        glTexCoord2f(0.0,1.0);glVertex3f(1,1,1.001);
        glTexCoord2f(0.0,0.0);glVertex3f(1,0,1.001);
        glTexCoord2f(1.0,0.0);glVertex3f(-1,0,1.001);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0.22f, 0.22f, 0.22f);
    glColor3f(0,0,0);
    glTranslatef(-0,0,0.0);
    glScalef(8,12,4);
    glutSolidCube(1.0);
    glPopMatrix();
}

void Corpo::setCurvatura(int membro,float curv)
{
    curvatura[membro] = curv;

    switch(membro)
    {
    case 0:
        mindinho.setCurvatura(curv);
        break;
    case 1:
        anelar.setCurvatura(curv);
        break;
    case 2:
        maior.setCurvatura(curv);
        break;
    case 3:
        indicador.setCurvatura(curv);
        break;
    case 4:
        cabeca.setCurvatura(curv);
        break;
    }
}

void Corpo::setCurvaturaA(int membro,float curv)
{
    curvatura[membro] = curv;

    switch(membro)
    {
    case 0:
        mindinho.setCurvaturaA(curv);
        break;
    case 1:
        anelar.setCurvaturaA(curv);
        break;
    case 2:
        maior.setCurvaturaA(curv);
        break;
    case 3:
        indicador.setCurvaturaA(curv);
        break;
    case 4:
        cabeca.setCurvatura(curv);
        break;
    }
}

void Corpo::setCurvaturaB(int membro,float curv)
{
    curvatura[membro] = curv;

    switch(membro)
    {
    case 0:
        mindinho.setCurvaturaB(curv);
        break;
    case 1:
        anelar.setCurvaturaB(curv);
        break;
    case 2:
        maior.setCurvaturaB(curv);
        break;
    case 3:
        indicador.setCurvaturaB(curv);
        break;
    case 4:
        cabeca.setCurvatura(curv);
        break;
    }
}

void Corpo::abrir(bool tudoJunto)
{
    if (tudoJunto)
        for (int j=getCurvatura(1);j>=0;j-=5)
        {
            for (int i=4;i>=0;i--)
            {
                setCurvatura(i,j);

            }
            display();
        }
    else
        for (int i=4;i>=0;i--)
        {
            for (int j=getCurvatura(i);j>=0;j-=5)
            {
                setCurvatura(i,j);
                display();
            }
        }

}

void Corpo::fechar(bool tudoJunto)
{
    if (tudoJunto)
    for (int j=getCurvatura(1);j<=100;j+=5)
    {
        for (int i=0;i<5;i++)
        {
            setCurvatura(i,j);
        }
        display();
    }
    else
    for (int i=0;i<5;i++)
    {
        for (int j=getCurvatura(i);j<=100;j+=5)
        {
            setCurvatura(i,j);
            display();
        }
    }
}

void Corpo::andar()
{
    abrir(true);
    //printf("%d",getCurvatura(1));

    for(int cont=0; cont<=10;cont++){

         for (int j=getCurvatura(1); j<=30;j+=5)
        {

            setCurvaturaA(1,j);
            display();
        }


         for (int j=getCurvatura(1),k=getCurvatura(0); j>=-10;j-=5,k+=5)
        {

            setCurvaturaA(1,j);
            setCurvaturaA(0,k);
            curvaturaZ[3]=j;
            curvaturaZ[2]=j;
            chaoZ -= 1;
            Sleep(10);
            display();
        }

           for (int j=getCurvatura(1),k=getCurvatura(0); j<=30;j+=5,k-=5)
        {

            setCurvaturaA(1,j);
            setCurvaturaA(0,k);
            curvaturaZ[3]=j;
            curvaturaZ[2]=j;
            chaoZ -= 1;
            Sleep(10);
            display();
        }

    }
    for (int j=getCurvatura(1); j>=0;j-=5)
    {

            setCurvaturaA(1,j);
            curvaturaZ[3]=j;
            curvaturaZ[2]=j;
            display();
    }

}

void Corpo::tchau()
{
    home();

    for(int i = curvatura[3] ; i < 200; i+=10)
    {
        curvatura[3]=i;

        display();
    }

    for(int cont=0; cont<=5;cont++){

         for(int i = curvatura[3] ; i > 165; i-=5)
        {
            curvatura[3]=i;
            display();
        }
        for(int i = curvatura[3] ; i < 200; i+=10)
        {
            curvatura[3]=i;

            display();
        }
    }
    for(int i = curvatura[3] ; i >= 0; i-=10)
        {
            curvatura[3]=i;

            display();
        }
    home();
}

void Corpo::danca()
{
   // home();

    //setCurvaturaA(3,90);
    //setCurvaturaA(2,90);
    for(int v=0;v<=1; v++){
        for(int j = 0, i=0; j<=110;j+=2,i-=2){
            curvaturaZ[3]=i;
            curvaturaZ[2]=j;
            curvatura[3]=j-20;
            curvatura[2]=j+20;
            display();
        }

        home();
            //curvaturaZ[2]=-180;

        printf("3= %d ",curvaturaZ[3]);
        printf("2= %d ",curvaturaZ[2]);


        for (int j=getCurvatura(1), k=110,i=-110; j<=30;j+=2,k-=7,i+=7)
        {
                curvaturaZ[3]=i;
                curvaturaZ[2]=k;

                setCurvaturaA(1,j);

                display();
        }

        curvaturaZ[3]=0;
        curvaturaZ[2]=0;

        for(int i=0;i<=2;i++){

             for (int j=getCurvatura(1),k=getCurvatura(0); j>=-10;j-=1,k+=1)
            {

                setCurvaturaA(1,j);
                setCurvaturaA(0,k);
                setCurvaturaA(2,j);
                setCurvaturaA(3,j);
                Sleep(10);
                display();
            }

               for (int j=getCurvatura(1),k=getCurvatura(0); j<=30;j+=1,k-=1)
            {

                setCurvaturaA(1,j);
                setCurvaturaA(0,k);
                setCurvaturaA(2,j);
                setCurvaturaA(3,j);
                Sleep(10);
                display();
            }
        }
    }
    home();



     for (int j=getCurvatura(1),k=getCurvatura(0); j>=-10;j-=1,k+=1)
    {

        setCurvaturaA(1,j);
        setCurvaturaA(0,k);
        curvaturaZ[3]=j*10;
        Sleep(10);
        display();
    }

       for (int j=getCurvatura(1),k=getCurvatura(0); j<=30;j+=1,k-=1)
    {

        setCurvaturaA(1,j);
        setCurvaturaA(0,k);

        Sleep(10);
        display();
    }

    home();
    for (int j=getCurvatura(1),i=-110; j<=30;j+=2,i+=7)
    {
                curvaturaZ[3]=i;




                display();
    }


}


void Corpo::home()
{
    abrir(true);

    if (ang < 0)
        ang += 360;
    if (ang2< 0)
        ang2+= 360;
    if (ang3< 0)
        ang3+= 360;
    if (chaoAng < 0)
        chaoAng += 360;


    while (ang > 0)
    {
        ang-= 10;
        display();
    }
    ang = 0;
    while (ang2 > 0)
    {
        ang2-= 10;
        display();
    }
    ang2 = 0;
    while (ang3 > 0)
    {
        ang3-= 10;
        display();
    }
    ang3 = 0;
    display();
    while (chaoAng > 0)
    {
        chaoAng -= 10;
        display();
    }
    chaoAng = 0;
    display();

}









/////////////////////////////////////////////////////////////
Corpo m(1.0);

///////////////////////////////////////////////////
void init(void)
{
//    LoadGLTextures();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   glBindTexture(GL_TEXTURE_2D, texture[0]);
   //////////////ISSO AQUI EH PRA LUZ///////////E EU AINDA N SEI COMO FUNCA/////
    GLfloat			diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0};
    GLfloat			ambientLight[] = { 0.2f, 0.2f, 0.4f, 1.0};
    GLfloat			lightPos[] = { 0.0f, 500.0f, 100.0f, 1.0f };
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.0f,1.0f,0.5f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, diffuseLight );
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    //////////////////////////////////////////////////////////////////////////

    glPushMatrix();

        glTranslatef (0.0, -5.0, -15.0);
        glRotatef (ang3, 0.0, 0.0, 1.0);
        glRotatef (ang, 0.0, 1.0, 0.0);
        glRotatef (ang2, 1.0, 0.0, 0.0);
        //glColor3f(0,0,0);

      m.desenha();

    glPopMatrix();

        glPushMatrix();
        glRotatef(chaoAng, 0, 1, 0);
        glColor3f(0.0, 0.85, 0.0);
        Chao();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(130.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -10.0);
}




void keyboard (unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'q':
            if (m.getCurvatura(0) < 100)
                m.setCurvaturaA(0,m.getCurvatura(0)+5);
            break;
        case 'a':
            if (m.getCurvatura(0) > 0)
                m.setCurvaturaA(0,m.getCurvatura(0)-5);
            break;
        case 'w':
            if (m.getCurvatura(1) < 100)
                m.setCurvaturaA(1,m.getCurvatura(1)+5);
            break;
        case 's':
            if (m.getCurvatura(1) > 0)
                m.setCurvaturaA(1,m.getCurvatura(1)-5);
            break;
         case 'e':
            if (m.getCurvatura(2) < 100)
                m.setCurvatura(2,m.getCurvatura(2)+5);
            break;
        case 'd':
            if (m.getCurvatura(2) > 0)
                m.setCurvatura(2,m.getCurvatura(2)-5);
            break;
        case 'r':
            if (m.getCurvatura(3) < 100)
                m.setCurvatura(3,m.getCurvatura(3)+5);
            break;
        case 'f':
            if (m.getCurvatura(3) > 0)
                m.setCurvatura(3,m.getCurvatura(3)-5);
            break;
        case 't':
            if (m.getCurvatura(4) < 100)
                m.setCurvatura(4,m.getCurvatura(4)+5);
            break;
        case 'g':
            if (m.getCurvatura(4) > 0)
                m.setCurvatura(4,m.getCurvatura(4)-5);
            break;
        case '.': //>
            ang += 5;
            chaoAng += 5;
            if (ang>360)
                ang -= 360;
            break;
        case ',': //<
            ang -= 5;
            chaoAng -= 5;
            if (ang<0)
                ang += 360;
            break;
        case ']':
            ang2 += 5;
            if (ang2>360)
                ang2 -= 360;
            break;
        case '[':
            ang2 -= 5;
            if (ang2<0)
                ang2 += 360;
            break;
        case '+':
            m.abrir();
            break;
        case '*' :
            m.abrir(true);
            break;
        case '/' :
            m.fechar(true);
            break;
        case '-':
            m.fechar();
            break;
        case 27: //ESC
            exit(0);
            break;
        case '9':
            ang3 += 5;
            if (ang3>360)
                ang3 -= 360;
            break;
        case '0':
            ang3 -= 5;
            if (ang3<0)
                ang3 += 360;
            break;
        case '1' :
            m.tchau();
            break;
        case '2' :
            m.andar();
            break;
        case '3' :
            m.danca();
            break;
        case 'u':
            for(int i=0; i<4; i++)
            {
                if (m.getCurvatura(i) < 100)
                    m.setCurvaturaA(i,m.getCurvatura(i)+5);
            }
            break;
        case 'j':
            for(int i=0; i<4; i++)
            {
                if (m.getCurvatura(i)> 0)
                    m.setCurvaturaA(i,m.getCurvatura(i)-5);
            }

            break;

        case 8 :
            m.home();
            break;

        default:
            return;
    }
    glutPostRedisplay();
}

void olhos(int value){


    switch (olho){
        case 0: olho=3;glutTimerFunc(250,olhos, 1); break;
        case 1: olho++;glutTimerFunc(250,olhos, 1);break;
        case 2: olho=0;glutTimerFunc(250,olhos, 1);break;
        case 3: olho=1;glutTimerFunc(10000,olhos, 1);break;
    }

    glutPostRedisplay();
}







int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (300, 300);
    glutInitWindowPosition (200, 200);
    glutCreateWindow (argv[0]);
    init ();

    printf("FullScreen?(y/n) ");
    if (getchar() == 'y')
        glutFullScreen();


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    LoadGLTextures();
    /*if (!){
        printf("Aquii");
		return 1; // If Texture Didn't Load Return FALSE
	}*/

	glutTimerFunc(33, olhos, 1);

    glutMainLoop();
    return 0;
}
