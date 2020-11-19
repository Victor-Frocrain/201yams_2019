/*
** EPITECH PROJECT, 2020
** yams
** File description:
** yams.cpp
*/

#include "../include/yams.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

void dispHelp()
{
    std::ifstream fs("help");

    if (!fs.fail()) {
        std::cout << fs.rdbuf() << std::endl;
    }
}

bool parseCombination(std::string type, std::string expected)
{
    if (expected.find(type) != 0)
        return false;
    if ((type != "full" && expected.length() != type.length() + 2) || (type == "full" && expected.length() != type.length() + 4))
        return false;
    if (expected[type.length()] != '_')
        return false;
    if (expected[type.length() + 1] < '1' || expected[type.length() + 1] > '6')
        return false;
    if (type == "full" && (expected[expected.length() - 1] < '1' || expected[expected.length() - 1] > '6'))
        return false;
    if (type == "straight" && expected[expected.length() - 1] != '5' && expected[expected.length() - 1] != '6')
        return false;
    return true;
}

void computeYams(int dices[], int value)
{
    double result = 0;
    int n = 5;

    for (int i = 0; i < 6; i++) {
        if (dices[i] == value)
            n--;
    }
    result = (1 / std::pow(6, n)) * 100;
    std::cout << "Chances to get a " << std::to_string(value) << " yams: " << std::fixed << std::setprecision(2) << result << "%" << std::endl;
}

double fact(double value)
{
    double result = 1;

    for (int i = 1; i <= value; i++)
        result *= i;
    return result;
}

double binomy(int a, int b)
{
    double result = 0;

    result = (fact(a) / (fact(b) * fact(a - b))) * std::pow(1.0 / 6.0, b) * std::pow(5.0 / 6.0, a - b);
    return result;
}

void computeFull(int dices[], int value1, int value2)
{
    double result = 0;
    double tmp = 0;
    double nb1 = 0;
    double nb2 = 0;

    for (int i = 0; i < 5; i++) {
        if (dices[i] == value1 && nb1 < 3) {
            nb1++;
        }
        else if (dices[i] == value2 && nb2 < 2) {
            nb2++;
        }
    }
    if (2 - nb2 > 3 - nb1)
        result = fact(5 - nb2 - nb1) / (fact(2 - nb2) * fact((5 - nb2 - nb1) - (2 - nb2)));
    else
        result = fact(5 - nb2 - nb1) / (fact(3 - nb1) * fact((5 - nb2 - nb1) - (3 - nb1)));
    tmp = (3 - nb1) + (2 - nb2);
    while (tmp > 0) {
        result *= (1.0 / 6.0);
        tmp--;
    }
    result *= 100;
    std::cout << "Chances to get a " << std::to_string(value1) << " full of " << std::to_string(value2) << ": " << std::fixed << std::setprecision(2) << result << "%" << std::endl;
}

int seekNumber(int dices[], int nb)
{
    int result = 0;

    for (int i = 0; i < 5; i++) {
        if (dices[i] == nb) {
            result++;
            break;
        }
    }
    return result;
}

void computeStraight(int dices[], int value)
{
    int nbOcc = 0;
    double result = 0;

    if (value == 6)
        nbOcc = seekNumber(dices, 2) + seekNumber(dices, 3) + seekNumber(dices, 4) + seekNumber(dices, 5) + seekNumber(dices, 6);
    else
        nbOcc = seekNumber(dices, 1) + seekNumber(dices, 2) + seekNumber(dices, 3) + seekNumber(dices, 4) + seekNumber(dices, 5);
    if (nbOcc == 5)
        result = 100;
    else
        result = fact(5 - nbOcc) / std::pow(6, 5 - nbOcc) * 100;
    std::cout << "Chances to get a " << std::to_string(value) << " straight: " << std::fixed << std::setprecision(2) << result << "%" << std::endl;
}

double computeChances(int dices[], int type, int value)
{
    double result = 0;
    int nb = 0;

    for (int i = 0; i < 5; i++) {
        if (dices[i] == value)
            nb++;
    }
    if (nb >= type)
        result = 100;
    else {
        for (int i = type - nb; i < 5 - nb + 1; i++)
            result += binomy(5.0 - nb, i);
        result *= 100;
    }
    return result;
}

void computeFour(int dices[], int value)
{
    double result = computeChances(dices, 4, value);

    std::cout << "Chances to get a " << std::to_string(value) << " four-of-a-kind: " << std::fixed << std::setprecision(2) << result << "%" << std::endl;
}

void computePair(int dices[], int value)
{
    double result = computeChances(dices, 2, value);

    std::cout << "Chances to get a " << std::to_string(value) << " pair: " << std::fixed << std::setprecision(2) << result << "%" << std::endl;
}

void computeThree(int dices[], int value)
{
    double result = computeChances(dices, 3, value);

    std::cout << "Chances to get a " << std::to_string(value) << " three-of-a-kind: " << std::fixed << std::setprecision(2) << result << "%" << std::endl;
}

int computeProbs(int dices[], std::string expected)
{
    std::string type = "";
    int values[2] = { 0, 0 };

    for (size_t i = 0, j = 0; i < expected.length(); i++) {
        if ((expected[i] < '1' || expected[i] > '6') && expected[i] != '_')
            type += expected[i];
        else if (expected[i] >= '1' && expected[i] <= '6') {
            if (j > 1)
                return MY_ERROR;
            values[j] = expected[i] - '0';
            j++;
        }
    }
    if (!parseCombination(type, expected))
        return MY_ERROR;
    if (type == "yams")
        computeYams(dices, values[0]);
    else if (type == "full" && values[0] != values[1])
        computeFull(dices, values[0], values[1]);
    else if (type == "straight")
        computeStraight(dices, values[0]);
    else if (type == "four")
        computeFour(dices, values[0]);
    else if (type == "pair")
        computePair(dices, values[0]);
    else if (type == "three")
        computeThree(dices, values[0]);
    else
        return MY_ERROR;
    return MY_SUCCESS;
}

int parse_args(std::string args[], int *dices)
{
    int result = MY_SUCCESS;
    bool thrown = true;

    for (int i = 0; i < 5; i++) {
        if (args[i].length() != 1 || args[i][0] < '0' || args[i][0] > '6') {
            result = MY_ERROR;
            break;
        }
        dices[i] = std::stoi(args[i]);
        if (dices[i] == 0)
            thrown = false;
    }
    for (int i = 0; i < 5; i++) {
        if (dices[i] != 0 && thrown == false)
            result = MY_ERROR;
    }
    return result;
}

int yams(int ac, char **args)
{
    int result = MY_SUCCESS;
    int dices[5] = { 0, 0, 0, 0, 0 };

    if (ac < 2)
        result = MY_ERROR;
    else if (ac == 2) {
        std::string arg(args[1]);
        if (arg == "-h")
            dispHelp();
    }
    else if (ac == 7) {
        std::string argi[6];
        for (int i = 0; i < 6; i++)
            argi[i] = args[i + 1];
        result = parse_args(argi, dices);
        if (result == MY_SUCCESS)
            result = computeProbs(dices, argi[5]);
    }
    else
        result = MY_ERROR;
    return result;
}