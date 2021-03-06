/**
 * Projeto 5 - Computa??o Gr?fica
 * Desenho de uma estrela de 8 pontas dupla fixas no ponto m?dio
 * Thais Silva Mendes
 * 30/08/2021
*/

#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265

/* Vari?veis Globais */
double raioH = 31.13;//Raio do hexadec?gono
double metade = raioH * sin(11.25 * PI / 180);//Calcula a metade do tamanho da ripa usando graus
double tamanho = 2 * metade;//Calcula o tamanho de cada lado do hexadec?gono/estrela
double metadeDiv2 = metade / 2;
double sobra = (metadeDiv2 * 0.1);//Calcula o tamanho do excedente de cada lado da ripa


/* Realiza os c?lculos para descobrir o ?ngulo alpha */
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

/* Desenha o ret?ngulo */
void Retangulo(bool flag){
    if(!flag){//Estrela com a ponta dobrada
        glBegin(GL_QUADS);
            glVertex2f(-metadeDiv2 - sobra, -0.5);
            glVertex2f(metadeDiv2 + sobra, -0.5);
            glVertex2f(metadeDiv2 + sobra, 0.5);
            glVertex2f(-metadeDiv2 - sobra, 0.5);
        glEnd();
    }else{//Estrela normal
        glBegin(GL_QUADS);
            glVertex2f(-metade - sobra, -0.5);
            glVertex2f(metade + sobra, -0.5);
            glVertex2f(metade + sobra, 0.5);
            glVertex2f(-metade - sobra, 0.5);
        glEnd();
    }


}

/* Posiciona cada um dos lados do hexadec?gono no local correto */
void Desenha_ponta(double alpha, double raioE, bool flag){
    double raioEmenosx = cos(alpha * PI / 180) * metade * 2;
    double theta = (180 - (2 * alpha));//3? ?ngulo do tri?ngulo menor
    double gama = 180 - 22.5 - alpha;//3? ?ngulo da 1? situa??o
    double delta = (360 - (2 * gama));//Angulo externo a 1? estrela e tamb?m do quadrado
    double epsilon = (360 - (2 * delta)) / 2;//Outro ?ngulo do quadrado

    if(flag){//Estrela normal
        glColor3f(1.0, 0.0, 0.0);//Cor vermelha

        glTranslatef(-metade, 0.0, 0.0);
        //Rotaciona o lado da estrela pelo angulo externo
        glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
        glTranslatef(metade, 0.0, 0.0);
        Retangulo(flag);

        glTranslatef(metade, 0.0, 0.0);
        glRotatef((- 2 * alpha), 0, 0, 1);
        glTranslatef(-metade, 0.0, 0.0);
        Retangulo(flag);
    }else{//Estrela com a ponta dobrada
        glColor3f(0.0, 0.0, 1.0);//Cor azul
        glTranslatef((raioE - raioEmenosx), 0.0, 0.0);
        glRotatef(alpha, 0, 0, 1);
        glTranslatef(metadeDiv2, 0.0, 0.0);
        Retangulo(flag);

        glTranslatef(metadeDiv2, 0.0, 0.0);
        glRotatef(-(180 - theta + epsilon), 0, 0, 1);
        glTranslatef(-metadeDiv2, 0.0, 0.0);
        Retangulo(flag);

        glTranslatef(-metadeDiv2, 0.0, 0.0);
        glRotatef((180 - delta), 0, 0, 1);
        glTranslatef(-metadeDiv2, 0.0, 0.0);
        Retangulo(flag);

        glTranslatef(-metadeDiv2, 0.0, 0.0);
        glRotatef(180 - (180 - theta + epsilon), 0, 0, 1);
        glTranslatef(-metadeDiv2, 0.0, 0.0);
        Retangulo(flag);
    }


}

/* Desenha cada uma das estrelas*/

void Desenha_estrela(double raioE, double alpha, int flag){
    int lados = 0;
    if(flag){//Estrela normal
        glColor3f(1.0, 0.0, 0.0);//Cor vermelha
        glTranslatef(raioE, 0.0, 0.0);
        glRotatef(-alpha, 0, 0, 1);
        glTranslatef(-metade, 0.0, 0.0);
        Retangulo(flag);

        while(lados < 7){
            Desenha_ponta(alpha, raioE, flag);
            lados++;
        }

        glTranslatef(-metade, 0.0, 0.0);
        glRotatef((360 - 2*(180 - alpha - 22.5)), 0, 0, 1);
        glTranslatef(metade, 0.0, 0.0);
        Retangulo(flag);
    }else{//Estrela com a ponta dobrada
        while(lados < 8){
            glPushMatrix();
            glRotatef(lados * 45, 0, 0, 1);
            Desenha_ponta(alpha, raioE, flag);
            glPopMatrix();
            lados++;
        }
    }
    glFlush();
}

/* Desenha */
void Desenha(){
    double raioE = 25.3;
    double alpha = calculos(raioE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    //Desenha os eixos X e Y da cor preta
    glColor3f(0.0,0.0,0.0);
    Eixos(); //Caso de teste

    while(1){
        for(double i = tamanho; i < raioH; i += 0.5){
            glClear(GL_COLOR_BUFFER_BIT);
            raioE = i;
            alpha = calculos(raioE);
            glPushMatrix();
            Desenha_estrela(raioE, alpha, true);
            glPopMatrix();

            glPushMatrix();
            Desenha_estrela(raioE, alpha, false);
            glPopMatrix();
            system("cls");
        }
        for(double j = raioH; j > tamanho; j -= 0.5){
            glClear(GL_COLOR_BUFFER_BIT);
            raioE = j;
            alpha = calculos(raioE);
            glPushMatrix();
            Desenha_estrela(raioE, alpha, true);
            glPopMatrix();

            glPushMatrix();
            Desenha_estrela(raioE, alpha, false);
            glPopMatrix();
            system("cls");
        }
    }
}

/* Inicializa a janela glut */
void Inicializa(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//Define o modo do display inicial
    glutInitWindowPosition(200,50);//Posi??o da janela
    glutInitWindowSize(750, 750);//Tamanho da janela
	glutCreateWindow("Atividade 5");//Nome da janela
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);// Define a cor de fundo da janela de visualiza??o como branca
}

/* Inicializa o sistema de coordenadas */
void Atualiza_tamanho(int largura, int altura){
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-50.0f, 50.0f, -50.0f, 50.0f);//Estabele quais pontos ser?o mapeados na janela

}

/* Programa principal */
int main(void){
    Inicializa();//Inicializa a janela glut
	glutReshapeFunc(Atualiza_tamanho);//Registra eventos de altera??o de tamanho da janela
	glutDisplayFunc(Desenha);//registra fun??o callback para tratar evento de desenho
	glutMainLoop();//Inicia tratamento de eventos
    return 0;
}
