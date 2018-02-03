import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Scanner;

public class Project6 {
	public static void main(String[] args) {
		try {
			Scanner inFile1 = new Scanner(new FileReader(args[0]));
			Scanner inFile2 = new Scanner(new FileReader(args[1]));
			Scanner inFile3 = new Scanner(new FileReader(args[2]));
			//inFile3 since it was not specified will read:
			
			//2
			//5
			//40
			
			//because for each input set, you are to run the program three (3) separate times:
			//one time with 2 processors
			//one time with 5 processors
			//one time with 40 processors 
			
			PrintWriter outFile = new PrintWriter(args[3]);
			
			dependencyGraph dG = new dependencyGraph();
			dG.schedule(inFile1, inFile2, inFile3, outFile);//2 processors
			inFile1.close();
			inFile2.close();
			
			inFile1 = new Scanner(new FileReader(args[0]));
			inFile2 = new Scanner(new FileReader(args[1]));
			dG.schedule(inFile1, inFile2, inFile3, outFile);//5 processors
			inFile1.close();
			inFile2.close();
			
			inFile1 = new Scanner(new FileReader(args[0]));
			inFile2 = new Scanner(new FileReader(args[1]));
			dG.schedule(inFile1, inFile2, inFile3, outFile);//40 processors
			inFile1.close();
			inFile2.close();
			
			inFile3.close();
			outFile.close();
		}
	
		catch (Exception e) {
			System.out.println(e);
		}
	}
}