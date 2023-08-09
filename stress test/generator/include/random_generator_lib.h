#ifndef RANDOM_GENERATOR_LIB_H
#define RANDOM_GENERATOR_LIB_H

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <string>
/**
 * @brief there is some functions help to generate random things
 * such as integer, strings, trees, ... and also shuffling.
 *
 * there are more comments explain each function in the .cpp file
 */

// full 32-bit unsigned random number
std::mt19937 random_seed(time(0));

int random32(int, int);
long long random64(long long, long long);

std::string random_huge_number(int);

std::string random_string(int);

template <typename T>
T pick_random(std::vector<T> &);
template <typename T>
T pick_random_and_remove(std::vector<T> &);

std::vector<std::pair<int, int>> random_tree(int, int, int);

std::vector<int> random_permutation(int);

std::string random_binary_string(int);

bool random_flag();

char random_vowel(bool);

std::vector<std::vector<long long>> random_matrix(int, int, long long, long long);

#include "random_generator_lib.cpp"

#endif
