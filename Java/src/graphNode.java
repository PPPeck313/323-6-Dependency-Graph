public class graphNode {
	int jobID;
	graphNode next;
	
	graphNode() {
		this(0, null);
	}

	graphNode(int id, graphNode n) {
		jobID = id;
		next = n;
	}
}
