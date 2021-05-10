/*
 * Fichier: Vehicule.h
 * Auteur: Roy Boutros
 *         Jean-Paul Khoueiry
 * Date: 3 novembre 2020
 * Description: Definition la classe Vehicule.
 */

#ifndef VEHICULE_HEADER
#define VEHICULE_HEADER

#include <string>

using namespace std;

class Vehicule
{
public:
	Vehicule();
	Vehicule(const string& type, int autonomieComplete, int autonomieRestante);
	Vehicule(const Vehicule& vehicule);

	void setAutonomieComplete(int autonomie);
	void setAutonomieRestante(int autonomie);
	void setType(const string& type);

	void plein();
	bool deplacement(int distance);

	const string& getType() const;
	int getAutonomieComplete() const;
	int getAutonomieRestante() const;
	int getPourcentageAutonomieRestante() const;


private:
	string type_;
	int autonomieComplete_;
	int autonomieRestante_;
};
#endif