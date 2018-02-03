import java.io.PrintWriter;
import java.util.Scanner;

public class dependencyGraph {
	int numJobs;
	int numProcessors;
	int totalJobTime;
	int Time;
	
	int processorSchedule[][];
	hashNode graphHashTable[];
	graphNode OPEN;
	
	dependencyGraph() {
		this (0,0,0,0,null);
	}

	dependencyGraph(int nJ, int nP, int tJT, int T, graphNode O) {
		numJobs = nJ;
		numProcessors = nP;
		totalJobTime = tJT;
		Time = T;
		
		processorSchedule = new int[numProcessors + 1][totalJobTime + 1];
		graphHashTable = new hashNode[numJobs];
		
		OPEN = O;
	}
	
    void dependencyGraph(graphNode hN) {
        if (OPEN == null) {
            OPEN = hN;
        }
        
        else {
            graphNode travelerPrev = null;
            graphNode traveler = OPEN;
            
            while (traveler != null
                   && graphHashTable[hN.jobID].jobTime < graphHashTable[traveler.jobID].jobTime) {
                travelerPrev = traveler;
                traveler = traveler.next;
            }
            
            if (traveler != null && graphHashTable[hN.jobID].jobTime == graphHashTable[traveler.jobID].jobTime) {
                while (traveler != null
                       && graphHashTable[hN.jobID].jobTime == graphHashTable[traveler.jobID].jobTime
                       && graphHashTable[hN.jobID].childCount < graphHashTable[traveler.jobID].childCount) {
                    travelerPrev = traveler;
                    traveler = traveler.next;
                }
            }
            
            if (travelerPrev != null) {
                travelerPrev.next = hN;
                hN.next = traveler;
            }
            
            else {
                OPEN = hN;
                hN.next = traveler;
            }
        }
    }
	
	void schedule(Scanner dependencies, Scanner times, Scanner processors, PrintWriter outFile) {
		numJobs = dependencies.nextInt();
		numJobs = times.nextInt();//redundant, but included in both inFiles for some reason
		numProcessors = processors.nextInt();
		
		if (numProcessors > numJobs) {//40 is scaled down in both example scenarios
			numProcessors = numJobs;
		}

		Time = 1;//0
		
		graphHashTable = new hashNode[numJobs + 1];//1
		for (int i = 0; i < graphHashTable.length; i++) {
			graphHashTable[i] = new hashNode();
		}

		while(dependencies.hasNext()) {
			int job = dependencies.nextInt();
			int child = dependencies.nextInt();
			
			
			graphNode newNode = new graphNode(child, graphHashTable[job].stackTop);
			
			graphHashTable[job].stackTop = newNode;
			graphHashTable[job].childCount++;
			graphHashTable[child].fatherCount++;//2
		}//3
		
		totalJobTime = 0;//4
		
		while (times.hasNext()) {
			int job = times.nextInt();
			int jobTime = times.nextInt();
			graphHashTable[job].jobTime = jobTime;
			totalJobTime += jobTime;//5
		}//6
		
		processorSchedule = new int[numProcessors + 1][totalJobTime + 1];//7
		
		while(Time < totalJobTime) {
			int job = 1;//8

			while(job <= numJobs) {
				if (graphHashTable[job].fatherCount == 0) {
					int orphan = job;
					graphNode newNode = new graphNode(orphan, null);
					insert(newNode);
					graphHashTable[orphan].fatherCount--;//9
					//is -1 now, job is now on the Open
				}
				job++;//10
			}//11
			
			int processor = 1;//12
			
			while (OPEN != null && processor <= numProcessors) {
				if (OPEN != null && processorSchedule[processor][0] <= 0)  {
					processorSchedule[processor][0]++;
					job = OPEN.jobID;
					OPEN = OPEN.next;
					int jobTime = graphHashTable[job].jobTime;
				
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
					graphHashTable[doneJob].fatherCount--;
					
					for (int i = 0; i < graphHashTable[doneJob].childCount; i++) {//forgot this very important step
						graphHashTable[graphHashTable[doneJob].stackTop.jobID].fatherCount--;//is equal to -2 now, job is done
						graphHashTable[doneJob].stackTop = graphHashTable[doneJob].stackTop.next;
					}
						
					processorSchedule[processor][0] = 0;
				}//22
				processor++;//23
			}//24
		}//25
		
		print(outFile);
	}	
	
	void print(PrintWriter outFile) {//prints cleanly spaced and organized table based on string length of 2
		String slot = "";
		
		for (int i = 0; i < processorSchedule[0].length; i++) {
			if (i == 0) {
				outFile.print("  ");
			}
			
			else {
				outFile.print("T" + i);
			}
			
			slot = Integer.toString(i);
			
			if (slot.length() == 1) {
				outFile.print("  ");
			}
			
			else {
				outFile.print(" ");
			}
		}
		
		outFile.println();
		
		for (int i = 1; i < processorSchedule.length; i++) {
			outFile.print("P" + i);
			slot = Integer.toString(i);
			
			if (slot.length() == 1) {
				outFile.print("  ");
			}
			
			else {
				outFile.print(" ");
			}		
			
			for (int j = 1; j < processorSchedule[i].length; j++) {
				slot = Integer.toString(processorSchedule[i][j]);
				
				if (slot.length() == 1) {
					outFile.print(processorSchedule[i][j] + "   ");
				}
				
				else {
					outFile.print(processorSchedule[i][j] + "  ");
				}
			}
			outFile.println();
		}
		outFile.println('\n');
	}
}
