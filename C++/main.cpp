//Preston Peck
//CS 323
//November 30, 2016
//Project 6

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class graphNode {
	private:
		int jobID;
		graphNode* next;

	public:
		graphNode();
		graphNode(int id, graphNode* n);

	friend class dependencyGraph;
};

class hashNode {
	private:
		int jobTime;
		int fatherCount;
		int childCount;
		graphNode* stackTop;
	
	public:
		hashNode();
		hashNode(int jT, int fC, int cC, graphNode* sT);

	friend class graphNode;
	friend class dependencyGraph;
};

class dependencyGraph {
	private:
		int numJobs;
		int numProcessors;
		int totalJobTime;
		int Time;
	
		int** processorSchedule;
		hashNode** graphHashTable;
		graphNode* OPEN;
	
	public:
		dependencyGraph();
		dependencyGraph(int nJ, int nP, int tJT, int T, graphNode* O);
		void insert(graphNode* hN);
		void schedule(ifstream& dependencies, ifstream& times, ifstream& processors, ofstream& outFile);
		void print(ofstream& outFile);
};
        

int main(int argc, char *argv[]) {
	ifstream inFile1;
	ifstream inFile2;
	ifstream inFile3;
	ofstream outFile;

	inFile1.open(argv[1]);
	inFile2.open(argv[2]);
	inFile3.open(argv[3]);
	//inFile3 since it was not specified will read:
		
	//2
	//5
	//40
		
	//because for each input set, you are to run the program three (3) separate times:
	//one time with 2 processors
	//one time with 5 processors
	//one time with 40 processors 

	if (!inFile1.is_open() || !inFile2.is_open() || !inFile3.is_open()) {
    	cerr<<"File failed to open!"<<endl;
    	return 0;
	}

	outFile.open(argv[4]);
		
	dependencyGraph* dG = new dependencyGraph();
	dG->schedule(inFile1, inFile2, inFile3, outFile);//2 processors
	inFile1.close();
	inFile2.close();
		
		


	inFile1.open(argv[1]);
	inFile2.open(argv[2]);
	dG->schedule(inFile1, inFile2, inFile3, outFile);//5 processors
	inFile1.close();
	inFile2.close();
		
	inFile1.open(argv[1]);
	inFile2.open(argv[2]);
	dG->schedule(inFile1, inFile2, inFile3, outFile);//40 processors
	inFile1.close();
	inFile2.close();
		
	inFile3.close();
	outFile.close();
}



hashNode::hashNode() : hashNode(0,0,0,NULL) {}
	
hashNode::hashNode(int jT, int fC, int cC, graphNode* sT) {
	jobTime = jT;
	fatherCount = fC;
	childCount = cC;
	stackTop = sT;
}



graphNode::graphNode() : graphNode(0, NULL) {}

graphNode::graphNode(int id, graphNode* n) {
	jobID = id;
	next = n;
}



dependencyGraph::dependencyGraph() : dependencyGraph(0,0,0,0,NULL) {}

dependencyGraph::dependencyGraph(int nJ, int nP, int tJT, int T, graphNode* O) {
	numJobs = nJ;
	numProcessors = nP;
	totalJobTime = tJT;
	Time = T;
	
	processorSchedule = new int*[numProcessors + 1];

	for (int i = 0; i < numProcessors + 1; i++) {
		processorSchedule[i] = new int[totalJobTime + 1];
	}

	graphHashTable = new hashNode*[numJobs];

	for (int i = 0; i < numJobs; i++) {
		graphHashTable[i] = new hashNode();
	}
	
	OPEN = O;
}

void dependencyGraph::insert(graphNode* hN) {	
	if (OPEN == NULL) {
		OPEN = hN;
	}
	
	else {
		graphNode* travelerPrev = NULL;
		graphNode* traveler = OPEN;

		while (traveler != NULL 
				&& graphHashTable[hN->jobID]->jobTime < graphHashTable[traveler->jobID]->jobTime) {
			travelerPrev = traveler;
			traveler = traveler->next;
		}

		if (traveler != NULL && graphHashTable[hN->jobID]->jobTime == graphHashTable[traveler->jobID]->jobTime) {
			while (traveler != NULL
					&& graphHashTable[hN->jobID]->jobTime == graphHashTable[traveler->jobID]->jobTime
					&& graphHashTable[hN->jobID]->childCount < graphHashTable[traveler->jobID]->childCount) {
				travelerPrev = traveler;
				traveler = traveler->next;
			}
		}

		if (travelerPrev != NULL) {
			travelerPrev->next = hN;
			hN->next = traveler;
		}

		else {
			OPEN = hN;
			hN->next = traveler;
		}
	}
}

void dependencyGraph::schedule(ifstream& dependencies, ifstream& times, ifstream& processors, ofstream& outFile) {
	dependencies >> numJobs;
	times >> numJobs;//redundant, but included in both inFiles for some reason
	processors >> numProcessors;
	
	if (numProcessors > numJobs) {//40 is scaled down in both example scenarios
		numProcessors = numJobs;
	}

	Time = 1;//0
	
	graphHashTable = new hashNode*[numJobs + 1];//1

	for (int i = 0; i <= numJobs; i++) {
		graphHashTable[i] = new hashNode();
	}

	int job = 0;
	int child = 0;

	while(dependencies >> job) {
		dependencies >> child;
		
		graphNode* newNode = new graphNode(child, graphHashTable[job]->stackTop);

		graphHashTable[job]->stackTop = newNode;
		graphHashTable[job]->childCount++;
		graphHashTable[child]->fatherCount++;//2
	}//3
	
	totalJobTime = 0;//4
	
	int jobTime = 0;

	while (times >> job) {
		times >> jobTime;
		graphHashTable[job]->jobTime = jobTime;
		totalJobTime += jobTime;//5
	}//6
	
	processorSchedule = new int*[numProcessors + 1];//7
	for (int i = 0; i < numProcessors + 1; i++) {
		processorSchedule[i] = new int[totalJobTime + 1];
	}

	while(Time < totalJobTime) {
		job = 1;//8

		while(job <= numJobs) {
			if (graphHashTable[job]->fatherCount == 0) {
				int orphan = job;
				graphNode* newNode = new graphNode(orphan, NULL);
				insert(newNode);
				graphHashTable[orphan]->fatherCount--;//9
				//is -1 now, job is now on the Open
			}
			job++;//10
		}//11
		
		int processor = 1;//12
		
		while (OPEN != NULL && processor <= numProcessors) {
			if (OPEN != NULL && processorSchedule[processor][0] <= 0)  {
				processorSchedule[processor][0]++;
				job = OPEN->jobID;
				OPEN = OPEN->next;
				int jobTime = graphHashTable[job]->jobTime;
			
				int slot = Time;//14
				
				while (slot < Time + jobTime) {
					processorSchedule[processor][slot] = job;//15
					slot++;//16
				}//17
			}//13
			processor++;//18
		}//19			
		
		Time++;//20
		
		processor = 1;//21
		
		while (processor <= numProcessors) {
			if (processorSchedule[processor][0] > 0 && processorSchedule[processor][Time] <= 0) {
				int doneJob = processorSchedule[processor][Time - 1];
				graphHashTable[doneJob]->fatherCount--;
				
				for (int i = 0; i < graphHashTable[doneJob]->childCount; i++) {//forgot this very important step
					graphHashTable[graphHashTable[doneJob]->stackTop->jobID]->fatherCount--;//is equal to -2 now, job is done
					graphHashTable[doneJob]->stackTop = graphHashTable[doneJob]->stackTop->next;
				}
					
				processorSchedule[processor][0] = 0;
			}//22
			processor++;//23
		}//24
	}//25

	print(outFile);
}	
	
void dependencyGraph::print(ofstream& outFile) {//provided monospaced font cleanly prints table based on string length of 3
	string slot = "";
	
	for (int i = 0; i < totalJobTime + 1; i++) {
		if (i == 0) {
			outFile << "  ";
		}
		
		else {
			outFile << "T" << i;
		}
		
		slot = std::to_string(i);
		
		if (slot.length() == 1) {
			outFile << "  ";
		}
		
		else {
			outFile << " ";
		}
	}
	
	outFile << endl;
	
	for (int i = 1; i < numProcessors + 1; i++) {
		outFile << "P" << i;
		slot = std::to_string(i);
		
		if (slot.length() == 1) {
			outFile << "  ";
		}
		
		else {
			outFile << " ";
		}		
		
		for (int j = 1; j < totalJobTime + 1; j++) {
			slot = std::to_string(processorSchedule[i][j]);
			
			if (slot.length() == 1) {
				outFile << processorSchedule[i][j] << "   ";
			}
			
			else {
				outFile << processorSchedule[i][j] << "  ";
			}
		}
		outFile << endl;
	}
	outFile << endl << endl;
}