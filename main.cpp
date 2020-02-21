
/*********************************************************/
/*                        Robot                          */
/*********************************************************/
/*													     */
/*       ESGI: Algorithmiques pour l'infographies		 */
/*													     */
/*********************************************************/
/*													     */
/*  Objectif: afficher des formes 2D et les transformer  */
/*													     */
/*********************************************************/


#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// alpha c'est l'angle horisontal (longitude) - en radiant
// phi c'ngle vertical (altitude) - en radiant

float angle = 50.0;
float epaule = -5.0;
float cameraAngle = 10.0;
bool go = true;

float alpha = 0; // = de 0 a 2 PI
float phi = 0; // de -PI/2 a PI/2
float r = 5.0; // = C'esr le R c'est la distance
// r +- pas, pas >0 et r>0 !   Zoom avec -pas dezoom avec +pas

/* prototypes de fonctions */
void initRendering();                           // Initialisation du rendu
void display();                             // mod�lisation
void reshape(int w,int h);                      // visualisation
void update(int value);                         // mise � jour: appelle Timer pour l'animation de la sc�ne
void keyboard(unsigned char key, int x, int y); // fonction clavier


/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
		  char **argv){  // argv: tableau de chaines de caract�res, argv[0] contient le nom du programme lanc� (plus un �ventuel chemin)


	/* Initialisation de glut et creation de la fenetre */
  glutInit(&argc, argv);                       // Initialisation
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
  glutInitWindowSize(500, 500);                // dimension fen�tre
	glutInitWindowPosition (100, 100);           // position coin haut gauche
	glutCreateWindow("TP1: formes 2D et transformation");  // nom

	/* Initialisation d'OpenGL */
	initRendering();

	/* Enregistrement des fonctions de rappel
     => initialisation des fonctions callback appel�es par glut */
  glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(20,update,0);

	/* rq: le callback de fonction (fonction de rappel) est une fonction qui est pass�e en argument � une
	autre fonction. Ici, le main fait usage des deux fonctions de rappel (qui fonctionnent en m�me temps)
	alors qu'il ne les conna�t pas par avance.*/


	/* Entr�e dans la boucle principale de glut, traitement des �v�nements */
    glutMainLoop();         // lancement de la boucle de r�ception des �v�nements
    return 0;               // pour finir
}


/* Initialisation d'OpenGL pour le rendu de la sc�ne */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);

	/* d�finit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  d�finit la taille d'un pixel*/
	glPointSize(2.0);

}

/* Cr�ation de la sc�ne */
void display(){
	/* Efface les tampons de couleur et de profondeur de l'image avec la couleur de fond.
	rq: buffer: m�moire tampon, c'est donc une surface en memoire utilis�e pour stocker une image*/
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* la mat de visualisation-mod�lisation est modifiable par d�faut */
	glMatrixMode(GL_MODELVIEW);

	/* on charge l'identit� dans la matrice de mod�lisation-visualisation*/
	glLoadIdentity();


	/* Permet de cr�er un point de vue. D�finit une matrice de mod�lisation-visualisation et la multiplie
	� droite de lma matrice active, ici l'identit�*/
	//glRotatef(cameraAngle,0.0,0.0,1.0); v1 camera animation
	gluLookAt((r * cos(phi) * sin(alpha)),
						(r * sin(phi)),
					  (r * cos(phi) * cos(alpha)),      // position cam�ra
		      	0.0, 0.0, 0.0,      // visée
			  		0.0, 1.0, 0.0);     // vecteur d'orientation cam�ra
  //glRotatef(-cameraAngle,0.1,-0.1,1.0); V1 animation


 //ROBOT
		glPushMatrix();
			glPushMatrix();
				//head
				glScalef(0.9,1.0,0.9);
				glColor3f(0.788,0.725,0.505);
				glutSolidSphere(0.70, 18.0, 18.0);
			glPopMatrix();
			glPushMatrix();
				//eyeball left
				glColor3f(1.0,1.0,1.0);
				glTranslatef(-0.3,0.2,0.5);
				glScalef(0.1,0.1,0.1);
				glutSolidSphere(1.0,18.0,18.0);
			glPopMatrix();
			glPushMatrix();
				//eyeball right
				glColor3f(1.0,1.0,1.0);
				glTranslatef(0.3,0.2,0.5);
				glScalef(0.1,0.1,0.1);
				glutSolidSphere(1.0,18.0,18.0);
			glPopMatrix();
			glPushMatrix();
				//iris left
				glColor3f(0.9,0.0,0.0);
				glTranslatef(-0.3,0.2,0.6);
				glScalef(0.04,0.04,0.04);
				glutSolidSphere(1.0,18.0,18.0);
			glPopMatrix();
			glPushMatrix();
				//iris right
				glColor3f(0.9,0.0,0.0);
				glTranslatef(0.3,0.2,0.6);
				glScalef(0.04,0.04,0.04);
				glutSolidSphere(1.0,18.0,18.0);
			glPopMatrix();
				glPushMatrix();
					//nose
					glColor3f(0.7,0.0,0.0);
					glTranslatef(0.0,0.0,0.6);
					glScalef(0.08,0.14,0.08);
					glutSolidSphere(1.0,18.0,18.0);
				glPopMatrix();
			glPushMatrix();
				//ears
				glScalef(0.2,0.2,0.2);
				glColor3f(0.688,0.625,0.405);
				glPushMatrix();
					//right
					glTranslatef(3.0,0.0,0.0);
					glutSolidTetrahedron();
				glPopMatrix();
				glPushMatrix();
					//left
					glTranslatef(-3.0,0.5,0.0);
					glRotatef(180,0.0,0.0,1.0);
					glutSolidTetrahedron();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				//mouth
				glScalef(0.04,0.02,0.04);
				glColor3f(0.9,0.5,0.0);
				glTranslatef(0.0,-15.0,15.0);
				glutSolidTorus(2,4,18,18);
			glPopMatrix();
		glPopMatrix();


	/* On swap (�change) les buffers, c�d, on fait passer l'image calcul�e et dessin�e
	dans le back buffer au buffer qui va l'afficher: le front buffer (en g�n�ral), c'est le bouble buffering
	Cela �vite une image anim�e sacad�e, si elle �tait directement trac�e dans le front buffer*/
	glutSwapBuffers();

	/* On force l'affichage */
	glFlush(); // nettoie les fen�tres pr�c�dentes
}


void update(int value){
	//animation camera
/* animation v1
	if(cameraAngle>=360){
		cameraAngle=0;
	}else{
		cameraAngle+=0.1;
	}
*/

glutPostRedisplay();
glutTimerFunc(1,update,0);
}


/*  Mise en forme de la scene pour l'affichage */
void reshape(int w,  // w: largeur fenetre
			 int h)  // h: hauteur fenetre
{
	/* Viewport: cadrage. Specifie la region (position et taille en px) que l'image observee de la scene occupe
	 l'ecran => reduction et agrandissement de l'image possible*/
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);

	/* Specifie que la matrice de projection va etre modifiee  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();             // matrice courante: l'identite
	//glOrtho(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	/* Perspective avec point de fuite */
	gluPerspective(60.0,// angle d'ouverture vertical camera
				   (GLfloat) w / (GLfloat) h,// ratio largeur-hauteur
				   1.0,// plan proche z=1
				   200.0);// plan aloigne z=200


}

/* Fonction de gestion du clavier */
void keyboard(unsigned char key,       // Touche qui a ete pressee
                    int x, int y) {    // Coordonnees courante de la souris

		switch (key){

			case '-':
				if(r<10){
					r = r + 0.5;
					break;
				}else{
					r=10;
					break;
				}
			case '+':
				if(r>2){
					r = r - 0.5;
					break;
				}else{
					r=2;
					break;
				}
			case 'q':
				if(alpha<=2*M_PI){
					alpha = alpha + 0.1;
					break;
				}else{
					alpha=0;
					break;
				}
				case 'd':
					if(alpha>0){
						alpha = alpha - 0.1;
						break;
					}else{
						alpha=2*M_PI;
						break;
					}
			case 's':
				if(phi<=M_PI/2-0.1){
					phi = phi + 0.1;
					break;
				}else{
					phi=M_PI/2-0.1;
					break;
				}
			case 'z':
				if(phi>=-M_PI/2+0.1){
					phi = phi - 0.1;
					break;
				}else{
					phi=M_PI/-2+0.1;
					break;
				}
			case 'x':   /* Quitter le programme */
				exit(0);
		}
}
