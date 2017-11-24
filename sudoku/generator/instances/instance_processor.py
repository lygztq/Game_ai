with open('instances.txt','r') as instances_file:
	instances_in_line = instances_file.readlines()
	instances = []
	for line in range(len(instances_in_line)):
		new_item = instances_in_line[line].split()
		with open('instance%d.txt'%line,'w') as new_file:
			for i in range(9):
				for j in range(9):
					new_file.write(new_item[i*9+j])
					new_file.write(' ')
				new_file.write('\n')

