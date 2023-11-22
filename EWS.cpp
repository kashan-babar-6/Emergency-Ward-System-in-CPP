#include<iostream>
#include<string>
#include<ctime> //Randon nUmber w.r.t time
#include<stdlib.h>
#include<fstream>
#include<conio.h>
using namespace std;

//User Defined Functions
void receptionMenu();
void enterPatient();
void operationDetails();
void allStats();
int generateNum(int, int);
string spaceToStarac(string);
string staracToSpace(string);

//Creating Patient's Class
class Patient {
    public:
        string name, problem;
        int condition, AT, OT, FT;
        float TAT, WT;
        bool completed;
        static int SAT;

        void patientInput();
        void storePatients();
};
int Patient::SAT= 0;
void Patient::patientInput() {
    AT= SAT;
    OT= generateNum(1, 30);
    completed= false;  
    FT=0;
    WT=0;
    TAT=0;
}
void Patient::storePatients() {

    fstream ReadyPatients;
    ReadyPatients.open("ReadyPatients.txt", ios::app);
    if(ReadyPatients.is_open()) {
        ReadyPatients<<name<<" "<<problem<<" "<<AT<<" "<<OT<<" "<<condition<<" "
                    <<FT<<" "<<TAT<<" "<<WT<<" "<<completed<<endl;
    }
    else {
        cout<<"\nFile is not openned";
    }
    ReadyPatients.close();

}
 
class Scheduling {
    public:
        int noOfPatients();//fethc total patients
        bool retrievePatients(Patient *); //fetch patients data
        void sortingPatients(Patient *, int);
        int nextPatient(Patient *, int, int);
        float avgTAT(Patient *,float);
        float avgWT(Patient *,float);
        int allNoOfPatients(); //function for all completed patients
        bool allRetrievePatients(Patient *); //function for all completed patients
};
int Scheduling::noOfPatients() {
    fstream countPatients;
    countPatients.open("ReadyPatients.txt", ios::in);

    int count=0;
    string line;
    while(getline(countPatients, line)) {
        count++;
    }
    return count;
}
bool Scheduling::retrievePatients(Patient pArray[]) {
    fstream readFile;
    readFile.open("ReadyPatients.txt", ios::in);
    string name, problem;
    int AT, OT, condition, FT, TAT, WT;
    bool completed;
    int i=0;
    if(readFile.is_open()) {
        while(readFile>>name>>problem>>AT>>OT>>condition>>FT>>TAT>>WT>>completed) {
            pArray[i].name= staracToSpace(name);
            pArray[i].problem= staracToSpace(problem);
            pArray[i].AT= AT;
            pArray[i].OT= OT;
            pArray[i].condition= condition;
            pArray[i].FT= FT;
            pArray[i].TAT= TAT;
            pArray[i].WT= WT;
            pArray[i].completed= completed;
            i++;
        }
        return true;
    }
    else {
        return false;
    }
}
void Scheduling::sortingPatients(Patient pArray[], int size) {
    Patient temp;
    for(int i=0; i<size; i++) {
        for(int j=i; j<size - 1; j++) {
            if(pArray[j].AT > pArray[j+1].AT) {
                temp= pArray[j];
                pArray[j]= pArray[j+1];
                pArray[j+1]= temp;
            }
        }
    }
}
int Scheduling::nextPatient(Patient pArray[], int size, int cTime) {
    int maxPriority= -1;
    int indexNum;
    for(int i=0; i<size; i++) {
        if(pArray[i].AT <= cTime && pArray[i].completed == false) {
            if(pArray[i].condition < maxPriority || maxPriority == -1) {
                maxPriority= pArray[i].condition;
                indexNum= i;
            }
            else if(pArray[i].condition == maxPriority) {
                if(pArray[i].AT < pArray[indexNum].AT) {
                    indexNum= i;
                }
            }
        }
    }
    return indexNum;
}
float Scheduling::avgTAT(Patient pArray[], float size) {
    float sum=0;
    for(int i=0; i<size; i++) {
        sum += pArray[i].TAT;
    }
    return sum / size;
}
float Scheduling::avgWT(Patient pArray[], float size) {
    float sum=0;
    for(int i=0; i<size; i++) {
        sum += pArray[i].WT;
    }
    return sum / size;
}
int Scheduling::allNoOfPatients() {
    fstream countPatients;
    countPatients.open("CompletedOperations.txt", ios::in);

    int count=0;
    string line;
    while(getline(countPatients, line)) {
        count++;
    }
    return count;
}
bool Scheduling::allRetrievePatients(Patient *pArray) {
    fstream readFile;
    readFile.open("CompletedOperations.txt", ios::in);
    string name, problem;
    int AT, OT, condition, FT, TAT, WT;
    bool completed;
    int i=0;
    if(readFile.is_open()) {
        while(readFile>>name>>problem>>AT>>OT>>condition>>FT>>TAT>>WT>>completed) {
            pArray[i].name= staracToSpace(name);
            pArray[i].problem= staracToSpace(problem);
            pArray[i].AT= AT;
            pArray[i].OT= OT;
            pArray[i].condition= condition;
            pArray[i].FT= FT;
            pArray[i].TAT= TAT;
            pArray[i].WT= WT;
            pArray[i].completed= completed;
            i++;
        }
        return true;
    }
    else {
        return false;
    }
}

int main() {

    receptionMenu();

}

void receptionMenu() {

    int receptChoice=0;
	bool receptError= false;
	
	while(true) {	
        system("CLS");	
		cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	   Emergency Ward System	|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|		Reception		|"<<endl
			<<"\t\t\t\t\t|					|"<<endl;
		
		cout<<"\t\t\t\t\t| Press '1' to enter patients		|"<<endl
			<<"\t\t\t\t\t| Press '2' to start operation	        |"<<endl
			<<"\t\t\t\t\t| Press '3' to check overall stats	|"<<endl
			<<"\t\t\t\t\t|					|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl;
				
		if(receptError==true) {
			cout<<"\n\t\t\t\t\t*Error: Invalid Choice Number!"<<endl;
		}
				
		cout<<"\n\t\t\t\t\tEnter your Choice: ";
		cin>>receptChoice;
			
		if(receptChoice==1) {
			enterPatient();
			break;
		}
		else if(receptChoice==2) {
			operationDetails();
			break;
		}
		else if(receptChoice==3) {
			allStats();
			break;
		}
		else {
			receptError= true;
			continue;
		}
	}

}

void enterPatient() {

    system("CLS");
	cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|	  Emergency Ward System	        |"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|	      Enter Patients		|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl;

    int noOfpatients=0;
    cout<<"\n\t\t\t\t\tHow many Patients you want to enter: ";
    cin>>noOfpatients;

    Patient patient[noOfpatients];

    for(int i=0; i<noOfpatients; i++) {
        system("CLS");
        cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
            <<"\t\t\t\t\t|	  Emergency Ward System	        |"<<endl
            <<"\t\t\t\t\t-----------------------------------------"<<endl
            <<"\t\t\t\t\t|	         Patient "<<i+1<<"		|"<<endl
            <<"\t\t\t\t\t-----------------------------------------"<<endl;
        cin.ignore();
        cout<<"\t\t\t\t\tEnter Patient's name: ";
        getline(cin, patient[i].name);
        cout<<"\t\t\t\t\tEnter Patient's Problem: ";
        getline(cin, patient[i].problem);
        cout<<"\t\t\t\t\tEnter condition number:"<<endl
            <<"\t\t\t\t\t\t1- Critical"<<endl
            <<"\t\t\t\t\t\t2- Serious"<<endl
            <<"\t\t\t\t\t\t3- Emergency"<<endl
            <<"\t\t\t\t\t\t4- Normal"<<endl;
        cout<<"\t\t\t\t\tEnter your choice: ";
        cin>>patient[i].condition;
        patient[i].patientInput();

        patient[i].name= spaceToStarac(patient[i].name);
        patient[i].problem= spaceToStarac(patient[i].problem);

        //File Handling(Admitting Patients)
        patient[i].storePatients();

    }
    patient[0].SAT++;
    cout<<"\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|    Patient(s) Admitted Successfully	|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl;
    cout<<"\n\n\t\t\t\t\tPress any key to go to Reception Menu";
	if(getch()) {
		system("CLS");
		receptionMenu();
	}
}

void operationDetails() {
    Scheduling schedule;
    int noOfPatients= schedule.noOfPatients();

    system("CLS");	
	cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|	   Emergency Ward System	|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|	    Operation Schedule		|"<<endl
        <<"\t\t\t\t\t-----------------------------------------"<<endl;

    if(noOfPatients == 0) {
        cout<<"\n\n\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|          No Patients to Operate	|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl;
    }
    else {
        Patient patients[noOfPatients];
        schedule.retrievePatients(patients);

        schedule.sortingPatients(patients, noOfPatients);

        int currentTime= patients[0].AT;
        int prevPatientIndex= 0;
        int patientIndex= 0;

        for(int i=0; i<noOfPatients; i++) {
            if(i==0) {
                patientIndex= schedule.nextPatient(patients, noOfPatients, currentTime);
                patients[patientIndex].FT= patients[patientIndex].AT + patients[patientIndex].OT;
                patients[patientIndex].TAT= patients[patientIndex].FT - patients[patientIndex].AT;
                patients[patientIndex].WT= patients[patientIndex].TAT - patients[patientIndex].OT;
                patients[patientIndex].completed= true;
                prevPatientIndex= patientIndex;
                currentTime= patients[patientIndex].FT;
            }
            else {
                patientIndex= schedule.nextPatient(patients, noOfPatients, currentTime);
                patients[patientIndex].FT= patients[patientIndex].OT + patients[prevPatientIndex].FT;
                patients[patientIndex].TAT= patients[patientIndex].FT - patients[patientIndex].AT;
                patients[patientIndex].WT= patients[patientIndex].TAT - patients[patientIndex].OT;
                patients[patientIndex].completed= true;
                prevPatientIndex= patientIndex;
                currentTime= patients[patientIndex].FT;
            }
        }

        cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl
			<<"|Patient Name    	Arrival Time	Operation Time	    Condition	    Complete Time	Turnaround Time    Waiting Time|"<<endl
			<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;

        for(int i=0; i<noOfPatients; i++) {
            cout<<patients[i].name<<"\t\t\t"<<patients[i].AT<<"\t\t"<<patients[i].OT<<"\t\t"<<patients[i].condition<<"\t\t"<<patients[i].FT<<"\t\t\t"<<patients[i].TAT<<"\t\t"<<patients[i].WT<<endl
            <<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
        }
        cout<<"\n\n\t\t\t\t\t-----------------------------------------"
            <<"\n\t\t\t\t\tAverage Turnaround Time= "<<schedule.avgTAT(patients, noOfPatients)<<endl
            <<"\t\t\t\t\tAverage Waiting Time= "<<schedule.avgWT(patients, noOfPatients)
            <<"\n\t\t\t\t\t-----------------------------------------"<<endl;

        fstream cOperations;
        cOperations.open("CompletedOperations.txt", ios::app);
        for(int i=0; i<noOfPatients; i++) {
            patients[i].name= spaceToStarac(patients[i].name);
            patients[i].problem= spaceToStarac(patients[i].problem);
            cOperations<<patients[i].name<<" "<<patients[i].problem<<" "<<patients[i].AT
            <<" "<<patients[i].OT<<" "<<patients[i].condition<<" "<<patients[i].FT
            <<" "<<patients[i].TAT<<" "<<patients[i].WT<<" "<<patients[i].completed<<endl;
        }
        cOperations.close();

        remove("ReadyPatients.txt");
    }
    cout<<"\n\n\t\t\t\t\tPress any key to go to Reception Menu";
	if(getch()) {
		system("CLS");
		receptionMenu();
        return;
	}

}

void allStats() {

    Scheduling schedule;
    int allNoPatients= schedule.allNoOfPatients();
    Patient allPatients[allNoPatients];
    schedule.allRetrievePatients(allPatients);
    system("CLS");
	cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	   Emergency Ward System	|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|		Overall Stats		|"<<endl
			<<"\t\t\t\t\t|					|"<<endl;
		
	cout<<"\t\t\t\t\t| Total Operations Completed: "<<allNoPatients<<"		|"<<endl
		<<"\t\t\t\t\t| Average Turnaround Time: "<<schedule.avgTAT(allPatients, allNoPatients)<<"         |"<<endl
		<<"\t\t\t\t\t| Average Waiting Time: "<<schedule.avgWT(allPatients, allNoPatients)<<"	        |"<<endl
		<<"\t\t\t\t\t|					|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl;
    
    cout<<"\n\n\t\t\t\t\tPress any key to go to Reception Menu";
	if(getch()) {
		system("CLS");
		receptionMenu();
        return;
	}

}

int generateNum(int minNum, int maxNum) {
	
	srand((unsigned)time(0));
	int id=0;
	id= rand() % maxNum; //rand()generate random number
	
	if(id<minNum) {
		id= rand() % maxNum + minNum;
	}
	
	return id;
	
}

string spaceToStarac(string words) {
	
	for(int i=0; i<words.length(); i++) {
		if(words[i]==' ') {
			words[i]='*';
		}
	}
	
	return words;
	
}

string staracToSpace(string words) {
	
	for(int i=0; i<words.length(); i++) {
		if(words[i]=='*') {
			words[i]=' ';
		}
	}
	
	return words;
} 

