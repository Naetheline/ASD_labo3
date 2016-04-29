/*
 * ASD : Labo 3
 * 
 * Auteurs : Lara Chauffoureaux, Marie Lemdjo, Nathalie Mégevand
 * Date : 29.04.2016
 * Fichier Source : tris.cpp
 */

#include <utility>
#include <vector>

template < typename RandomAccessIterator >
void selectionSort( RandomAccessIterator begin,
                   RandomAccessIterator end )
{   
   for(auto i = begin; i < end - 1; i++)
   {
      RandomAccessIterator iMin = i;
      
      for(auto j = i + 1; j < end; j++)
      {
         if(*j < *iMin)
         {
            iMin = j;
         }
      }
      if(iMin != i)
      {
         std::swap(*i, *iMin);
      }
   }
}

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
   } else {
      if (*p1 < *p3) return p1;
      else if (*p2 < *p3) return p3;
      return p2;
   }
}

template < typename RandomAccessIterator >
RandomAccessIterator partitionner(RandomAccessIterator begin,
        RandomAccessIterator end) {
   
   RandomAccessIterator i = begin-1;
   RandomAccessIterator j = end;
   
   while (1) {
      do{
         i++;
      }while (*i < *end);//Vérifie que les élements à gauche du pivot sont inférieurs
      do{  
        j--; 
      }while (j > begin and *j > *end);//Vérifie que les élements à droite du pivot sont supérieurs
         
      if (i >= j)
         break;
      swap(*i, *j);
   }
   swap(*i, *end);
   return i;
}

template < typename RandomAccessIterator >
void quickSort(RandomAccessIterator begin,
        RandomAccessIterator end) {
   
   RandomAccessIterator i ;
   RandomAccessIterator j ;
   RandomAccessIterator hi= end-1;

   
   if (end <= begin)//Condition d'arret
      return;
   
   RandomAccessIterator pivot = selectPivot(begin, end); //Choisit l'élément pivot
   std::swap(*pivot, *hi); //permute l'élement pivot avec le dernier élément de la liste 
  
   i = begin-1;
   j = hi;   
   while (1) {
      do{
         ++i;
      }while (*i < *hi);/*Vérifie que les élements à 
                          gauche du pivot sont inférieurs*/
      do{  
        --j; 
      }while (j > begin and *j > *hi);/*Vérifie que les élements 
                                       à droite du pivot sont supérieurs*/
         
      if (i >= j)
         break;
      std::swap(*i, *j);
   }
   std::swap(*i, *hi);//Echange deux élements pointés par i et hi    
   quickSort(begin,i);
   quickSort(i+1, end);
}

template < typename RandomAccessIterator >
void countingSort( RandomAccessIterator begin,
                  RandomAccessIterator end )
{
  auto min = *begin;
  auto max = *begin;

  // Détermination MIN et MAX
  for(auto i = begin; i != end; i++)
    {
      if(*i < min)
	{
	  min = *i;
	}
      else if(*i > max)
	{
	  max = *i;
	}
    }
  const unsigned int TAILLE = max - min + 1;
  std::vector<unsigned int> tabCompte;
  tabCompte.resize(TAILLE);

  // Comptage
    for(auto i = begin; i != end; i++)
      {
	tabCompte.at(*i - min)++;
      }

   // Tri du tableau
     unsigned int k = 0;
     for(unsigned int i = 0; i < TAILLE; i++)
      {
	for(unsigned int j = 0; j < tabCompte.at(i); j++)
         {
           *(begin + k++) = i + min;
         }
      }
}
