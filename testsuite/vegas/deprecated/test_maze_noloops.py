pathToData = "datasets/"
file = open(pathToData + "testmaze")

w = int(read(file))
h = int(read(file))
pos_x = int(read(file))
pos_y = int(read(file))

i = 0
readMaze(i)

#__debug__

printMaze(i)

close(file)

def readMaze(i):
   if i >= h:
      print "Finished reading maze"
      return 0
   end

   j = 0
   readRow(i, j)
   i = i + 1
   readMaze(i)
end

def readRow(i, j):
   if j >= w:
      print "Finished reading row: " + str(i)
      return 0
   end

   name = "maze_" + str(i) + "_" + str(j)
   ::eval(name) = read(file)

   j = j + 1
   readRow(i, j)
end

def printMaze(i):
   if i >= h:
      print "Finished printing maze"
      return 0
   end

   j = 0
   line = " "
   print printRow(i, j, line)

   i = i + 1
   printMaze(i)
end

def printRow(i, j, line):
   if j >= w:
      return line
   end

   name = "maze_" + str(i) + "_" + str(j)
   line = line + str(eval(name)) + " "

   j = j + 1
   return printRow(i, j, line)
end

