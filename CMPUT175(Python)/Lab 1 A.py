# opens then reads and copies lines from rainfall file, then closes it
rain_file = open('rainfall.txt','r')
contents = rain_file.read()
rain_file.close()
line_list = contents.splitlines()

# creates an empty dictionary then appends each city as the key and the rainfall measure as the value 
city_dir = dict()
for i in line_list:
    tem = i.split(' ')
    city_dir[tem[0]] = tem[1]

# creates empty dictionaries to sort the cities by rainfall measure
Cat_1 = dict()
Cat_2 = dict()
Cat_3 = dict()
Cat_4 = dict()
Cat_5 = dict()

# appends city to appropriate category based on rainfall measure
for key,value in city_dir.items():
    if 51 <= float(value) and float(value) < 61:
        Cat_1[key] = value
    elif 61 <= float(value) and float(value) < 71:
        Cat_2[key] = value
    elif 71 <= float(value) and float(value) < 81:
        Cat_3[key] = value
    elif 81 <= float(value) and float(value) < 91:
        Cat_4[key] = value
    elif 91 <= float(value) and float(value) <= 100:
        Cat_5[key] = value

# creates a file in write mode then writes each category as a section title, followed by
# the city and the rainfall measure, then closes the file
outfile = open('rainfallfmt.txt','w')

outfile.write('[51-60]\n')
for key,value in Cat_1.items():
    outfile.write('{:^25s}{:5.1f}\n'.format(key.upper(),float(value)))

outfile.write('[61-70]\n')
for key,value in Cat_2.items():
    outfile.write('{:^25s}{:5.1f}\n'.format(key.upper(),float(value)))

outfile.write('[71-80]\n')
for key,value in Cat_3.items():
    outfile.write('{:^25s}{:5.1f}\n'.format(key.upper(),float(value)))

outfile.write('[81-90]\n')
for key,value in Cat_4.items():
    outfile.write('{:^25s}{:5.1f}\n'.format(key.upper(),float(value)))

outfile.write('[91-100]\n')
for key,value in Cat_5.items():
    outfile.write('{:^25s}{:5.1f}\n'.format(key.upper(),float(value)))

outfile.close()