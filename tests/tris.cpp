/*
 *
 * Fonctions de tris qui vont être utilisées
 * lors de notre test de performance
 *
 * Un tri par sélection
 * Un tri rapie
 * Un tri par comptage
 */


// Tri par sélection
template <typename RandomAccessIterator>
void selectionSort(RandomAccessIterator begin, RandomAccessIterator end);


// Tri rapide
template <typename RandomAccessIterator>
void quickSort(RandomAccessIterator begin, RandomAccessIterator end);

// Tri par comptage
template <typename RandomAccessIterator>
void countingSort(RandomAccessIterator begin, RandomAccessIterator end);



// IMPLEMENTATION

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
