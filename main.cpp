#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

int posx = 300;
int largura = 50;
int altura = 50;
float aspecto = 50;
int win = 50;
int dx = 0;
int dy = 0;
int rc = 0;
char texto[12] = "";
int timerActive = 0;

void DesenhaFoguete(void){

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-5.0f, 30.0f);
        glVertex2f(5.0f,  30.0f);
        glVertex2f(5.0f,  10.0f);
        glVertex2f(-5.0f, 10.0f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 40.0f);
        glVertex2f(-5.0f, 30.0f);
        glVertex2f(5.0f, 30.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-5.0f, 20.0f);
        glVertex2f(-10.0f, 10.0f);
        glVertex2f(-5.0f, 10.0f);
        glVertex2f(5.0f, 20.0f);
        glVertex2f(10.0f, 10.0f);
        glVertex2f(5.0f, 10.0f);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-3.0f, 7.5f);
        glVertex2f(3.0f, 7.5f);
        glVertex2f(0.0f, 0.0f);
    glEnd();
}
void FazMoldura(){
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-win*aspecto, -win);
        glVertex2f(-win*aspecto, win);
        glVertex2f(win*aspecto, win);
        glVertex2f(win*aspecto, -win);
    glEnd();
    glLineWidth(1);
}
void Desenha(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, largura, altura);

    glPushMatrix();
    glRotatef(45, 0, 0, 1);

    glPopMatrix();

    glPushMatrix();
        glRotatef(rc, 0, 0, 1);
        glTranslatef(dx, dy, 0);
        DesenhaFoguete();
    glPopMatrix();

    glPushMatrix();
      glPushAttrib(GL_CURRENT_BIT);
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(-45, -45);
        char *str;
        str = texto;

        glScalef(5,5,1);
        while(*str){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *str++);
        }
        glPopAttrib();
    glPopMatrix();

    FazMoldura();
    //glFlush();
    glutSwapBuffers();
}

void RotacionaTimer(int value){
    if(timerActive == 1){
        rc++;
        glutTimerFunc(33, RotacionaTimer, value);
    }else{
        printf("END LOOP");
    }
    glutPostRedisplay();
}

void StopTimer(){
    timerActive = 0;
}

void Inicializa(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void verificaModificadores() {
    int modificadores = glutGetModifiers();
    if(modificadores & GLUT_ACTIVE_ALT)
        printf("Alt apertado\n");
    if(modificadores & GLUT_ACTIVE_SHIFT)
        printf("Shift apertado\n");
    if(modificadores & GLUT_ACTIVE_CTRL)
        printf("Ctrl apertado\n");
}
void teclado(unsigned char tecla, int x, int y){
    verificaModificadores();
    switch(tecla){
        case 27 :
            printf("Tchau!\n");
            exit(0);
        case 'a' :
            glutFullScreen();
            break;
        case 's' :
            glutReshapeWindow(100, 100);
            glutPositionWindow(500, 500);
            break;
        case 'i':
            timerActive = 1;
            RotacionaTimer(1);
            break;
        case 'p':
            StopTimer();
            break;
        default :
            printf("vc apertou (%c)\n", tecla);
    }
}
void teclasEspeciais(int tecla, int x, int y){
    verificaModificadores();
    switch(tecla){
        case GLUT_KEY_F1 :
            printf("Vc apertou F1\n");
            break;
        case GLUT_KEY_LEFT :
            //if(posx > 50) posx-=50;
            //glutPositionWindow(posx, 300);
            dx -= 1;
            break;
        case GLUT_KEY_RIGHT :
            //if(posx > 500) posx+=50;
            //glutPositionWindow(posx, 300);
            dx += 1;
            break;
        case GLUT_KEY_DOWN :
            dy -= 1;
            break;
        case GLUT_KEY_UP :
            dy += 1;
            break;
        default : printf("Vc apertou outra tecla especial [%d]\n", tecla);

    }
    glutPostRedisplay();
}
void GerenciaMouse(int button, int state, int x, int y){
    printf("botao %d \n", button);

    if(button == 0 && state == GLUT_DOWN){
        if(rc < 360){
            rc += 10;
        }else{
            rc = 0;
            rc += 10;
        }
    }else{
        if(button == 2 && state == GLUT_DOWN){
            if(rc > -360){
                rc -= 10;
            }else{
                rc = 0;
                rc -= 10;
            }
        }
    }
    glutPostRedisplay();
}
void movimentoMouseBotaoApertado(int x, int y){
    printf("Botao apertado[%d, %d]\n", x, y);
}
void movimentoMouse(int x, int y){
    sprintf(texto, "(%d, %d)", x, y);
    glutPostRedisplay();
}
void ocioso(void){
    //printf(".");
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h){
    if(h == 0) h=1;
    largura = w;
    altura = h;
    aspecto = (float) largura/altura;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-win*aspecto, win*aspecto, -win, win);

/*    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w <= h)
        gluOrtho2D(-50.0f, 50.0f, -50.0f*h/w, 50.0f*h/w);
    else
        gluOrtho2D(-50.0f*h/w, 50.0f*h/w, -50.0f, 50.0f);
*/
}

int main(void){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    Inicializa();
    glutCreateWindow("Primeiro Programa - Teclado");
    glutDisplayFunc(Desenha);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclasEspeciais);
    glutMouseFunc(GerenciaMouse);
    glutMotionFunc(movimentoMouseBotaoApertado);
    glutPassiveMotionFunc(movimentoMouse);
 //   glutIdleFunc(ocioso);
    //criaMenu();
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMainLoop();
}
