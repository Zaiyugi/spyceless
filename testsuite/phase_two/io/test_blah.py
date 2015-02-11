pathToData = "datasets/"
file = open(pathToData + "testmaze")

w = int(read(file))
h = int(read(file))
pos_x = int(read(file))
pos_y = int(read(file))

i = 0
readMaze(i)

printMaze(i)

close(file)

def readMaze(i):
	#if i > h:
		#print "Finished reading maze"
		#return 0
	#end

	#j = 0
	#readRow(i, j)
	#i = i + 1
	#readmaze(i)
end
