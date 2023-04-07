def isValidDate(date):
    Days31 = [1,3,5,7,8,10,12]
    Days30 = [4,6,9,11]
    if '-' not in date or date.count('-') != 2:
        print('Ivalid data entry form')
    else:
        d = date.split('-')
        if len(d[0]) != 4 or len(d[1]) != 2 or len(d[2]) != 2:
            print('Invalid date')
        else:
            if not d[0].isnumeric() or not d[1].isnumeric() or not d[2].isnumeric:
                print("Invalid date")
            else:
                leapYear = 0
                if int(d[0]) % 4 == 0:
                    leapYear = True
                else:
                    leapYear = False
                assert(1901 <= int(d[0]) <= 2020),"Year not in valid range"
                assert(1 <= int(d[1]) <= 12),"Invalid month"
                if int(d[1]) in Days31:
                    assert(1 <= int(d[2]) <= 31),"Invalid date"
                elif int(d[1]) in Days30:
                    assert(1 <= int(d[2]) <= 30),"Invalid date"
                elif int(d[1]) == 2 and leapYear:
                    assert(1 <= int(d[2]) <= 29),"Invalid date"
                elif int(d[1]) and not leapYear:
                    assert(1 <= int(d[2]) <= 28),"Invalid date"                
dateCheck = input("Enter a date:")
isValidDate(dateCheck)
            
        