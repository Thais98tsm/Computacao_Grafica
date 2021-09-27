/**
 * Projeto 8 - Computação Gráfica
 * Desenho de uma estrela tripla 3D
 * Thais Silva Mendes
 * 24/09/2021
*/

#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

/* Variáveis Globais */
double raioH = 31.13, raioE = 31.13;//Raio do hexadecágono e raio da estrela
double metade = raioH * sin(11.25 * PI / 180);//Calcula a metade do tamanho da ripa usando graus
double metadeDiv2 = metade / 2;//1/4 do tamanho de cada aresta da estrela, utilizada para a estrela com a ponta dobrada
double tamanho = 2 * metade;//Calcula o tamanho de cada lado do hexadecágono/estrela
double sobra = (metade * 0.1);//Calcula o tamanho do excedente de cada lado da ripa
GLdouble obsX = 0, obsY = 0, obsZ = 150; //Posição incial do observador
GLfloat angle, fAspect;//Altura da visualização em y e área de visualização em x
bool usuario = false, controle = true;//usuario = Verifica se o usuário quer animar a estrela | controle = controla se a estrela deve aumentar ou diminuir

/* Realiza os cálculos para descobrir o ângulo alpha */
double Calculos(){
    int a = 1;
    double b = -2 * raioE * cos(22.5 * PI / 180);
    double c =  (raioE * raioE) - (tamanho * tamanho);
    double delta = (b * b) - 4 * a * c;
    double raiz1, raiz2, menorRaiz, cosAlpha;

    raiz1 = (-b + sqrt(delta))/(2 * a);
    raiz2 = (-b - sqrt(delta))/(2 * a);

    if(raiz2 < raiz1 && raiz2 > 0)
        menorRaiz = raiz2;
    else
        menorRaiz = raiz1;

    cosAlpha = ((menorRaiz * menorRaiz) - (raioE * raioE) - (tamanho * tamanho)) / (-2 * raioE * tamanho);
    return acos(cosAlpha) * 180 / PI;
}

/* Callback para gerenciar eventos do teclado para teclas especiais (F1, PgDn, entre outras) */
void SpecialKeys(int key, int x, int y){
	switch (key) {
		case GLUT_KEY_LEFT :
			obsX -= 10;
		break;
		case GLUT_KEY_RIGHT :
			obsX += 10;
		break;
		case GLUT_KEY_UP :
			obsY += 10;
		break;
        case GLUT_KEY_DOWN :
			obsY -= 10;
		break;
        case GLUT_KEY_HOME :
			obsZ += 10;
		break;
		case GLUT_KEY_END :
            obsZ -= 10;
		break;
    }
	glLoadIdentity();
	gluLookAt(obsX,obsY,obsZ, 0,0,0, 0,1,0);//Atualiza a posição do observador
   	glutPostRedisplay();
}

/* Função callback chamada pela GLUT a cada intervalo de tempo */
void Timer(int value){
    if(raioE >= tamanho && controle){
        raioE -= 0.05;
        controle = true;
    }
    if((raioE < tamanho || raioE == tamanho) || !controle){
        raioE += 0.05;
        controle = false;
    }

    // Redesenha a estrela com o novo raio
    glutPostRedisplay();
    if(usuario)
        glutTimerFunc(50, Timer, 1);

}

/* Função callback chamada para gerenciar eventos de teclado */
void GerenciaTeclado(unsigned char key, int x, int y){
    switch (key) {
            case 'A':
            case 'a':// muda a cor corrente para vermelho
                usuario = true;
                glutTimerFunc(50, Timer, 1);
            break;
            case 'I':
            case 'i':
                usuario = false;
            break;
    }
    glutPostRedisplay();
}

/* Inicializa parâmetros de rendering */
void Inicializa (void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    angle = 45;
}

/* Função usada para especificar o volume de visualização */
void EspecificaParametrosVisualizacao(void){
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
	// Especifica a projeção perspectiva
    gluPerspective(angle, fAspect, 0.5, 500);
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Especifica posição do observador e do alvo
    gluLookAt(obsX,obsY,obsZ, 0,0,0, 0,1,0);
}

/* Função callback chamada quando o tamanho da janela é alterado */
void AlteraTamanhoJanela(GLsizei w, GLsizei h){
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;
	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;
	EspecificaParametrosVisualizacao();
}

/* Função callback chamada para gerenciar eventos do mouse */
void GerenciaMouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

/* Desenha a primitiva */
void Paralelepidedo(bool flag){
    if(!flag){
        //Desenha a frente e o fundo do paralelepípedo
        glBegin(GL_LINE_LOOP);
            glVertex3f(-metadeDiv2-sobra, -1.0, 1.0);
            glVertex3f(metadeDiv2+sobra, -1.0, 1.0);
            glVertex3f(metadeDiv2+sobra, 1.0, 1.0);
            glVertex3f(-metadeDiv2-sobra, 1.0, 1.0);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex3f(-metadeDiv2-sobra, -1.0, -1.0);
            glVertex3f(metadeDiv2+sobra, -1.0, -1.0);
            glVertex3f(metadeDiv2+sobra, 1.0, -1.0);
            glVertex3f(-metadeDiv2-sobra, 1.0, -1.0);
        glEnd();

        //Desenhas as linhas restantes para formar o paralelepípedo
        glBegin(GL_LINES);
            glVertex3f(-metadeDiv2-sobra, -1.0, 1.0);
            glVertex3f(-metadeDiv2-sobra, -1.0, -1.0);
            glVertex3f(-metadeDiv2-sobra, 1.0, 1.0);
            glVertex3f(-metadeDiv2-sobra, 1.0, -1.0);
            glVertex3f(metadeDiv2+sobra, -1.0, 1.0);
            glVertex3f(metadeDiv2+sobra, -1.0, -1.0);
            glVertex3f(metadeDiv2+sobra, 1.0, 1.0);
            glVertex3f(metadeDiv2+sobra, 1.0, -1.0);
        glEnd();
    }else{
        //Desenha a frente e o fundo do paralelepípedo
        glBegin(GL_LINE_LOOP);
            glVertex3f(-metade-sobra, -1.0, 1.0);
            glVertex3f(metade+sobra, -1.0, 1.0);
            glVertex3f(metade+sobra, 1.0, 1.0);
            glVertex3f(-metade-sobra, 1.0, 1.0);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex3f(-metade-sobra, -1.0, -1.0);
            glVertex3f(metade+sobra, -1.0, -1.0);
            glVertex3f(metade+sobra, 1.0, -1.0);
            glVertex3f(-metade-sobra, 1.0, -1.0);
        glEnd();

        //Desenhas as linhas restantes para formar o paralelepípedo
        glBegin(GL_LINES);
            glVertex3f(-metade-sobra, -1.0, 1.0);
            glVertex3f(-metade-sobra, -1.0, -1.0);
            glVertex3f(-metade-sobra, 1.0, 1.0);
            glVertex3f(-metade-sobra, 1.0, -1.0);
            glVertex3f(metade+sobra, -1.0, 1.0);
            glVertex3f(metade+sobra, -1.0, -1.0);
            glVertex3f(metade+sobra, 1.0, 1.0);
            glVertex3f(metade+sobra, 1.0, -1.0);
        glEnd();
    }
}

/* Posiciona cada um dos lados da estrela no local correto */
void DesenhaPonta(double alpha, bool flag){
    //Cálculos utilizados para montar a estrela com a ponta dobrada
    double raioEmenosx = cos(alpha * PI / 180) * metade * 2;
    double theta = (180 - (2 * alpha));//3º ângulo do triângulo menor
    double gama = 180 - 22.5 - alpha;//3º ângulo da 1º situação
    double delta = (360 - (2 * gama));//Angulo externo a 1º estrela e também do quadrado
    double epsilon = (360 - (2 * delta)) / 2;//Outro ângulo do quadrado

    if(flag){//Estrela normal
        glColor3f(1.0, 0.0, 0.0);//Cor vermelha

        glTranslatef(-metade, 0.0, 0.0);
        //Rotaciona o lado da estrela pelo angulo externo
        glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
        glTranslatef(metade, 0.0, 0.0);
        Paralelepidedo(flag);

        glTranslatef(metade, 0.0, 0.0);
        glRotatef((- 2 * alpha), 0, 0, 1);
        glTranslatef(-metade, 0.0, 0.0);
        Paralelepidedo(flag);
    }else{//Estrela com a ponta dobrada
        glColor3f(0.0, 0.0, 1.0);//Cor azul
        glTranslatef((raioE - raioEmenosx), 0.0, 0.0);
        glRotatef(alpha, 0, 0, 1);
        glTranslatef(metadeDiv2, 0.0, 0.0);
        Paralelepidedo(flag);

        glTranslatef(metadeDiv2, 0.0, 0.0);
        glRotatef(-(180 - theta + epsilon), 0, 0, 1);
        glTranslatef(-metadeDiv2, 0.0, 0.0);
        Paralelepidedo(flag);

        glTranslatef(-metadeDiv2, 0.0, 0.0);
        glRotatef((180 - delta), 0, 0, 1);
        glTranslatef(-metadeDiv2, 0.0, 0.0);
        Paralelepidedo(flag);

        glTranslatef(-metadeDiv2, 0.0, 0.0);
        glRotatef(180 - (180 - theta + epsilon), 0, 0, 1);
        glTranslatef(-metadeDiv2, 0.0, 0.0);
        Paralelepidedo(flag);
    }
}

/* Função callback chamada para fazer o desenho da estrela dupla, a normal e a com a ponta dobrada */
void DesenhaEstrelaDupla(double alpha){
    int lados = 0;
    //Estrela normal
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);//Cor vermelha
        glTranslatef(raioE, 0.0, 0.0);
        glRotatef(-alpha, 0, 0, 1);
        glTranslatef(-metade, 0.0, 0.0);
        Paralelepidedo(true);

        while(lados < 7){
            DesenhaPonta(alpha, true);
            lados++;
        }

        glTranslatef(-metade, 0.0, 0.0);
        glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
        glTranslatef(metade, 0.0, 0.0);
        Paralelepidedo(true);
    glPopMatrix();
    //Estrela com a ponta dobrada
    lados = 0;
    while(lados < 8){
        glPushMatrix();
            glRotatef(lados * 45, 0, 0, 1);
            DesenhaPonta(alpha, false);
        glPopMatrix();
        lados++;
    }
    glutSwapBuffers();
}

/* Função callback chamada para fazer o desenho da estrela em três dimensões */
void DesenhaEstrela3D(double alpha){
    DesenhaEstrelaDupla(alpha);
    DesenhaEstrelaDupla(alpha);

    glRotatef(90, 0, 1, 0);

    DesenhaEstrelaDupla(alpha);
    DesenhaEstrelaDupla(alpha);

    glRotatef(90, 1, 0, 0);

    DesenhaEstrelaDupla(alpha);
    DesenhaEstrelaDupla(alpha);
}


/* Função callback que desenha toda a cena e faz animação */
void Desenha(){
    double alpha;
	glClear(GL_COLOR_BUFFER_BIT);

	alpha = Calculos();
    DesenhaEstrela3D(alpha);
	glutSwapBuffers();
}

/* Programa Principal */
int main(void){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
	glutCreateWindow("Atividade 8");
	glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(GerenciaTeclado);
	Inicializa();
	glutMainLoop();
}
