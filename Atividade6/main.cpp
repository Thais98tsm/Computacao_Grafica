/**
 * Projeto 6 - Computação Gráfica
 * Desenho de um hexadecágono 3D
 * Thais Silva Mendes
 * 12/09/2021
*/

#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

/* Variáveis Globais */
int raio = 50;//Raio do hexadecágono
float tamanho = raio * sin(11.25 * PI / 180);//Calcula a metade do tamanho da ripa usando graus
float delta = (tamanho * 0.1);//Calcula o tamanho do excedente de cada lado da ripa
GLdouble obsX = 0, obsY = 0, obsZ = 200; //Posição incial do observador
GLfloat angle, fAspect;//Altura da visualização em y e área de visualização em x

// Callback para gerenciar eventos do teclado para teclas especiais (F1, PgDn, entre outras)
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
        glVertex3f(-tamanho-delta, -1.0, 1.0);
        glVertex3f(tamanho+delta, -1.0, 1.0);
        glVertex3f(tamanho+delta, 1.0, 1.0);
        glVertex3f(-tamanho-delta, 1.0, 1.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-tamanho-delta, -1.0, -1.0);
        glVertex3f(tamanho+delta, -1.0, -1.0);
        glVertex3f(tamanho+delta, 1.0, -1.0);
        glVertex3f(-tamanho-delta, 1.0, -1.0);
    glEnd();

    //Desenhas as linhas restantes para formar o paralelepípedo
    glBegin(GL_LINES);
        glVertex3f(-tamanho-delta, -1.0, 1.0);
        glVertex3f(-tamanho-delta, -1.0, -1.0);
        glVertex3f(-tamanho-delta, 1.0, 1.0);
        glVertex3f(-tamanho-delta, 1.0, -1.0);
        glVertex3f(tamanho+delta, -1.0, 1.0);
        glVertex3f(tamanho+delta, -1.0, -1.0);
        glVertex3f(tamanho+delta, 1.0, 1.0);
        glVertex3f(tamanho+delta, 1.0, -1.0);

    glEnd();

}

/* Posiciona cada um dos lados do hexadecágono no local correto */
void Posiciona_Retangulo(){
    glTranslatef(tamanho, 0.0, 0.0);
    glRotatef(22.5, 0, 0, 1);
    glTranslatef(tamanho, 0.0,  0.0);
    Retangulo();
}

/* Função callback chamada para fazer o desenho */
void Desenha(void){
    int lados = 1;
	glClear(GL_COLOR_BUFFER_BIT);

	//Primeiro lado do hexágono
    glColor3f(1.0, 0.0, 0.0);//Cor vermelha
    glTranslatef(raio, 0.0, 0.0);
    glRotatef(101.25, 0, 0, 1);
    glTranslatef(tamanho, 0.0, 0.0);
    Retangulo();

    while(lados < 16){
        if(lados % 2)//Intercala as cores entre vermelha e azul
            glColor3f(0.0, 0.0, 1.0);
        else
            glColor3f(1.0, 0.0, 0.0);
        Posiciona_Retangulo();
        lados++;
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
void EspecificaParametrosVisualizacao(void)
{
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
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;
	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;
	EspecificaParametrosVisualizacao();
}

/* Função callback chamada para gerenciar eventos do mouse */
void GerenciaMouse(int button, int state, int x, int y)
{
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

/* Programa Principal */
int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
	glutCreateWindow("Atividade 6");
	glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutSpecialFunc(SpecialKeys);
	Inicializa();
	glutMainLoop();
}
