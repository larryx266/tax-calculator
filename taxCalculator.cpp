#include "taxCalculator.h"

using namespace std;

taxCalculator::taxCalculator() { }

double taxCalculator::inputIncomeToDouble(string preParsedIncome){
	string temp = "";
	bool decimalFlag = false;
	for (unsigned int i = 0; i < preParsedIncome.size(); i++){
		if (preParsedIncome[i] > 57 || 
			(preParsedIncome[i] < 48 && preParsedIncome[i] != 46 && preParsedIncome[i] != 44 && preParsedIncome[i] != 36)){
			cout << "Please enter a valid income number" << endl << endl;
			return -1;
		}

		if (preParsedIncome[i] == 46){
			if (decimalFlag){
				cout << "Please enter a valid income number" << endl << endl;
				return -1;
			}
			else decimalFlag = true;
		}

		if (preParsedIncome[i] != 36 && preParsedIncome[i] != 44) temp += preParsedIncome[i];
	}

	return stod(temp);
}

//adds all possible tax from each incremental bracket, subtracts anything extra at the end
double taxCalculator::californiaFiling(double income, unsigned int filingStatus, ostream& file, bool dump){
	double tax = 0;
	int i;
	if (dump) file << "**California State Tax**" << endl;

	for (i = 0; i < 9; i++){
		if (income <= 0) break;

		if (i == 8){ //when maxed, apply highest bracket on remaining income
			tax += income * californiaTaxBracketPercentages[8];
			if (dump){
				file << "Amount taxed at " << californiaTaxBracketPercentages[8] * 100 << "% ";
				file << "from ";
				file << moneyAmountToString(californiaTaxBrackets[filingStatus][8] + 0.01).substr(0, moneyAmountToString(californiaTaxBrackets[filingStatus][8]).size() - 1);
				file << " to MAX: ";
				file << moneyAmountToString(income).substr(0, moneyAmountToString(income).size() - 1) << ", resulting in ";
				file << moneyAmountToString(income * californiaTaxBracketPercentages[6]);
				file << " from this tax bracket" << endl;
			}
			income = 0;
		}

		else{
			double taxAtBracket = californiaTaxBrackets[filingStatus][i + 1] - californiaTaxBrackets[filingStatus][i];
			income -= taxAtBracket;
			tax += taxAtBracket * californiaTaxBracketPercentages[i];
			if (dump){
				if (income < 0){
					file << "Amount taxed at " << californiaTaxBracketPercentages[i] * 100 << "%: ";
					file << "from ";
					file << moneyAmountToString(californiaTaxBrackets[filingStatus][i] + 0.01).substr(0, moneyAmountToString(californiaTaxBrackets[filingStatus][i]).size() - 1);
					file << " to ";
					file << moneyAmountToString(californiaTaxBrackets[filingStatus][i + 1]).substr(0, moneyAmountToString(californiaTaxBrackets[filingStatus][i + 1]).size() - 1);
					file << ": ";
					file << moneyAmountToString(income + taxAtBracket).substr(0, moneyAmountToString(income + taxAtBracket).size() - 1) << ", resulting in ";
					file << moneyAmountToString((income + taxAtBracket) * californiaTaxBracketPercentages[i]);
					file << " from this tax bracket" << endl;
				}
				else{
					file << "Amount taxed at " << californiaTaxBracketPercentages[i] * 100 << "%: ";
					file << "from ";
					file << moneyAmountToString(californiaTaxBrackets[filingStatus][i] + 0.01).substr(0, moneyAmountToString(californiaTaxBrackets[filingStatus][i]).size() - 1);
					file << " to ";
					file << moneyAmountToString(californiaTaxBrackets[filingStatus][i + 1]).substr(0, moneyAmountToString(californiaTaxBrackets[filingStatus][i + 1]).size() - 1);
					file << ": ";
					file << moneyAmountToString(taxAtBracket).substr(0, moneyAmountToString(taxAtBracket).size() - 1) << ", resulting in ";
					file << moneyAmountToString(taxAtBracket * californiaTaxBracketPercentages[i]);
					file << " from this tax bracket" << endl;
				}
			}
		}
	}

	tax += income * californiaTaxBracketPercentages[i - 1]; //subtracting back if we added too much (income is negative or zero)
	return tax;
}

double taxCalculator::federalFiling(double income, unsigned int filingStatus, ostream& file, bool dump){
	double tax = 0;
	int i;
	if (dump) file << endl << "**Federal Tax**" << endl;

	for (i = 0; i < 7; i++){
		if (income <= 0) {
			break;
		}

		if (i == 6){ //different when maxed
			tax += income * federalTaxBracketPercentages[6];
			if (dump){
				file << "Amount taxed at " << federalTaxBracketPercentages[6] * 100 << "% ";
				file << "from ";
				file << moneyAmountToString(federalTaxBrackets[filingStatus][6] + 0.01).substr(0, moneyAmountToString(federalTaxBrackets[filingStatus][6]).size() - 1);
				file << " to MAX: ";
				file << moneyAmountToString(income).substr(0, moneyAmountToString(income).size() - 1) << ", resulting in ";
				file << moneyAmountToString(income * federalTaxBracketPercentages[6]);
				file << " from this tax bracket" << endl;
			}
			income = 0;
		}

		else{
			double taxAtBracket = federalTaxBrackets[filingStatus][i + 1] - federalTaxBrackets[filingStatus][i];
			income -= taxAtBracket;
			tax += taxAtBracket * federalTaxBracketPercentages[i];
			if (dump){
				if (income < 0){
					file << "Amount taxed at " << federalTaxBracketPercentages[i] * 100 << "%: ";
					file << "from ";
					file << moneyAmountToString(federalTaxBrackets[filingStatus][i] + 0.01).substr(0, moneyAmountToString(federalTaxBrackets[filingStatus][i]).size() - 1);
					file << " to ";
					file << moneyAmountToString(federalTaxBrackets[filingStatus][i + 1]).substr(0, moneyAmountToString(federalTaxBrackets[filingStatus][i + 1]).size() - 1);
					file << ": ";
					file << moneyAmountToString(income + taxAtBracket).substr(0, moneyAmountToString(income + taxAtBracket).size() - 1) << ", resulting in ";
					file << moneyAmountToString((income + taxAtBracket) * federalTaxBracketPercentages[i]);
					file << " from this tax bracket" << endl;
				}
				else{
					file << "Amount taxed at " << federalTaxBracketPercentages[i] * 100 << "%: ";
					file << "from ";
					file << moneyAmountToString(federalTaxBrackets[filingStatus][i] + 0.01).substr(0, moneyAmountToString(federalTaxBrackets[filingStatus][i]).size() - 1);
					file << " to ";
					file << moneyAmountToString(federalTaxBrackets[filingStatus][i + 1]).substr(0, moneyAmountToString(federalTaxBrackets[filingStatus][i + 1]).size() - 1);
					file << ": ";
					file << moneyAmountToString(taxAtBracket).substr(0, moneyAmountToString(taxAtBracket).size() - 1) << ", resulting in ";
					file << moneyAmountToString(taxAtBracket * federalTaxBracketPercentages[i]);
					file << " from this tax bracket" << endl;
				}
			}
		}
	}

	tax += income * federalTaxBracketPercentages[i - 1]; //subtracting back if we added too much (income is negative or zero)
	return tax;
}

string taxCalculator::moneyAmountToString(double tax){
	string result = to_string(tax);
	int size = 0;
	for (unsigned int i = 0; i < result.size(); i++){
		if (result[i] == 46){
			size += 4;
			break;
		}
		size++;
	}

	int commasAdded = 0;
	int count = size - 7;
	while (count > 0){
		result.insert(count, ",");
		commasAdded++;
		count -= 3;
	}

	result = result.substr(0, size + commasAdded);
	result.insert(0, "$");

	return result;
}