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
    CustServ = True
    NormCust = CircularQueue(3)
    VipCust = CircularQueue(3)    
    while CustServ:
        Mode = input('Add, Serve or Exit:')
        while Mode.upper() not in ['ADD','SERVE','EXIT']:
            print('Invalid mode')
            Mode = input('Add, Serve or Exit:')
        try:
            if Mode.upper() == 'ADD':
                Name = input('Enter the name of the Person to add:')
                VIP = input('Is the customer VIP?')
                while VIP.upper() not in ['TRUE','FALSE']:
                    print('Invalid input')
                    VIP = input('Is the customer VIP?')
                if VIP.upper() == 'TRUE' and not VipCust.isFull():
                    VipCust.enqueue(Name)
                    print('Add',Name,'to VIP line')
                elif VIP.upper() == 'TRUE' and VipCust.isFull():
                    raise Exception('Error:VIP customers queue is full')
                elif VIP.upper() == 'FALSE' and not NormCust.isFull():
                    NormCust.enqueue(Name)
                    print('Add',Name,'to normal line')
                else:
                    raise Exception('Error:Normal customers queue is full')
                print('Normal customers queue:',str(NormCust))
                print('VIP customers queue:',str(VipCust))
                print('')
            elif Mode.upper() == 'SERVE':
                if VipCust.isEmpty() and NormCust.isEmpty():
                    raise Exception("Error: Queues are empty")
                else:
                    if not VipCust.isEmpty():
                        served = VipCust.dequeue()
                        print(served,'has been served')
                    else:
                        served = NormCust.dequeue()
                        print(served,'has been served')
                print('Normal customers queue:',str(NormCust))
                print('VIP customers queue:',str(VipCust))
                print('')
            else:
                print('Quitting')
                CustServ = False
        except Exception as e:
            print(e)
main()            