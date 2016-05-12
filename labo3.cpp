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

using namespace std;

using time_point = chrono::high_resolution_clock::time_point;
// using now() = chrono::high_resolution_clock::now();
// using nano  = chrono::duration_cast<chrono::nanoseconds>;

// Tri par sélection
template < typename RandomAccessIterator >
void selectionSort(RandomAccessIterator begin, RandomAccessIterator end) {
   
   for (auto i = begin; i < end - 1; i++) {
      
      RandomAccessIterator iMin = i;
      for (auto j = i + 1; j < end; j++) {
         
         if (*j < *iMin) {
            iMin = j;
         }
      }
      
      if (iMin != i) {
         swap(*i, *iMin);
      }
   }
}

// Fonction de choix du pivot (quicksort)
template < typename RandomAccessIterator >
RandomAccessIterator selectPivot(const RandomAccessIterator begin,
                                 const RandomAccessIterator end) {
   
   RandomAccessIterator p1 = begin;
   RandomAccessIterator p2 = begin + (end - begin) / 2;
   RandomAccessIterator p3 = end - 1;

   if (*p1 < *p2) {
      
      if (*p2 < *p3) return p2;
      else if (*p1 < *p3) return p3;
      return p1;
   }
   else {
      
      if (*p1 < *p3) return p1;
      else if (*p2 < *p3) return p3;
      return p2;
   }
}

//Fonction de partionnage (quicksort)
template < typename RandomAccessIterator >
RandomAccessIterator partitionner(RandomAccessIterator begin,
                                  RandomAccessIterator end) {
   
   RandomAccessIterator i = begin - 1;
   RandomAccessIterator j = end;

   while (1) {
      do {
         i++;
      } while (*i < *end); //Vérifie que les élements à gauche du pivot sont inférieurs
      
      do {
         j--;
      } while (j > begin and *j > *end); //Vérifie que les élements à droite du pivot sont supérieurs

      if (i >= j) {
         break;
      }
      
      swap(*i, *j);
   }

   swap(*i, *end);
   return i;
}

//Tri rapide
template < typename RandomAccessIterator >
void quickSort(RandomAccessIterator begin, RandomAccessIterator end) {
   
   RandomAccessIterator i;
   RandomAccessIterator j;
   RandomAccessIterator hi = end - 1;

   if (end <= begin) { //Condition d'arret
      
      return;
   }

   RandomAccessIterator pivot = selectPivot(begin, end); //Choisit l'élément pivot
   swap(*pivot, *hi); //permute l'élement pivot avec le dernier élément de la liste 

   i = begin - 1;
   j = hi;

   while (1) {
      
      do {
         ++i;
      } while (*i < *hi); /* Vérifie que les élements à 
                             gauche du pivot sont inférieurs*/
      do {
         --j;
      } while (j > begin and *j > *hi); /* Vérifie que les élements 
                                           à droite du pivot sont supérieurs*/

      if (i >= j)  {
         break;
      }
      
      swap(*i, *j);
   }
   
   swap(*i, *hi); //Echange deux élements pointés par i et hi    
   quickSort(begin, i);
   quickSort(i + 1, end);
}

//Tri par comptage
template < typename RandomAccessIterator >
void countingSort(RandomAccessIterator begin, RandomAccessIterator end) {
   
   auto min = *begin;
   auto max = *begin;

   // Détermination MIN et MAX
   for (auto i = begin; i != end; i++) {
      
      if (*i < min) {
         min = *i;
      } 
      else if (*i > max) {
         max = *i;
      }
   }
   
   const unsigned int TAILLE = max - min + 1;
   vector<unsigned int> tabCompte;
   tabCompte.resize(TAILLE);

   // Comptage
   for (auto i = begin; i != end; i++) {
      
      tabCompte.at(*i - min)++;
   }

   // Tri du tableau
   unsigned int k = 0;
   for (unsigned int i = 0; i < TAILLE; i++) {
      for (unsigned int j = 0; j < tabCompte.at(i); j++) {
         
         *(begin + k++) = i + min;
      }
   }
}

//Fonction de test empirique sur les données
int main() {
   const unsigned int NB_SIMULATIONS = 30;
   const unsigned int MAX_VALUE = 100;

   cout << "Taille\tTemps selection\tTemps rapide\tTemps comptage" << endl;

   // Variation de la taille des tableaux à trier
   for (unsigned int m = 1; m < 8; m++) {
      const size_t SIZE = pow(10, m);
      srand(m);

      double avgTimeSelct = 0;
      double avgTimeQuick = 0;
      double avgTimeCount = 0;

      time_point before;
      time_point after;

      for (unsigned int i = 0; i < NB_SIMULATIONS; i++) {

         vector<int> vector1;
         vector<int> vector2;
         vector<int> vector3;

         vector1.resize(m);
         vector2.resize(m);
         vector3.resize(m);

         // Remplissage
         for (size_t j = 0; j < SIZE; j++) {
            
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
      
      cout << SIZE << "\t" << avgTimeSelct / NB_SIMULATIONS
                   << "\t" << avgTimeQuick / NB_SIMULATIONS
                   << "\t" << avgTimeCount / NB_SIMULATIONS << endl;
   }

   return EXIT_SUCCESS;
}
