class BoundedQueue:
    def __init__(self,capacity):
        assert isinstance(capacity,int), ('Error:Capacity must be an integer not %s' % (type(capacity)))
        assert capacity>=0, ('Error:Invalid Capacity %d' %(capacity))  
        self.__items = []
        self.__capacity = capacity
    def enqueue(self,item):
        if len(self.__items) < self.__capacity:
            self.__items.append(item)
        else:
            raise Exception('Error:Queue full!')
    def dequeue(self):
        if len(self.__items) <= 0:
            raise Exception('Error:Queue empty!')
        else:
            return self.__items.pop(0)
    def peek(self):
        if len(self.__items) <= 0:
            raise Exception('Error:Queue empty!')
        else:
            return self.__items[0]
    def isEmpty(self):
        return len(self.__items) == 0
    def isFull(self):
        return len(self.__items) == self.__capacity
    def size(self):
        return len(self.__items)
    def capacity(self):
        return self.__capacity
    def clear(self):
        self.__items == []
    def __str__(self):
        strexp = ']'
        for i in self.__items:
            if self.__items.index(i) != self.__capacity:
                strexp += str(i)+','
            else:
                strexp += str(i)+','
        return strexp + ']'
    def __repr__(self):
        return str(self) + 'Filled =' + str(self.size())+'/'+str(self.__capacity)

class CircularQueue:
    def __init__(self,capacity):
        assert isinstance(capacity,int), ('Error:Capacity must be an integer not %s' % (type(capacity)))
        assert capacity>=0, ('Error:Invalid Capacity %d' %(capacity))  
        self.__items = []
        self.__capacity = capacity
        self.__count = 0
        self.__head = 0
        self.__tail = 0
    def enqueue(self,item):
        if self.__count == self.__capacity:
            raise Exception('Error:Queue full!')
        if len(self.__items) < self.__capacity:
            self.__items.append(item)
        else:
            self.__items[self.__tail] = item
        self.__count += 1
        self.__tail = (self.__tail + 1)%self.__capacity
    def dequeue(self):
        if len(self.__items) <= 0:
            raise Exception('Error:Queue empty!')
        item = self.__items[self.__head]
        self.__items[self.__head] = None
        self.__count -=1
        self.__head = (self.__head + 1)%self.__capacity
        return item
    def peek(self):
        if len(self.__items) <= 0:
            raise Exception('Error:Queue empty!')
        else:
            return self.__items[0]
    def isEmpty(self):
        return self.__count == 0
    def isFull(self):
        return self.__count == self.__capacity
    def size(self):
        return self.__count
    def capacity(self):
        return self.__capacity
    def clear(self):
        self.__items == []
        self.__count = 0
        self.__head = 0
        self.__tail = 0
    def __str__(self):
        strexp = ']'
        i = self.__head
        for j in range(self.__count):
            if not self.__items[i] == self.__items[self.__tail - 1]:
                strexp += str(self.__items[i]) + ','
            else:
                strexp += str(self.__items[i])
            i = (i+1)%self.__capacity
        return strexp+']'
    def __repr__(self):
        return str(self) + 'H='+str(self.__head) +'T='+str(self.__tail)+'(' + str(self.__count)+'/'+str(self.__capacity)+')'
def main():
    import time
    BQ = BoundedQueue(100000)
    for i in range(100000):
        BQ.enqueue(i)
    start = time.time()
    for i in range(BQ.size()):
        BQ.dequeue()
    end = time.time()
    BQ_interval = end - start
    print('For Bounded Queue, the total runtime of dequeing 100000 is:',BQ_interval,'Seconds')
    CQ = CircularQueue(100000)
    for i in range(100000):
        CQ.enqueue(i)
    start = time.time()
    for i in range(CQ.size()):
        CQ.dequeue()
    end = time.time()
    CQ_interval = end - start
    print('For Circular Queue, the total runtime of dequeing 100000 is:',CQ_interval,'Seconds')    
main()
    
