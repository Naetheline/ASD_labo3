/*
 * ASD : Labo 3
 * 
 * Auteurs : Lara Chauffoureaux, Marie Lemdjo, Nathalie Mégevand
 * Date : 22.04.2016
 * Fichier source : main.cpp
 * 
 * Test empiriquement les différents temps moyens
 * mis par les différents tris pour trier des tableaux
 * de taille différentes
 */


#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>

#include "tris.h"

using namespace std;

using time_point  = chrono::high_resolution_clock::time_point;
// using now() = chrono::high_resolution_clock::now();
// using nano  = duration_cast<chrono::nanoseconds>;

int main()
{
  const unsigned int NB_SIMULATIONS = 30;
  const unsigned int MAX_VALUE      = 100;

  cout << "Taille\tTemps selection\tTemps rapide\tTemps comptage"
       << endl;

  // Variation de la taille des tableaux à trier
  for(unsigned int m = 1; m < 8; m++)
    {
      const size_t SIZE =  pow(10, m);
      srand(m);

      double avgTimeSelct = 0;
      double avgTimeQuick = 0;
      double avgTimeCount = 0;

      time_point before;
      time_point after;
      
      for(unsigned int i = 0; i < NB_SIMULATIONS; i++)
	{
	  
	  vector<int> vector1;
	  vector<int> vector2;
	  vector<int> vector3;

	  vector1.resize(m);
	  vector2.resize(m);
	  vector3.resize(m);

	  // Remplissage
	  for(size_t j = 0; j < SIZE; j++)
	    {
	      int element = rand() % MAX_VALUE + 1;
	      vector1.push_back(element);
	      vector2.push_back(element);
	      vector3.push_back(element);
	    }

	  
	  // Tris

	  // Selection
	  before = chrono::high_resolution_clock::now();
	  selectionSort(vector1.begin(), vector1.end());
	  after = chrono::high_resolution_clock::now();
	  avgTimeSelct +=
	    chrono::duration_cast<chrono::nanoseconds>(after - before).count();

	  // Rapide
	  before = chrono::high_resolution_clock::now();
	  quickSort(vector2.begin(), vector2.end());
	  after = chrono::high_resolution_clock::now();
	  avgTimeQuick +=
	    chrono::duration_cast<chrono::nanoseconds>(after - before).count();

	  // Comptage
	  before = chrono::high_resolution_clock::now();
	  countingSort(vector3.begin(), vector3.end());
	  after = chrono::high_resolution_clock::now();
	  avgTimeCount +=
	    chrono::duration_cast<chrono::nanoseconds>(after - before).count(); 
	}
      cout << m << "\t" << avgTimeSelct / NB_SIMULATIONS
	   << "\t" << avgTimeQuick / NB_SIMULATIONS
	   << "\t" << avgTimeCount / NB_SIMULATIONS << endl;
    }

  return EXIT_SUCCESS;
}
