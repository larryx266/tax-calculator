#include "taxCalculator.h"

using namespace std;


int main (int argc, char** argv) {
    taxCalculator calc;
	unsigned int filingStatus;
	string incomeAsString;
	double income;
	string effectiveStateIncome;
	string effectiveFederalIncome;
	int stateDeduction = 0;
	int federalDeduction = 0;
	string stateDeductionString = "$0.000";
	string federalDeductionString = "$0.000";
	double stateTax;
	double federalTax;
	double totalTax;
	char userInput;
	fstream fileDump;
	string fileName;
	bool dump = false;

	cout << "Larry is not liable for any loss, damage, or responsibility that arises from use of this program" << endl;
	cout << endl << "How will you be filing? " << endl;
	cout << "Enter a Number" << endl;
	cout << "   1) Single" << endl << "   2) Married, Filing Jointly" << endl;
	cout << "   3) Head of Household" << endl << "   4) Married, Filing Separately" << endl;
	cin >> filingStatus;
	if (cin.fail() || filingStatus > 4 || filingStatus == 0){
		cout << "Enter a valid option" << endl;
		return -1;
	}
	filingStatus--;

	cout << endl << "Please Enter Your Total Taxable Income: ";
	cin >> incomeAsString;

	income = calc.inputIncomeToDouble(incomeAsString);
	if (income == -1) return -1;
	if (income <= 100000) {
		cout << "Come back when you make more money (> $100,000)" << endl << endl;
		return 0;
	}

	cout << endl << "Would you like to apply standard deductions?" << endl;
	cout << "Enter 'y' or 'n': ";
	cin >> userInput;

	if (userInput == 'Y' || userInput == 'y'){
		stateDeduction = calc.californiaStandardDeductions[filingStatus % 3];
		federalDeduction = calc.federalStandardDeductions[filingStatus % 3];
		stateDeductionString = calc.moneyAmountToString(stateDeduction);
		federalDeductionString = calc.moneyAmountToString(federalDeduction);
	}

	cout << "Would you like to review the calculations?" << endl;
	cout << "Enter 'y' or 'n': ";
	cin >> userInput;
	while (userInput == 'y' || userInput == 'Y'){
		cout << endl << "Please enter a file name for data. It will be saved as a txt file: ";
		cin >> fileName;
		//string tempPath = "C:\\Users\\larry\\Desktop\\";
		string tempPath = "";
		fileDump.open(tempPath + fileName + ".txt", ios::out);
		if (fileDump.fail()){
			cout << "Could not create file" << endl;
			cout << "Would you like to try again?" << endl;
			cout << "Enter 'y' or 'n': ";
			cin >> userInput;
			continue;
		}
		break;
	}

	if (userInput == 'y' || userInput == 'Y'){
		dump = true;
		fileDump << "***Calculations***" << endl << endl;
	}
	effectiveStateIncome = calc.moneyAmountToString(income - stateDeduction);
	effectiveStateIncome = effectiveStateIncome.substr(0, effectiveStateIncome.size() - 1);
	effectiveFederalIncome = calc.moneyAmountToString(income - federalDeduction);
	effectiveFederalIncome = effectiveFederalIncome.substr(0, effectiveFederalIncome.size() - 1);

	stateTax = calc.californiaFiling(income - stateDeduction, filingStatus % 3, fileDump, dump);
	federalTax = calc.federalFiling(income - federalDeduction, filingStatus, fileDump, dump);
	totalTax = stateTax + federalTax;
	incomeAsString = calc.moneyAmountToString(income);

	cout << endl << "Thank You" << endl;
	cout << endl << "Generating Your Report... " << endl << endl;
	usleep(650000);

	cout << "--------------------------------------------------------------" << endl << endl;
	cout << "Your Total Taxable Income was: " << incomeAsString.substr(0, incomeAsString.size() - 1) << endl;
	cout << "Your Filing Status was: " << calc.filingStatuses[filingStatus] << endl << endl;
	usleep(250000);
	cout << "Your California State Standard Deduction is: " << stateDeductionString.substr(0, stateDeductionString.size() - 1) << endl;
	cout << "Your Effective California State Income is: " << effectiveStateIncome << endl;
	cout << "Your California State Income Tax is: " << calc.moneyAmountToString(stateTax) << endl << endl;
	usleep(50000);
	cout << "Your Federal Standard Deduction is: " << federalDeductionString.substr(0, federalDeductionString.size() - 1) << endl;
	cout << "Your Effective Federal Income is: " << effectiveFederalIncome << endl;
	cout << "Your Federal Income Tax is: " << calc.moneyAmountToString(federalTax) << endl << endl;
	usleep(30000);
	cout << "***Your Total Income Tax is: " << calc.moneyAmountToString(totalTax) << "***" << endl;
	usleep(20000);
	cout << "You will be taxed " << fixed << setprecision(2) << totalTax * 100 / income << "% of your total income" << endl;
	cout << "Please round the decimal points accordingly" << endl << endl;
	cout << "--------------------------------------------------------------" << endl << endl;

	if (dump){
		fileDump << endl << "--------------------------------------------------------------" << endl;
		fileDump << "***Report***" << endl << endl;
		fileDump << "Your Total Taxable Income was: " << incomeAsString.substr(0, incomeAsString.size() - 1) << endl;
		fileDump << "Your Filing Status was: " << calc.filingStatuses[filingStatus] << endl << endl;
		fileDump << "Your California State Standard Deduction is: " << stateDeductionString.substr(0, stateDeductionString.size() - 1) << endl;
		fileDump << "Your Effective California State Income is: " << effectiveStateIncome << endl;
		fileDump << "Your California State Income Tax is: " << calc.moneyAmountToString(stateTax) << endl << endl;
		fileDump << "Your Federal Standard Deduction is: " << federalDeductionString.substr(0, federalDeductionString.size() - 1) << endl;
		fileDump << "Your Effective Federal Income is: " << effectiveFederalIncome << endl;
		fileDump << "Your Federal Income Tax is: " << calc.moneyAmountToString(federalTax) << endl << endl;
		fileDump << "***Your Total Income Tax is: " << calc.moneyAmountToString(totalTax) << "***" << endl;
		fileDump << "You will be taxed " << fixed << setprecision(2) << totalTax * 100 / income << "% of your total income" << endl;
		fileDump << "Please round the decimal points accordingly" << endl << endl;
		fileDump << "--------------------------------------------------------------" << endl << endl;
	}

	usleep(400000);
    if (dump) {
	    cout << endl << "File successfully written" << endl;
	    cout << "File saved at application location" << endl << endl;
    }

	cout << "Press Enter to exit" << endl;
	cin.clear();
	cin.sync();
	cin.get();
	return 0;
}
