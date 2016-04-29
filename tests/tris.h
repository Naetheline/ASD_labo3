/*
 * ASD : Labo 3
 * 
 * Auteurs : Lara Chauffoureaux, Marie Lemdjo, Nathalie Mégevand
 * Date : 22.04.2016
 * Fichier SourceEn-tête : tris.h
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

#include "tris_implementation.h"
