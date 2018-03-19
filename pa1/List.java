// List.java
// Eric Yup
// 1530440 
// pa1 
// doubly linked list ADT
	public class List{
	// Node subclass
	private class Node{
		int data ;
		Node next ;
		Node prev ;
	    // Constructor for Node
	    Node(int data){ 
	    	this.data = data; 
	      	next = null; 
	      	prev = null;
	    }
	    // toString:  Overides Object's toString method.
	    public String toString() { 
	    	return String.valueOf(data); 
	    }
	}
	private Node head;		
	private Node tail;		
	private	int length;		
	private Node cursor;	
	
	// Constructor 
	// Creates new list.
	List(){
		head = null;
		tail = null;
		length = 0; // initialize
		cursor = null;
	}
	// Access functions
	int length(){return length;}// Returns the number of elements in this List.
	int index(){
        if (cursor == null) return -1;
       Node temp = head;
       int index = 0;
       while( temp != null ){
            if( temp.data == cursor.data) return index;
            index++;
            temp = temp.next;
       }
      return -1;
	} // If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.
	int front() { 
	        if( length() > 0) return head.data;
	        return -1;
	}
	   // Returns front element. Pre: length()>0
	int back(){
		if ( length() > 0) return tail.data;
		return -1;// Returns back element. Pre: length()>0
	}
	int get(){
        if(length() > 0 && index() >= 0) return cursor.data;
        return -1;
	}
        // Returns cursor element. Pre: length()>0, index()>=0
	
	boolean equals(List L){
		if( length() != L.length()) return false;
        List.Node A = this.head;
        List.Node B = L.head;        
        while( A != null){
             if( A.data != B.data) return false;
             A = A.next;
             B = B.next;
        }
        return true;
	}
	// Returns true if and only if this List and L are the same
	// integer sequence. The states of the cursors in the two Lists
	// are not used in determining equality.
	// Manipulation procedures
	void clear(){
        head = null;
        tail = null;
        length = 0;
        cursor = null;
	}
	// Resets this List to its original empty state.
	void moveFront(){if (length() > 0){cursor = head;}}
	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	void moveBack() {if (length() > 0){cursor = tail;}}//.next??
	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void movePrev() {
		if(index() == -1){return;}
        if(index() == 0) {cursor = null;}
        if ( index() >= 0 && index() <= length()-1) {cursor = cursor.prev;}// If cursor is defined and not at front, moves cursor one step toward
	}
	// front of this List, if cursor is defined and at front, cursor becomes

	// undefined, if cursor is undefined does nothing.

	void moveNext(){
		if(index() == -1) {return;}
        if(index() == length()-1) {cursor = null;}
        if ( index() >= 0 && index() <= length()-1) {cursor = cursor.next;}
	}
	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void prepend(int data){
		List.Node temp = new List.Node(data);
		if(length()>0){
			temp.next = head;
			head.prev = temp;
			head = temp;
		}
		if(length() == 0){
	    	head = temp;
	    	tail = temp;
		}
		length++;
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void append(int data){
		List.Node temp = new List.Node(data);		
		if(length() > 0){	
			tail.next = temp;				
			temp.prev = tail;				
			tail = temp;				
	    }   
	    if(length() == 0){
	    	head = temp;
	    	tail = temp;
	    }
	    length++;
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void insertBefore(int data) {
		if( length() > 0 && index() >= 0){
            if(index() == 0){
            prepend(data); 
            return;
            }
            List.Node temp = new List.Node(data);
            temp.next = cursor;
            temp.prev= cursor.prev;
            cursor.prev.next = temp;
            cursor.prev = temp;
        }
		length++;
	}
	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(int data) {
		if( length() > 0 && index() >= 0){
            if(index() == length()-1){
            append(data); 
            return;
            }
            List.Node temp = new List.Node(data);
            temp.next = cursor.next;
            temp.prev= cursor;
            cursor.next.prev = temp;
            cursor.next = temp;
        }
		length++;
	}
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void deleteFront(){
        if( length() < 0) {return;}
        if( length() == 1){
        clear();
        return;
        }
        head = head.next;
        head.prev = null;
        length++;
	}
	// Deletes the front element. Pre: length()>0
	void deleteBack(){
        if( length() < 0) return;
        if( length() == 1){
        clear();
        return;
        }
        tail = tail.prev;
        tail.next = null;
	}
	// Deletes the back element. Pre: length()>0
	void delete(){
		List.Node temp = cursor;
	   	if(length()== 0){return;}
	   	if(length()>0 && index()>=0){
	   		if(temp != null){
	   			cursor.prev.next = cursor.next;
	   			cursor.next.prev = cursor.prev;
	        }
	   	}
		length--;
	}
	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	// Other methods
	public String toString() {
        String str = "";
        List.Node temp = head;
        while( temp != null){
        	str += temp.data + " ";
            temp = temp.next;
        }
        return str;
	}
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public List copy(){
		List C = new List();
		List.Node traverse = head;
		while( traverse != null ){
			C.append(traverse.data);
			traverse = traverse.next;
		}
		return C;
	}
	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	
}