/**
 * Projeto 1 - Computação Gráfica
 * Desenho de um hexadecágono
 * Thais Silva Mendes
 * 01/08/2021
*/

#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

/* Variáveis Globais */
int raio = 10;//Raio do hexadecágono
float tamanho = raio * sin(11.25 * PI / 180);//Calcula a metade do tamanho da ripa usando graus
float delta = (tamanho * 0.1);//Calcula o tamanho do excedente de cada lado da ripa

/* Eixos X e Y */
void Eixos(){
    glBegin(GL_LINES);
		glVertex2f(0.0, -30.0);
		glVertex2f(0.0, 30.0);
		glVertex2f(30.0, 0.0);
        glVertex2f(-30.0, 0.0);
	glEnd();
}

/* Desenha o retângulo */
void Retangulo(){
    glBegin(GL_LINE_LOOP);
        glVertex2f(-tamanho-delta, -0.25);
        glVertex2f(tamanho+delta, -0.25);
        glVertex2f(tamanho+delta, 0.25);
        glVertex2f(-tamanho-delta, 0.25);
    glEnd();
}

/* Posiciona cada um dos lados do hexadecágono no local corrento */
void Posiciona_Retangulo(){
    glTranslatef(tamanho, 0.0, 0.0);
    glRotatef(22.5, 0, 0, 1);
    glTranslatef(tamanho, 0.0,  0.0);
    Retangulo();
}

/* Desenha o hexadecágono */
void Desenha(){
    int lados = 1;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    //Desenha os eixos X e Y da cor preta
    glColor3f(0.0,0.0,0.0);
    Eixos(); //Caso de teste
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
    glFlush();
}

/* Inicializa a janela glut */
void Inicializa(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//Define o modo do display inicial
    glutInitWindowPosition(200,50);//Posição da janela
    glutInitWindowSize(750, 750);//Tamanho da janela
	glutCreateWindow("Atividade 1");//Nome da janela
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);// Define a cor de fundo da janela de visualização como branca
}

/* Inicializa o sistema de coordenadas */
void Atualiza_tamanho(int largura, int altura)
{
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-30.0f, 30.0f, -30.0f, 30.0f);//Estabele quais pontos serão mapeados na janela

}

/* Programa principal */
int main(void)
{
    Inicializa();//Inicializa a janela glut
	glutReshapeFunc(Atualiza_tamanho);//Registra eventos de alteração de tamanho da janela
	glutDisplayFunc(Desenha);//registra função callback para tratar evento de desenho
	glutMainLoop();//Inicia tratamento de eventos

    return 0;
}
