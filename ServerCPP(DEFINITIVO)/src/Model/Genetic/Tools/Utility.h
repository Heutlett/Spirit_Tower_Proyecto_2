#ifndef SERVER_UTILITY_H
#define SERVER_UTILITY_H


#include <iostream>
#include <ctgmath>
#include <random>

using namespace std;

class Utility {

public:
    /**
     * Retorna un random desde 0 hasta el parametro recibido.
     * @param pMax
     * @return
     */
    static int Random(int pMax);

    /**
     * Retorna un random del valor minimo hasta el valor maximo recibido.
     * @param pMin
     * @param pMax
     * @return
     */
    static int Random(int pMin, int pMax);

    /**
     * Convierte un numero de decimal a binario.
     * @param pDecimal
     * @return result
     */
    static string decToBinary(int pDecimal);

    /**
     * Convierte un numero de pBinary a decimal.
     * @param pBinary
     * @return resultado
     */
    static int binToDec(int pBinary);

    /**
     * Receive a string and split it based on given delimiter.
     * @param pString
     * @return
     */
    static vector<string> split(string pString, const string& delimiter);
};




#endif //SERVER_UTILITY_H
