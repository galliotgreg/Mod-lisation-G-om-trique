#include "struct.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct sMaillage 
{
	int nbSommets;
	int nbFacettes;
	int nbAretes;
	vector<point3> sommets;
	vector<vector<long>> facettes;
} maillage;

string nbSom, nbFac, nbAre;

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
		}
		else if (i == 2) {
			point.y = stof(token);
		}
		else {
			cout << "Problème avec le point" << i+2 << endl;
		}
		i++;
		ligne.erase(0, pos + delimiter.length());
	}
	point.z = stof(ligne);
	return point;
}

vector<long> creationFacette(string ligne) {
	size_t pos = 0;
	string delimiter = " ";
	string token;
	int i = 1;
	vector<long> facette;

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


int main() {

	string fichier = "buddha.off";
	//string fichier = "test.off";

	ouvertureFichier(fichier);

	cout << "Sommets : " << nbSom << ", Facettes :"<< nbFac << ", Arettte :" << nbAre << endl;

	maillage.nbSommets = stoi(nbSom);
	maillage.nbFacettes = stoi(nbFac);
	maillage.nbAretes = stoi(nbAre);

	stockage(fichier);
	
	
	system("pause");
}