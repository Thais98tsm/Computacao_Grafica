/**
 * Projeto 7 - Computação Gráfica
 * Desenho de uma estrela tripla 3D
 * Thais Silva Mendes
 * 20/09/2021
*/

#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

/* Variáveis Globais */
double raioH = 31.13;//Raio do hexadecágono
double metade = raioH * sin(11.25 * PI / 180);//Calcula a metade do tamanho da ripa usando graus
double tamanho = 2 * metade;//Calcula o tamanho de cada lado do hexadecágono/estrela
double sobra = (metade * 0.1);//Calcula o tamanho do excedente de cada lado da ripa
GLdouble obsX = 0, obsY = 0, obsZ = 150; //Posição incial do observador
GLfloat angle, fAspect;//Altura da visualização em y e área de visualização em x


/* Realiza os cálculos para descobrir o ângulo alpha */
double calculos(double raioE){
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

/* Desenha a primitiva */
void Retangulo(){
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

/* Posiciona cada um dos lados do hexadecágono no local correto */
void Posiciona_Retangulo(double alpha){
    glColor3f(0.0, 0.0, 1.0);//Cor azul
    glTranslatef(-metade, 0.0, 0.0);
    //Rotaciona o lado da estrela pelo ângulo externo
    glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
    glTranslatef(metade, 0.0, 0.0);
    Retangulo();

    glColor3f(1.0, 0.0, 0.0);//Cor vermelha
    glTranslatef(metade, 0.0, 0.0);
    glRotatef((- 2 * alpha), 0, 0, 1);
    glTranslatef(-metade, 0.0, 0.0);
    Retangulo();
}

/* Função callback chamada para fazer o desenho de cada um das estrelas */
void Desenha_Estrela(double raioE, double alpha){
    int lados = 0;

    glColor3f(1.0, 0.0, 0.0);//Cor vermelha
    glTranslatef(raioE, 0.0, 0.0);
    glRotatef(-alpha, 0, 0, 1);
    glTranslatef(-metade, 0.0, 0.0);
    Retangulo();

    while(lados < 7){
        Posiciona_Retangulo(alpha);
        lados++;
    }

    glColor3f(0.0, 0.0, 1.0);//Cor azul
    glTranslatef(-metade, 0.0, 0.0);
    glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
    glTranslatef(metade, 0.0, 0.0);
    Retangulo();
    // Executa os comandos OpenGL
	glutSwapBuffers();
}

/* Função callback chamada para fazer o desenho da estrela tripla */
void Desenha_Estrela_Tripla(double raioE, double alpha){
    glPushMatrix();
        Desenha_Estrela(raioE, alpha);
    glPopMatrix();

    glRotatef(90, 0, 1, 0);

    glPushMatrix();
        Desenha_Estrela(raioE, alpha);
    glPopMatrix();

    glRotatef(90, 1, 0, 0);

    glPushMatrix();
        Desenha_Estrela(raioE, alpha);
    glPopMatrix();
}

/* Função callback chamada para fazer o desenho */
void Desenha(void){
    double raioE = 31.13;
    double alpha = calculos(raioE);
	glClear(GL_COLOR_BUFFER_BIT);

	while(1){
        for(double i = tamanho; i < raioH; i += 0.5){
            glClear(GL_COLOR_BUFFER_BIT);
            raioE = i;
            alpha = calculos(raioE);
            Desenha_Estrela_Tripla(raioE, alpha);
            system("cls");
        }
        for(double j = raioH; j > tamanho; j -= 0.5){
            glClear(GL_COLOR_BUFFER_BIT);
            raioE = j;
            alpha = calculos(raioE);
            Desenha_Estrela_Tripla(raioE, alpha);
            system("cls");
        }
    }

	// Executa os comandos OpenGL
	glutSwapBuffers();
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

static void idle(void){
    glutPostRedisplay();
}

/* Programa Principal */
int main(void){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
	glutCreateWindow("Atividade 7");
	glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutSpecialFunc(SpecialKeys);
	glutIdleFunc(idle);
	Inicializa();
	glutMainLoop();
}
