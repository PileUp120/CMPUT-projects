def binarySearch (listNumbers, low, high, key):
    found = False
    low = low
    high = high
    guess = (high+low)//2
    if key == listNumbers[guess]:
        found = True
    else:
        while low <= high :
            if key < listNumbers[guess]:
                return binarySearch(listNumbers,low,guess-1,key)
            else:
                return binarySearch(listNumbers,guess+1,high,key)             
    if not found:
        guess = -1
    return guess


# Test array 
def main():
    array_for_test = [-8,-2,1,3,5,7,9]
    print(binarySearch(array_for_test,0,len(array_for_test)-1,9))
    print(binarySearch(array_for_test,0,len(array_for_test)-1,-8))
    print(binarySearch(array_for_test,0,len(array_for_test)-1,4))
    
main()