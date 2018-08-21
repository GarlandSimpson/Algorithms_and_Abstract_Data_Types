/**
 * Name: Garland Simpson
 * Cruzid:
 * Assignment: pa1
 */

public class List
{
    private int n;
    private int index;
    private Node cursor;
    private Node front;
    private Node back;

    // Constructor: Creates a new empty list.
    List()
    {
        n = 0;
        index = -1;
        cursor = null;
        front = null;
        back = null;
    }


    private class Node
    {
        private int element;
        private Node next;
        private Node previous;

        Node(int theElement)
        {
            element = theElement;
            next = previous = null;
        }
    }

    // Access functions
    int length()//Returns the number of elements in this List.
    {
        return n;
    }

    int index() //If cursor is defined, returns the index of the cursor element, otherwise returns -1.
    {
        return index;
    }

    int front() // Returns front element. Pre: length()>0
    {
        if (n <= 0)
            throw new RuntimeException("Error in front(): length <= 0");
        else
            return front.element;
    }

    int back()  // Returns back element. Pre: length()>0
    {
        if (n <= 0)
            throw new RuntimeException("Error in back(): length <= 0");
        else
            return back.element;
    }

    int get()  // Returns cursor element. Pre: length()>0, index()>=0
    {
        if (n <= 0)
            throw new RuntimeException("Error in get(): length <= 0");
        else if (index < 0)
            throw new RuntimeException("Error in get(): index < 0");
        else
            return cursor.element;
    }

    public boolean equals(List L) // Returns true if this List and L are the same integer
    // sequence. The cursor is ignored in both lists.
    {
        if (n != L.n) return false; // CASE: RHS Length != LHS Length.

        Node current = front;
        Node lCurrent = L.front;

        while(current != null)
        {
            if (current.element != lCurrent.element) // CASE: the elements are NOT Equal.
                return false;

            current = current.next;
            lCurrent = lCurrent.next;
        }

        return true; // CASE: The Lists are the same.
    }


    // Manipulation procedures
    void clear() // Resets this List to its original empty state.
    {
        n = 0;
        index = -1;
        cursor = null;
        front = null;
        back = null;
    }

    void moveFront() // If List is non-empty, places the cursor under the front element, otherwise does nothing.
    {
        if (n != 0)
        {
            index = n - 1;
            cursor = front;
        }
    }

    void moveBack() // If List is non-empty, places the cursor under the back element, otherwise does nothing.
    {
        if (n != 0)
        {
            index = n - 1;
            cursor = back;
        }
    }

    void movePrev() // If cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined and at front, cursor becomes
    // undefined, if cursor is undefined does nothing.
    {
        if (cursor != null)
        {
            cursor = cursor.previous;
            index--;
        }
    }

    void moveNext() // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing.
    {
        if (cursor != null)
        {
            cursor = cursor.next;
            index--;
        }
    }

    void prepend(int data) // Insert new element into this List.
    {
        Node newNode = new Node(data);

        if (n == 0) // CASE: list is empty.
        {
            newNode.next = null;
            newNode.previous = null;
            front = newNode;
            back = newNode;
            cursor = newNode;
            index = 0;
        }
        else // CASE: List is NOT empty, insert before front;
        {
            newNode.previous = null;
            newNode.next = front;
            front.previous = newNode;
            front = newNode;
        }
        n++;
    }

    void append(int data) // Insert new element into this List.
    {
        Node newNode = new Node(data);

        if (n == 0) // CASE: List is empty.
        {
            newNode.previous = null;
            newNode.next = null;
            front = newNode;
            back = newNode;
            cursor = newNode;
            index = 0;
        }
        else // CASE: List is NOT empty, insert after back.
        {
            newNode.next = null;
            newNode.previous = back;
            back.next = newNode;
            back = newNode;
        }
        n++;
    }

    void insertBefore(int data) // Insert new element before cursor. Pre: length()>0, index()>=0
    {
        if (n <= 0)
            throw new RuntimeException("Error in insertBefore(int): length <= 0");
        else if (index < 0)
            throw new RuntimeException("Error in insertBefore(int): index < 0");
        else
        {
            Node newNode = new Node(data);

            if (cursor.previous == null)
            {
                front = newNode;
                newNode.previous = null;
                newNode.next = cursor;
                cursor.previous = newNode;
            }
            else
            {
                newNode.previous = cursor.previous;
                newNode.next = cursor;
                cursor.previous = newNode;
                cursor = newNode.previous;
                cursor.next = newNode;
                cursor = newNode.next;
            }
            n++;
        }
    }

    void insertAfter(int data) // Inserts new element after cursor. Pre: length()>0, index()>=0
    {
        if (n <= 0)
            throw new RuntimeException("Error in insertAfter(int): length <= 0");
        else if (index < 0)
            throw new RuntimeException("Error in insertAfter(int): index < 0");
        else
        {
            Node newNode = new Node(data);

            if (cursor.next == null)
            {
                cursor.next = newNode;
                newNode.next = null;
                newNode.previous = cursor;
                back = newNode;
            }
            else
            {
                newNode.next = cursor.next;
                newNode.previous = cursor;
                cursor.next = newNode;
                cursor = newNode.next;
                cursor.previous = newNode;
                cursor = newNode.previous;
            }
            n++;
        }
    }

    void deleteFront() // Deletes the front element. Pre: length()>0
    {
        if (n <= 0)
            throw new RuntimeException("Error in deleteFront(): length <= 0");
        else
        {
            cursor = front;
            front = front.next;
            front.previous = null;
            cursor.next = null;
            cursor = front;
            n--;
        }
    }

    void deleteBack() // Deletes the back element. Pre: length()>0
    {
        if (n <= 0)
            throw new RuntimeException("Error in deleteBack(): length <= 0");
        else
        {
            cursor = back;
            back = back.previous;
            back.next = null;
            cursor.previous = null;
            cursor = back;
            n--;
        }
    }

    void delete() // Deletes cursor element, making cursor undefined. Pre: length()>0, index()>=0
    {
        if (n <= 0)
            throw new RuntimeException("Error in delete(): length <= 0");
        else if (index < 0)
            throw new RuntimeException("Error in delete(): index < 0");
        else
        {
            Node temp = cursor;
            cursor = temp.previous;
            cursor.next = temp.next;
            cursor = temp.next;
            cursor.previous = temp.previous;
            cursor = null;
            index = -1;
            n--;
        }
    }

    // Other methods
    @Override
    public String toString() // Overrides Object's toString method. Returns a String
    // representation of this List consisting of a space
    // separated sequence of integers, with front on left.
    {
        StringBuffer sb = new StringBuffer();
        if (n > 0)
        {
            Node current = front;

            while(current != null)
            {
                sb.append(current.element);

                if(current != back)
                    sb.append(" ");

                current = current.next;
            }
        }

        return new String(sb);
    }

    List copy() // Returns a new List representing the same integer sequence as this
    // List.  The cursor in the new list is undefined, regardless of the
    // state of the cursor in this List. This List is unchanged.
    {
        List newList = new List();
        Node current = front;

        while(current != null)
        {
            newList.append(current.element);
            current = current.next;
        }

        return newList;
    }
}
