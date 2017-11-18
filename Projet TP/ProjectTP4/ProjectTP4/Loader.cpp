#include "struct.h"
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "../../../GL/glut.h"

using namespace std;

struct sMaillage 
{
	int nbSommets;
	int nbFacettes;
	int nbAretes;
	float maxCoord = 0.0;
	point3 gravity = point3(0,0,0);
	vector<point3> sommets;
	vector<vector<int>> facettes;
} maillage;

string nbSom, nbFac, nbAre;

#define WIDTH  1080
#define HEIGHT 1080

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1
#define PI 3.14159

#define KEY_ESC 27

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid window_idle();
int zRotated;


// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(RED, GREEN, BLUE, ALPHA);
	glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	render_scene();

	// trace la scène grapnique qui vient juste d'être définie
	glFlush();
	glutSwapBuffers();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);

	// toutes les transformations suivantes s´appliquent au modèle de vue 
	glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case KEY_ESC:
		exit(1);
		break;

	default:
		printf("La touche %d n´est pas active.\n", key);
		break;
	}
}

GLvoid window_idle()
{
	zRotated++;
	glutPostRedisplay();
}


void render_scene()
{
	//c'est ici qu'on dessine
	glLoadIdentity();
	glRotatef(zRotated, 0, 1, 0);
	for (int i = 0; i < maillage.nbFacettes;i++) {

		vector<int> facetteGL = maillage.facettes[i];
		
		//cout << facetteGL[1] << facetteGL[2] << facetteGL[3] << endl;

		point3 pointA = maillage.sommets.at(facetteGL.at(1));
		point3 pointB = maillage.sommets.at(facetteGL.at(2));
		point3 pointC = maillage.sommets.at(facetteGL.at(3));		
		
		glBegin(GL_TRIANGLES);
			glColor3f(0.75, 0, 0);
			glVertex3f(pointA.x, pointA.y, pointA.z);
			glVertex3f(pointB.x, pointB.y, pointB.z);
			glVertex3f(pointC.x, pointC.y, pointC.z);		
		glEnd();
	}	
}

void initNbSommetFacetteArrete(string ligne) {
	size_t pos = 0;
	string delimiter = " ";
	string token;
	int i = 1;
	while ((pos = ligne.find(delimiter)) != std::string::npos) {
		token = ligne.substr(0, pos);
		if (i == 1) {
			nbSom = token;
		}
		else if (i == 2) {
			nbFac = token;
		}
		else {
			cout << "Problème avec les nombres de sommets, faces et arretes";
		}
		i++;
		ligne.erase(0, pos + delimiter.length());
	}
	nbAre = ligne;
}

point3 creationPoint(string ligne) {
	size_t pos = 0;
	string delimiter = " ";
	string token;
	int i = 1;
	point3 point;	

	while ((pos = ligne.find(delimiter)) != std::string::npos) {
		token = ligne.substr(0, pos);
		if (i == 1) {
			point.x = stof(token);
			if(maillage.maxCoord < abs(point.x) ) {
				maillage.maxCoord = abs(point.x);
			}
		}
		else if (i == 2) {
			point.y = stof(token);
			if (maillage.maxCoord < abs(point.y)) {
				maillage.maxCoord = abs(point.y);
			}
		}
		else {
			cout << "Problème avec le point" << i+2 << endl;
		}
		i++;
		ligne.erase(0, pos + delimiter.length());
	}
	point.z = stof(ligne);
	if (maillage.maxCoord < abs(point.z)) {
		maillage.maxCoord = abs(point.z);		
	}
	maillage.gravity.x += point.x;
	maillage.gravity.y += point.y;
	maillage.gravity.z += point.z;

	return point;
}

vector<int> creationFacette(string ligne) {
	size_t pos = 0;
	string delimiter = " ";
	string token;
	int i = 1;
	vector<int> facette;

	while ((pos = ligne.find(delimiter)) != std::string::npos) {
		token = ligne.substr(0, pos);
		facette.push_back(stol(token));
		i++;
		ligne.erase(0, pos + delimiter.length());
	}
	//facette.push_back(stol(ligne));
	return facette;
}

void ouvertureFichier(string fichierNom) {	
	// on ouvre le fichier en lecture
	ifstream fichier(fichierNom, ios::in);  
	string ligne;

	if (fichier)  // si l'ouverture a réussi
	{
		string ligne;

		for (int i = 1; i <= 2; i++) {
			if (i == 1) {
				getline(fichier, ligne);
				cout << ligne << endl;
				if (ligne.find("OFF") != string::npos)
				{
					continue;
				}
				else {
					cout << "Probleme d'extention";
					break;
				}
			}
			if (i == 2) {				
				getline(fichier, ligne);
				initNbSommetFacetteArrete(ligne);
			}
		}
		fichier.close();  // on ferme le fichier
	}
	else  // sinon
		cerr << "Impossible d'ouvrir le fichier !" << endl;	
}

void stockage(string fichierNom) {
	ifstream fichier(fichierNom, ios::in);
	string ligne;

	if (fichier)  // si l'ouverture a réussi
	{
		for (int i = 1; i <= maillage.nbSommets + maillage.nbFacettes + 2; i++) {
			getline(fichier, ligne);
			if (i <= 2)
				continue;
			else if (i > 2 && i <= maillage.nbSommets + 2) {				
				maillage.sommets.push_back(creationPoint(ligne));
			}
			else
			{								
				maillage.facettes.push_back(creationFacette(ligne));
			}
		}
	}
	fichier.close();
}

void centrageDuMaillage() {
	for (int i = 0; i < maillage.nbSommets; i++) {
		maillage.sommets[i].x -= maillage.gravity.x;
		maillage.sommets[i].y -= maillage.gravity.y;
		maillage.sommets[i].z -= maillage.gravity.z;
	}
}

void normalisationDuMaillage() {
	for (int i = 0; i < maillage.nbSommets; i++) {
		maillage.sommets[i].x /= maillage.maxCoord;		
		maillage.sommets[i].y /= maillage.maxCoord;
		maillage.sommets[i].z /= maillage.maxCoord;
	}
}

void sauverFichier(string fichierNom) {

	    //déclaration du flux et ouverture du fichier
		ofstream fichier(fichierNom, ios::out | ios::trunc); 

		if (fichier)  // si l'ouverture a réussi
		{
			fichier << "OFF" << endl;
			fichier << maillage.nbSommets << " " << maillage.nbFacettes << " " << maillage.nbAretes << endl;
			for (int i = 0; i < maillage.nbSommets; i++) {
				fichier << maillage.sommets[i].x << " " << maillage.sommets[i].y << " " << maillage.sommets[i].z << " " << endl;
			}
			for (int j = 0; j < maillage.nbFacettes; j++) {
				fichier << maillage.facettes[j][0] << " " << maillage.facettes[j][1] << " " << maillage.facettes[j][2] << " " << maillage.facettes[j][3] << endl;
			}
			fichier.close();  // on referme le fichier
		}
		else  // sinon
			cerr << "Erreur à l'ouverture !" << endl;
}


//BEGIN TODO --------------------------------------------------------------------------------------
//void retirerFacettes() {
//
//	random_device rd;     // only used once to initialise (seed) engine
//	mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
//	uniform_int_distribution<int> uni(0, maillage.nbFacettes); // guaranteed unbiased
//	
//	for (int i = 0; i < 100; i++) {
//		auto random_integer = uni(rng);
//		vector<int> vec = maillage.facettes[random_integer];
//		for (int j = 0; j < 4; i++) {
//			maillage.sommets.erase(vec.begin+vec[j]);
//		}
//		maillage.facettes.erase(vec.begin + random_integer);
//	}
//
//}
//END TODO ---------------------------------------------------------------------------------------

int main(int argc, char **argv)
{

	string fichier = "buddha.off";
	//string fichier = "test.off";

	ouvertureFichier(fichier);

	maillage.nbSommets = stoi(nbSom);
	maillage.nbFacettes = stoi(nbFac);
	maillage.nbAretes = stoi(nbAre);

	stockage(fichier);
	maillage.gravity /= maillage.nbSommets;
	
	cout << maillage.gravity << endl;
	centrageDuMaillage();

	cout << maillage.maxCoord << endl;
	normalisationDuMaillage();

	//retirerFacettes();

	sauverFichier("test1.off");

	//system("pause");

	// initialisation  des paramètres de GLUT en fonction
	// des arguments sur la ligne de commande
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// définition et création de la fenêtre graphique
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Primitives graphiques");

	// initialisation de OpenGL et de la scène
	initGL();
	init_scene();

	// choix des procédures de callback pour 
	// le tracé graphique
	glutDisplayFunc(&window_display);
	// le redimensionnement de la fenêtre
	glutReshapeFunc(&window_reshape);
	// la gestion des événements clavier
	glutKeyboardFunc(&window_key);
	glutIdleFunc(&window_idle);
	// la boucle prinicipale de gestion des événements utilisateur
	glutMainLoop();

	return 1;
}