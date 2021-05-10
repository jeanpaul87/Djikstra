/*
 * Fichier: Vehicule.cpp
 * Auteur: Roy Boutros
 *         Jean-Paul Khoueiry
 * Date: 3 novembre 2020
 * Description: Implementation de la classe Vehicule.
 */

#include "Vehicule.h"

Vehicule::Vehicule() {}

Vehicule::Vehicule(const string& type, int autonomieComplete, int autonomieRestante) : type_(type),
autonomieComplete_(autonomieComplete),
autonomieRestante_(autonomieRestante)
{}

Vehicule::Vehicule(const Vehicule& vehicule) : type_(vehicule.type_),
autonomieComplete_(vehicule.autonomieComplete_),
autonomieRestante_(vehicule.autonomieRestante_)
{}

void Vehicule::setAutonomieComplete(int autonomie)
{
	autonomieComplete_ = autonomie;
}

void Vehicule::setAutonomieRestante(int autonomie)
{
	autonomieRestante_ = autonomie;
}

void Vehicule::setType(const string& type)
{
	type_ = type;
}

void Vehicule::plein()
{
	autonomieRestante_ = autonomieComplete_;
}

bool Vehicule::deplacement(int distance)
{
	if (autonomieRestante_ -= distance < 0) {
		return false;
	}
	else {
		return true;
	}
}

const string& Vehicule::getType() const
{
	return type_;
}

int Vehicule::getAutonomieComplete() const
{
	return autonomieComplete_;
}

int Vehicule::getAutonomieRestante() const
{
	return autonomieRestante_;
}
int Vehicule::getPourcentageAutonomieRestante() const
{
	float resultat = (float)getAutonomieRestante() / (float)getAutonomieComplete();
	if (resultat < 0)
		resultat = 0;
	return (resultat * 100);
}