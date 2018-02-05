# 323 6-Dependency-Graph<br />
### CSC 323-32: Project 6 <Dependency Graph > (C++)<br />
### Preston Peck<br />
### Due date: Dec. 6, 2016 <br />

#### **** Algorithm steps for Dependency Job Scheduling:<br />

**Step 0:** open input-1 (argv[1]) and input-2 (argv[2]) and output (argv[4])<br />
     **0.1:** numJobs <-- get from input1.<br />
     **0.2:** numProcessor <-- get from argv[3]<br />
     **0.3:** if numProcessor > numJobs<br />
            numProcessor <-- numJobs <br />
     **0.4:** Time <-- 1 <br />
     
**Step 1:** graphHashTable <-- dynamically allocated and initialized of all fields<br />

**Step 2:** <ni, nj> <-- read from input-1<br />
     **2.1:** job <-- ni 	& child <-- nj<br />
     **2.2:** newNode <-- create a graphNode for <child><br />
     **2.3:** push newNode on the top of graphHashTable[index].stackTop<br />
     **2.4:** graphHashTable[job].childCount ++<br />
     **2.5:** graphHashTable[child].fatherCount ++<br />
     
**Step 3:** repeat step 2 until input-1 is end of file<br />

**Step 4:** totalJobTime <-- 0<br />

**Step 5:** <job, jobTime> <-- read from input-2<br />
     **5.1:** graphHashTable[job].jobTime <-- jobTime<br />
     **5.2:** totalJobTime += jobTime<br />
     
**Step 6:** repeat step 5 until input-2 is end of file<br />

**Step 7:** processorSchedule <-- dynamically allocated and initialized<br />

**Step 8:** job <-- 1<br />

**Step 9:** if graphHashTable[job].fatherCount == 0<br />
      **9.1:** orphan <-- job	<br />
      **9.2:** newNode <-- create a graphNode for <orphan><br />
      **9.3:** insert(OPEN, newNode)<br />
      **9.4:** graphHashTable[orphen].fatherCount --<br />
      
**Step 10:** job++<br />

**Step 11:** repeat step 9 - step 10 while job <= numJobs	   <br />

**Step 12:** processor <-- 1<br />

**Step 13:** if OPEN is not empty and processorSchedule[processor][0] <= 0<br />
     **13.1:** availProc <-- processor<br />
     **13.2:** processorSchedule[availProc][0]++<br />
     **13.3:** job <-- remove from Open <br />
     **13.4:** jobTime <-- graphHashTable[job].jobTime<br />
     
**Step 14:** slot <-- Time<br />

**Step 15:** processorSchedule[availProc][slot] <-- job<br />

**Step 16:** slot ++<br />

**Step 17:** repeat step 15 to step 16 while slot <= Time + jobTime<br />

**Step 18:** processor ++<br />

**Step 19:** repeat step 13 - step 18 while OPEN is *NOT empty* and (processor <= numProcessor) <br />

**Step 20:** Time++<br />

**Step 21:** processor <-- 1<br />

**Step 22:** if (processorSchedule[processor][0] > 0) and (processorSchedule[processor][Time] <= 0)<br />
doneJob <-- processorSchedule[processor][Time - 1]<br />
     **22.1:** graphHashTable[doneJob].fatherCount-- <br />
     **22.2:** processorSchedule[processor][0] <-- 0<br />
     
**Step 23:** processor ++<br />

**Step 24:** repeat step 22 to 23 while processor <= numProcessor<br />

**Step 25:** repeat which steps 8 to 24 while Time < totalJobTime<br />

### INPUT<br />
Dependencies	<br />				
15			<br />			
1 2				<br />		
1 3			<br />			
7 3			<br />			
9 3			<br />			
4 2			<br />			
4 6			<br />			
4 5			<br />			
2 6			<br />			
3 6			<br />			
3 10		<br />			
3 8			<br />			
5 13			<br />		
8 15			<br />		
8 11			<br />		
6 11			<br />		
6 12<br />
6 13<br />
5 14<br />
12 14<br />

13			<br />			
1 2			<br />			
7 3			<br />			
9 3			<br />			
4 2				<br />		
4 6				<br />	
4 5				<br />	
2 6				<br />		
3 10			<br />		
3 8				<br />		
5 13			<br />		
8 11			<br />		
6 11			<br />		
6 12			<br />		
6 13 <br />

Times <br />
15<br />
1 1<br />
2 1<br />
3 1<br />
4 1<br />
5 1<br />
6 1<br />
7 1<br />
8 1<br />
9 1<br />
10 1<br />
11 1<br />
12 1<br />
13 1<br />
14 1<br />
15 1<br />
  
13<br />
1 4<br />
2 1<br />
3 3<br />
4 3<br />
5 2<br />
6 2<br />
7 1<br />
8 2<br />
9 2<br />
10 3<br />
11 2<br />
12 4<br />
13 2<br />

Processors<br />
2<br />
5<br />
40<br />
  
### OUTPUT<br />
|    |T1  |T2  |T3  |T4  |T5  |T6  |T7  |T8  |T9  |T10 |T11 |T12 |T13 |T14 |T15 |
|--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |
|P1  |4   |5   |9   |3   |6   |12  |14  |11  |0   |0   |0   |0   |0   |0   |0   | <br /> 
|P2  |1   |2   |7   |0   |8   |15  |13  |10  |0   |0   |0   |0   |0   |0   |0   | <br />

|    |T1  |T2  |T3  |T4  |T5  |T6  |T7  |T8  |T9  |T10 |T11 |T12 |T13 |T14 |T15 |
|--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |
|P1  |4   |3   |6   |12  |14  |0   |0   |0   |0   |0   |0   |0   |0   |0   | 0  | <br />
|P2  |1   |5   |8   |15  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P3  |9   |2   |10  |13  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P4  |7   |0   |0   |11  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P5  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
 
|    |T1  |T2  |T3  |T4  |T5  |T6  |T7  |T8  |T9  |T10 |T11 |T12 |T13 |T14 |T15 |
|--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |
|P1  |4   |3   |6   |12  |14  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P2  |1   |5   |8   |15  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P3  |9   |2   |10  |13  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P4  |7   |0   |0   |11  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P5  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P6  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P7  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P8  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P9  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P10 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P11 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P12 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P13 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P14 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P15 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />

|    |T1  |T2  |T3  |T4  |T5  |T6  |T7  |T8  |T9  |T10 |T11 |T12 |T13 |T14 |T15 |T16 |T17  |T18  |T19  |T20  |T21  |T22  |T23  |T24  |T25  |T26 |T27 |T28 |T29 |T30 |T31 |
|--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |
|P1  |1   |1   |1   |1   |9   |9   |6   |6   |12  |12  |12  |12  |8   |8   |11  |11  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |<br />
|P2  |4   |4   |4   |5   |5   |2   |7   |3   |3   |3   |10  |10  |10  |13  |13  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |<br />

|    |T1  |T2  |T3  |T4  |T5  |T6  |T7  |T8  |T9  |T10 |T11 |T12 |T13 |T14 |T15 |T16 |T17  |T18  |T19  |T20  |T21  |T22  |T23  |T24  |T25  |T26 |T27 |T28 |T29 |T30 |T31 |
|--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |
|P1  |1   |1   |1   |1   |2   |10  |10  |10  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0  |0   |0   |0   |0   |0   |0   |0   |  <br />
|P2  |4   |4   |4   |5   |5   |6   |6   |12  |12  |12  |12  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0  |0   |0   |0   |0   |0   |0   |0   |  <br />|
|P3  |9   |9   |3   |3   |3   |8   |8   |13  |13  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0  |0   |0   |0   |0   |0   |0   |0   |  <br />|
|P4  |7   |0   |0   |0   |0   |0   |0   |11  |11  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0  |0   |0   |0   |0   |0   | 0  |0   |  <br />
|P5  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0  |0   |0   |0   |0   |0   |0   |0   |  <br />

|    |T1  |T2  |T3  |T4  |T5  |T6  |T7  |T8  |T9  |T10 |T11 |T12 |T13 |T14 |T15 |T16 |T17  |T18  |T19  |T20  |T21  |T22  |T23  |T24  |T25  |T26 |T27 |T28 |T29 |T30 |T31 |
|--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |--- |
|P1  |1   |1   |1   |1   |2   |10  |10  |10  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P2  |4   |4   |4   |5   |5   |6   |6   |12  |12  |12  |12  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P3  |9   |9   |3   |3   |3   |8   |8   |13  |13  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P4  |7   |0   |0   |0   |0   |0   |0   |11  |11  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P5  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P6  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   || <br />
|P7  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P8  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P9  |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P10 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P11 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P12 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
|P13 |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   |0   | <br />
