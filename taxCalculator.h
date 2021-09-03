#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <unistd.h>
#include <fstream>

class taxCalculator {
public:
    taxCalculator();
    double inputIncomeToDouble(std::string preParsedIncome); //input parser
    double californiaFiling(double income, unsigned int filingStatus, std::ostream& file, bool dump); //calculates california state tax
    double federalFiling(double income, unsigned int filingStatus, std::ostream& file, bool dump); //calculates federal tax
    std::string moneyAmountToString(double tax); //converts double to printable money format
    unsigned int californiaTaxBrackets[3][9] = {{0, 8932, 21175, 33421, 46394, 58634, 299508, 359407, 599012}, //single or married filing separately
											    {0, 17864, 42350, 66842, 92788, 117268, 599016, 718814, 1198024}, //married filing jointly
											    {0, 17876, 42353, 54597, 67569, 79812, 407329, 488796, 814658}}; //head of household
    double californiaTaxBracketPercentages[9] = {0.01, 0.02, 0.04, 0.06, 0.08, 0.093, 0.103, 0.113, 0.123};
    int californiaStandardDeductions[3] = {4601, 9202, 9202}; //single, married, head of household
    unsigned int federalTaxBrackets[4][7] = {{0, 9950, 40525, 86375, 164925, 209425, 523600}, //single
										    {0, 19900, 81050, 172750, 329850, 418850, 628300}, //married filing jointly
										    {0, 14200, 54200, 86350, 164900, 209400, 523600}, //head of household
										    {0, 9950, 40525, 86375, 164925, 209425, 314150}}; //married filing separately
    double federalTaxBracketPercentages[7] = {0.1, 0.12, 0.22, 0.24, 0.32, 0.35, 0.37};
    int federalStandardDeductions[3] = {12550, 25100, 18800}; //single, married, head of household
    std::string filingStatuses[4] = {"Single", "Married, Filing Jointly", "Head of Household", "Married, Filing Separately"};
};

