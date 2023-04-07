# opens the earthquake file then reads and copies all the lines from it, then closes it
quake_file = open('earthquake.txt','r')
contents = quake_file.read()
quake_file.close()
line_list = contents.splitlines()

# user created list of lists of regions
Regions = [['ALASKA'],['MAUI'],['PANAMA'],['MISSOURI'],['INDONESIA'],['VANUATU'],['MEXICO']]

# iterates through every line in the list of read lines from the file and splits them
# into lists of their own, then checks if a region name appears on that list and 
# appends the date and magnitude data from that list to the appropriate list in the
# list of lists of regions
for i in line_list:
    listed = i.split(' ')
    if 'ALASKA' in listed:
        data = [listed[1],listed[0]]
        Regions[0].append(data)
    elif 'MAUI' in listed:
        data = [listed[1],listed[0]]
        Regions[1].append(data)
    elif 'PANAMA' in listed:
        data = [listed[1],listed[0]]
        Regions[2].append(data)
    elif 'MISSOURI' in listed:
        data = [listed[1],listed[0]]
        Regions[3].append(data)
    elif 'INDONESIA' in listed:
        data = [listed[1],listed[0]]
        Regions[4].append(data)
    elif 'VANUATU' in listed:
        data = [listed[1],listed[0]]
        Regions[5].append(data)
    elif 'MEXICO' in listed:
        data = [listed[1],listed[0]]
        Regions[6].append(data)        

# prints each of the lists in the list of lists of regions 
for r in Regions:
    print(r)