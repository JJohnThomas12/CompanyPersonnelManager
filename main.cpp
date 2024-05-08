#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
class Person
{
private:
 string nam;
 string social;
 string birthDate;
public:
 Person() {}
 Person(string nam, string social, string birthDate)
 : nam(nam), social(social), birthDate(birthDate) {}
 void setNam(string nam) { this->nam = nam; }
 string getNam() const { return nam; }
 void setSocial(string social) { this->social = social; }
 string getSocial() const { return social; }
 void setBirthDate(string birthDate) { this->birthDate = birthDate; }
 string getBirthDate() const { return birthDate; }
 virtual string getCat() const = 0;
};
class Laborer : public Person
{
private:
 string jobs;
 string empId;
 double hourSal;
 double hourWork;
public:
 Laborer() {}
 Laborer(string nam, string social, string birthDate, string jobs, string empId, double hourSal, double hourWork)
 : Person(nam, social, birthDate), jobs(jobs), empId(empId), hourSal(hourSal), hourWork(hourWork) {}
 void setJobs(string jobs) { this->jobs = jobs; }
 string getJobs() const { return jobs; }
 void setEmpId(string empId) { this->empId = empId; }
 string getEmpId() const { return empId; }
 void setHourSal(double hourSal) { this->hourSal = hourSal; }
 double getHourSal() const { return hourSal; }
 void setHourWork(double hourWork) { this->hourWork = hourWork; }
 double getHourWork() const { return hourWork; }
 double calPay() const { return hourSal * hourWork; }
 string getCat() const override { return "Laborer"; }
};
class Manager : public Person
{
private:
 string dep;
 string empId;
 double sal;
public:
 Manager() {}
 Manager(string nam, string social, string birthDate, string dep, string empId, double sal)
 : Person(nam, social, birthDate), dep(dep), empId(empId), sal(sal) {}
 void setDep(string dep) { this->dep = dep; }
 string getDep() const { return dep; }
 void setEmpId(string empId) { this->empId = empId; }
 string getEmpId() const { return empId; }
 void setSal(double sal) { this->sal = sal; }
 double getSal() const { return sal; }
 string getCat() const override { return "Manager"; }
};
class Owner : public Person
{
private:
 double percOwn;
 string dateBecameOwn;
public:
 Owner() {}
 Owner(string nam, string social, string birthDate, double percOwn, string dateBecameOwn)
 : Person(nam, social, birthDate), percOwn(percOwn), dateBecameOwn(dateBecameOwn) {}
 void setPercOwn(double percOwn) { this->percOwn = percOwn; }
 double getPercOwn() const { return percOwn; }
 void setDateBecameOwn(string dateBecameOwn) { this->dateBecameOwn = dateBecameOwn; }
 string getDateBecameOwn() const { return dateBecameOwn; }
 string getCat() const override { return "Owner"; }
};
void displayPeople(const vector<Person*>& people)
{
 cout << "Name\t\tSSN\t\tBirth Date\t\tCategory\n";
 cout << "-----------------------------------------------------------\n";

 for (const auto& person : people)
 {
 cout << left << setw(16) << person->getNam()
 << left << setw(16) << person->getSocial()
 << left << setw(24) << person->getBirthDate()
 << left << person->getCat() << "\n";
 }
 cout << "-----------------------------------------------------------\n";
}
void findPersonByName(const vector<Person*>& people, const string& name)
{
 bool found = false;
 for (const auto& person : people)
 {
 if (person->getNam() == name)
 {
 cout << "Person Found:\n";
 cout << "Name: " << person->getNam() << "\n";
 cout << "SSN: " << person->getSocial() << "\n";
 cout << "Birth Date: " << person->getBirthDate() << "\n";

 if (auto laborer = dynamic_cast<Laborer*>(person))
 {
 cout << "Job: " << laborer->getJobs() << "\n";
 cout << "Employee ID: " << laborer->getEmpId() << "\n";
 cout << "Hourly Salary: $" << laborer->getHourSal() << "\n";
 cout << "Hours Worked: " << laborer->getHourWork() << "\n";
 cout << "Total Earnings: $" << laborer->calPay() << "\n";
 }
 else if (auto manager = dynamic_cast<Manager*>(person))
 {
 cout << "Department: " << manager->getDep() << "\n";
 cout << "Employee ID: " << manager->getEmpId() << "\n";
 cout << "Salary: $" << manager->getSal() << "\n";
 }
 else if (auto owner = dynamic_cast<Owner*>(person))
 {
 cout << "Percentage Owned: " << owner->getPercOwn() << "%\n";
 cout << "Date Became Owner: " << owner->getDateBecameOwn() << "\n";
 }
 found = true;
 break;
 }
 }
 if (!found)
 {
 cout << "Person not found.\n";
 }
}
void removePersonByName(vector<Person*>& people, const string& name)
{
 bool found = false;
 for (auto it = people.begin(); it != people.end(); ++it)
 {
 if ((*it)->getNam() == name)
 {
 delete *it;
 people.erase(it);
 cout << "Person removed.\n";
 found = true;
 break;
 }
 }
 if (!found)
 {
 cout << "Person not found.\n";
 }
}
void calculateAverageEarnings(const vector<Person*>& people)
{
 double totalLaborerEarnings = 0.0;
 double totalManagerEarnings = 0.0;
 int numLaborers = 0;
 int numManagers = 0;
 for (const auto& person : people)
 {
 if (auto laborer = dynamic_cast<Laborer*>(person))
 {
 totalLaborerEarnings += laborer->calPay();
 numLaborers++;
 }
 else if (auto manager = dynamic_cast<Manager*>(person))
 {
 totalManagerEarnings += manager->getSal();
 numManagers++;
 }
 }
 double averageLaborerEarnings = numLaborers > 0 ? totalLaborerEarnings / numLaborers : 0.0;
 double averageManagerEarnings = numManagers > 0 ? totalManagerEarnings / numManagers : 0.0;
 cout << "Average Earnings:\n";
 cout << "Laborers: $" << averageLaborerEarnings << "\n";
 cout << "Managers: $" << averageManagerEarnings << "\n";
}
void loadPeopleFromFile(vector<Person*>& people, const string& filename)
{
 ifstream inputFile(filename);
 if (inputFile.is_open())
 {
 string line;
 while (getline(inputFile, line))
 {
 stringstream ss(line);
 string name, ssn, birthDate, category;
 getline(ss, name, ',');
 getline(ss, ssn, ',');
 getline(ss, birthDate, ',');
 getline(ss, category, ',');
 if (category == "Laborer")
 {
 string jobs, empId, hourSalStr, hourWorkStr;
 getline(ss, jobs, ',');
 getline(ss, empId, ',');
 getline(ss, hourSalStr, ',');
 getline(ss, hourWorkStr);
 double hourSal = stod(hourSalStr);
 double hourWork = stod(hourWorkStr);
 people.push_back(new Laborer(name, ssn, birthDate, jobs, empId, hourSal, hourWork));
 }
 else if (category == "Manager")
 {
 string dep, empId, salStr;
 getline(ss, dep, ',');
 getline(ss, empId, ',');
 getline(ss, salStr);
 double sal = stod(salStr);
 people.push_back(new Manager(name, ssn, birthDate, dep, empId, sal));
 }
 else if (category == "Owner")
 {
 string percOwnStr, dateBecameOwn;
 getline(ss, percOwnStr, ',');
 getline(ss, dateBecameOwn);
 double percOwn = stod(percOwnStr);
 people.push_back(new Owner(name, ssn, birthDate, percOwn, dateBecameOwn));
 }
 }
 inputFile.close();
 cout << "Data loaded from file: " << filename << "\n";
 }
 else
 {
 cout << "Unable to open file: " << filename << "\n";
 }
}
void savePeopleToFile(const vector<Person*>& people, const string& filename)
{
 ofstream outputFile(filename);

 if (outputFile.is_open())
 {
 for (const auto& person : people)
 {
 outputFile << person->getNam() << ",";
 outputFile << person->getSocial() << ",";
 outputFile << person->getBirthDate() << ",";
 if (auto laborer = dynamic_cast<Laborer*>(person))
 {
 outputFile << "Laborer" << ",";
 outputFile << laborer->getJobs() << ",";
 outputFile << laborer->getEmpId() << ",";
 outputFile << laborer->getHourSal() << ",";
 outputFile << laborer->getHourWork();
 }

 else if (auto manager = dynamic_cast<Manager*>(person))
 {
 outputFile << "Manager" << ",";
 outputFile << manager->getDep() << ",";
 outputFile << manager->getEmpId() << ",";
 outputFile << manager->getSal();
 }

 else if (auto owner = dynamic_cast<Owner*>(person))
 {
 outputFile << "Owner" << ",";
 outputFile << owner->getPercOwn() << ",";
 outputFile << owner->getDateBecameOwn();
 }
 outputFile << "\n";
 }
 outputFile.close();
 cout << "Data saved to file: " << filename << "\n";
 }

 else
 {
 cout << "Unable to open file: " << filename << "\n";
 }
}
int main()
{
 vector<Person*> people;
 // Load data from file
 loadPeopleFromFile(people, "people_data.txt");
 while (true)
 {
 cout << "\nMenu:\n";
 cout << "1. Add a Laborer\n";
 cout << "2. Add a Manager\n";
 cout << "3. Add an Owner\n";
 cout << "4. Display all people\n";
 cout << "5. Find a person by name\n";
 cout << "6. Remove a person by name\n";
 cout << "7. Calculate average earnings\n";
 cout << "8. Quit\n";
 cout << "Enter your choice: ";
 int choice;
 cin >> choice;
 if (choice == 1)
 {
 string nam, social, birthDate, jobs, empId;
 double hourSal, hourWork;
 cout << "Enter name: ";
 cin >> nam;
 cout << "Enter SSN: ";
 cin >> social;
 cout << "Enter birth date: ";
 cin >> birthDate;
 cout << "Enter job: ";
 cin >> jobs;
 cout << "Enter employee ID: ";
 cin >> empId;
 cout << "Enter hourly salary: ";
 cin >> hourSal;
 cout << "Enter hours worked: ";
 cin >> hourWork;
 auto laborer = new Laborer(nam, social, birthDate, jobs, empId, hourSal, hourWork);
 people.push_back(laborer);
 }

 else if (choice == 2)
 {
 string nam, social, birthDate, dep, empId;
 double sal;
 cout << "Enter name: ";
 cin >> nam;
 cout << "Enter SSN: ";
 cin >> social;
 cout << "Enter birth date: ";
 cin >> birthDate;
 cout << "Enter department: ";
 cin >> dep;
 cout << "Enter employee ID: ";
 cin >> empId;
 cout << "Enter salary: ";
 cin >> sal;
 auto manager = new Manager(nam, social, birthDate, dep, empId, sal);
 people.push_back(manager);
 }

 else if (choice == 3)
 {
 string nam, social, birthDate;
 double percOwn;
 string dateBecameOwn;
 cout << "Enter name: ";
 cin >> nam;
 cout << "Enter SSN: ";
 cin >> social;
 cout << "Enter birth date: ";
 cin >> birthDate;
 cout << "Enter percentage owned: ";
 cin >> percOwn;
 cout << "Enter date became owner: ";
 cin >> dateBecameOwn;
 auto own = new Owner(nam, social, birthDate, percOwn, dateBecameOwn);
 people.push_back(own);
 }

 else if (choice == 4)
 {
 displayPeople(people);
 }

 else if (choice == 5)
 {
 string name;
 cout << "Enter name: ";
 cin >> name;
 findPersonByName(people, name);
 }

 else if (choice == 6)
 {
 string name;
 cout << "Enter name: ";
 cin >> name;
 removePersonByName(people, name);
 }

 else if (choice == 7)
 {
 calculateAverageEarnings(people);
 }

 else if (choice == 8)
 {
 savePeopleToFile(people, "people_data.txt");

 for (auto& person : people)
 {
 delete person;
 }
 return 0;
 }

 else
 {
 cout << "Invalid choice.\n";
 }
 }
}
