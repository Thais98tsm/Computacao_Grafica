/**
 * Projeto 3 - Computação Gráfica
 * Animação da estrela de 8 pontas
 * Thais Silva Mendes
 * 16/08/2021
*/


#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265

/* Variáveis Globais */
double raioH = 31.13;//Raio do hexadecágono
double metade = raioH * sin(11.25 * PI / 180);//Calcula a metade do tamanho da ripa usando graus
double tamanho = 2 * metade;//Calcula o tamanho de cada lado do hexadecágono/estrela
double sobra = (metade * 0.1);//Calcula o tamanho do excedente de cada lado da ripa

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

/* Eixos X e Y */
void Eixos(){
    glBegin(GL_LINES);
		glVertex2f(0.0, -50.0);
		glVertex2f(0.0, 50.0);
		glVertex2f(50.0, 0.0);
        glVertex2f(-50.0, 0.0);
	glEnd();
}

/* Inicializa a janela glut */
void Inicializa(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//Define o modo do display inicial
    glutInitWindowPosition(200,50);//Posição da janela
    glutInitWindowSize(750, 750);//Tamanho da janela
	glutCreateWindow("Atividade 3");//Nome da janela
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);// Define a cor de fundo da janela de visualização como branca
}

/* Inicializa o sistema de coordenadas */
void Atualiza_tamanho(int largura, int altura){
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-50.0f, 50.0f, -50.0f, 50.0f);//Estabele quais pontos serão mapeados na janela

}

/* Desenha o retângulo */
void Retangulo(){
    glBegin(GL_LINE_LOOP);
        glVertex2f(-metade - sobra, -0.5);
        glVertex2f(metade + sobra, -0.5);
        glVertex2f(metade + sobra, 0.5);
        glVertex2f(-metade - sobra, 0.5);
    glEnd();
}

/* Faz o posicionamento dos lados da estrela */
void Posiciona_retangulo(double alpha, int flag){
    if(flag == 1){

        glColor3f(0.0, 0.0, 1.0);//Cor azul

        glTranslatef(-metade, 0.0, 0.0);
        //Rotaciona o lado da estrela pelo angulo externo
        glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
        glTranslatef(metade, 0.0, 0.0);
        Retangulo();

        glTranslatef(metade, 0.0, 0.0);
        glRotatef((- 2 * alpha), 0, 0, 1);
        glTranslatef(-metade, 0.0, 0.0);
        Retangulo();
    }
    else{
        glColor3f(1.0, 0.0, 0.0);//Cor vermelha

        glTranslatef(-metade, 0.0, 0.0);
        //Rotaciona o lado da estrela pelo angulo externo
        glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
        glTranslatef(metade, 0.0, 0.0);
        Retangulo();

        glTranslatef(metade, 0.0, 0.0);
        glRotatef((- 2 * alpha), 0, 0, 1);
        glTranslatef(-metade, 0.0, 0.0);
        Retangulo();
    }

}

/* Desenha cada uma das estrelas*/

void Desenha_estrela(double raioE, double alpha, int flag){
    int lados = 0;
    if(flag == 1){//Estrela AZUL
        //Desenha os eixos X e Y da cor preta
        glColor3f(0.0,0.0,0.0);
        Eixos(); //Caso de teste

        glRotatef(22.5, 0, 0, 1);

        glColor3f(0.0, 0.0, 1.0);//Cor azul
        glTranslatef(raioE, 0.0, 0.0);
        glRotatef(-alpha, 0, 0, 1);
        glTranslatef(-metade, 0.0, 0.0);
        Retangulo();

        while(lados < 7){
            Posiciona_retangulo(alpha, flag);
            lados++;
        }

        glTranslatef(-metade, 0.0, 0.0);
        glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
        glTranslatef(metade, 0.0, 0.0);
        Retangulo();

    }else{//Estrela VERMELHA
        //Desenha os eixos X e Y da cor preta
        glColor3f(0.0,0.0,0.0);
        Eixos(); //Caso de teste

        glColor3f(1.0, 0.0, 0.0);//Cor vermelha
        glTranslatef(raioE, 0.0, 0.0);
        glRotatef(-alpha, 0, 0, 1);
        glTranslatef(-metade, 0.0, 0.0);
        Retangulo();

        while(lados < 7){
            Posiciona_retangulo(alpha, flag);
            lados++;
        }

        glTranslatef(-metade, 0.0, 0.0);
        glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
        glTranslatef(metade, 0.0, 0.0);
        Retangulo();
    }

    glFlush();
}

/* Desenha */
void Desenha(){
    int cont = 0;
    double raioE, alpha;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    while(1){
        for(double i = tamanho; i < raioH; i += 0.5){
            glClear(GL_COLOR_BUFFER_BIT);
            raioE = i;
            alpha = calculos(raioE);
            glPushMatrix();
            Desenha_estrela(raioE, alpha, 1);
            glPopMatrix();

            glPushMatrix();
            Desenha_estrela(raioE, alpha, 2);
            glPopMatrix();
            system("cls");
        }
        for(double j = raioH; j > tamanho; j -= 0.5){
            glClear(GL_COLOR_BUFFER_BIT);
            raioE = j;
            alpha = calculos(raioE);
            glPushMatrix();
            Desenha_estrela(raioE, alpha, 1);
            glPopMatrix();

            glPushMatrix();
            Desenha_estrela(raioE, alpha, 2);
            glPopMatrix();
            system("cls");

        }
        cont++;
    }
}

void Teclado( unsigned char tecla, int x, int y){
    switch (tecla){
        case 27 :
        case 'q':
            exit(0);
        break;
    }
}

/* Programa principal */
int main(void){
    Inicializa();//Inicializa a janela glut
	glutReshapeFunc(Atualiza_tamanho);//Registra eventos de alteração de tamanho da janela
	glutDisplayFunc(Desenha);//registra função callback para tratar evento de desenho
	glutKeyboardFunc(Teclado);
	glutMainLoop();//Inicia tratamento de eventos
    return 0;
}
