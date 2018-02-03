public class hashNode {
	int jobTime;
	int fatherCount;
	int childCount;
	graphNode stackTop;
	
	hashNode() {
		this(0,0,0,null);
	}
	
	hashNode(int jT, int fC, int cC, graphNode sT) {
		jobTime = jT;
		fatherCount = fC;
		childCount = cC;
		stackTop = sT;
	}
}
