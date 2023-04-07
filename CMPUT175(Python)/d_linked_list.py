from d_linked_node import d_linked_node

class d_linked_list:
    
    def __init__(self):
        self.__head=None
        self.__tail=None
        self.__size=0        

            
    def search(self, item):
        current = self.__head
        found = False
        while current != None and not found:
            if current.getData() == item:
                found= True
            else:
                current = current.getNext()
        return found
        
    def index(self, item):
        current = self.__head
        found = False
        index = 0
        while current != None and not found:
            if current.getData() == item:
                found= True
            else:
                current = current.getNext()
                index = index + 1
        if not found:
                index = -1
        return index        
         
    def add(self, item):
        temp = d_linked_node(item,self.__head,None)
        if self.__head != None:
            self.__head.setPrevious(temp)
        else:
            self.__tail = temp
        self.__head = temp
        self.__size += 1
        
    def remove(self, item):
        current = self.__head
        previous = None
        found = False
        while not found:
            if current.getData() == item:
                found = True
            else:
                previous = current
                current = current.getNext()
        if previous == None:
            self.__head = current.getNext()
        else:
            previous.setNext(current.getNext())
        if current.getNext() != None:
            current.getNext().setPrevious(previous)
        else:
            self.__tail = previous
        self.__size -= 1
        
    def append(self, item):
        temp = d_linked_node(item,None,None)
        if self.__head == None:
            self.__head = temp
        else:
            self.__tail.setNext(temp)
            temp.setPrevious(self.__tail)
        self.__tail = temp
        self.__size += 1        
        
    def insert(self, pos, item):
        if pos > (self.__size - 1):
            self.append(item)
        elif pos <= 0:
            self.add(item)
        else:
            i = 0
            current = self.__head
            while i < (pos-1):
                current = current.getNext()
                i += 1
            newNode = d_linked_node(item,None,None)
            newNode.setNext(current.getNext())
            newNode.setPrevious(current)
            current.setNext(newNode)
            newNode.getNext().setPrevious(newNode)
            self.__size += 1
        
    def pop(self, pos=None):
        if pos == None and self.__size == 1:
            item = self.__head.getData()
            self.__head.setData(None)
        elif pos == 0:
            item = self.__head.getData()
            newHead = self.__head.getNext()
            self.__head.setNext(None)
            newHead.setPrevious(None)
            self.__head = newHead
        elif pos == None:
            item = self.__tail.getData()
            newTail = self.__tail.getPrevious()
            self.__tail.setPrevious(None)
            newTail.setNext(None)
            self.__tail = newTail
        else:
            i = 0
            current = self.__head
            while i < (pos):
                current = current.getNext()
                i += 1
            item = current.getData()
            prevI = current.getPrevious()
            if current.getNext() != None:
                nextI = current.getNext()
                prevI.setNext(nextI)
                nextI.setPrevious(prevI)
            current.setPrevious(None)
            current.setNext(None)
        self.__size -= 1
        return item
        
    def search_larger(self, item):
        current = self.__head
        found = False
        index = 0
        while current != None and not found:
            if current.getData() > item:
                found= True
            else:
                current = current.getNext()
                index = index + 1
        if not found:
            index = -1
        return index 
        
    def get_size(self):
        return self.__size
    
    def get_item(self, pos):
        current = self.__head
        found = False
        i = 0
        if pos < 0:
            pos = self.__size + pos
        if 0 <= pos < self.__size:
            while i < pos:
                current = current.getNext()
                i += 1
        else:
            raise IndexError('Invalid position given for list')
        return current.getData()
        
    def __str__(self):
        s = ''
        i = 0
        current = self.__head
        while current != None:
            if i>0:
                s = s + ' '
            item = current.getData()
            if item != None:
                s = s + "%s" % item
                i += 1
            current = current.getNext()
        return s

def test():
                  
    linked_list = d_linked_list()
                    
    is_pass = (linked_list.get_size() == 0)
    assert is_pass == True, "fail the test"
            
    linked_list.add("World")
    linked_list.add("Hello")    
        
    is_pass = (str(linked_list) == "Hello World")
    assert is_pass == True, "fail the test"
              
    is_pass = (linked_list.get_size() == 2)
    assert is_pass == True, "fail the test"
            
    is_pass = (linked_list.get_item(0) == "Hello")
    assert is_pass == True, "fail the test"
        
        
    is_pass = (linked_list.get_item(1) == "World")
    assert is_pass == True, "fail the test"    
            
    is_pass = (linked_list.get_item(0) == "Hello" and linked_list.get_size() == 2)
    assert is_pass == True, "fail the test"
            
    is_pass = (linked_list.pop(1) == "World")
    assert is_pass == True, "fail the test"     
            
    is_pass = (linked_list.pop() == "Hello")
    assert is_pass == True, "fail the test"     
            
    is_pass = (linked_list.get_size() == 0)
    assert is_pass == True, "fail the test" 
                    
    int_list2 = d_linked_list()
                    
    for i in range(0, 10):
        int_list2.add(i)      
    int_list2.remove(1)
    int_list2.remove(3)
    int_list2.remove(2)
    int_list2.remove(0)
    is_pass = (str(int_list2) == "9 8 7 6 5 4")
    assert is_pass == True, "fail the test"
                
    for i in range(11, 13):
        int_list2.append(i)
    is_pass = (str(int_list2) == "9 8 7 6 5 4 11 12")
    assert is_pass == True, "fail the test"
                
    for i in range(21, 23):
        int_list2.insert(0,i)
    is_pass = (str(int_list2) == "22 21 9 8 7 6 5 4 11 12")
    assert is_pass == True, "fail the test"
                
    is_pass = (int_list2.get_size() == 10)
    assert is_pass == True, "fail the test"    
                    
    int_list = d_linked_list()
                    
    is_pass = (int_list.get_size() == 0)
    assert is_pass == True, "fail the test"
                    
        
                    
    for i in range(0, 1000):
        int_list.append(i)      
    correctOrder = True
            
    is_pass = (int_list.get_size() == 1000)
    assert is_pass == True, "fail the test"            
            
        
    for i in range(0, 200):
        if int_list.pop() != 999 - i:
            correctOrder = False
                            
    is_pass = correctOrder
    assert is_pass == True, "fail the test" 
            
    is_pass = (int_list.search_larger(200) == 201)
    assert is_pass == True, "fail the test" 
            
    int_list.insert(7,801)   
        
    is_pass = (int_list.search_larger(800) == 7)
    assert is_pass == True, "fail the test"
            
            
    is_pass = (int_list.get_item(-1) == 799)
    assert is_pass == True, "fail the test"
            
    is_pass = (int_list.get_item(-4) == 796)
    assert is_pass == True, "fail the test"
                    
    if is_pass == True:
        print ("=========== Congratulations! Your have finished exercise 1! ============")
                
if __name__ == '__main__':
    test()