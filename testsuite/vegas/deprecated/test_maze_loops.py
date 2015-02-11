pathToData = "datasets/"
file = open(pathToData + "maze_31x31")
array = "maze_"

cols = int(read(file))
rows = int(read(file))
start_x = int(read(file))
start_y = int(read(file))
breadcrumb = "*"
empty_cell = "0"

readMaze()

#__debug__

println ""
println "Initial Maze"
printMaze()

::eval(index(start_x, start_y)) = "$"
recurse(start_x, start_y)

println ""
println "Solved Maze (Path in 1s)"
printMaze()

close(file)

def index(i, j):
   return array + str(i) + "_" + str(j)
end

def readMaze():
   i = 0
   while i < rows:
      j = 0
      while j < cols:
         name = index(i, j)
         ::eval(name) = read(file)
         j = j + 1
      end
      i = i + 1
   end
end

def printMaze():
   i = 0
   while i < rows:
      j = 0
      while j < cols:
         name = index(i, j)
         val = ::eval(name)

         if val == breadcrumb or val == empty_cell:
            val = " "
         end
         print val + " "

         j = j + 1
      end
      println ""
      i = i + 1
   end
end

def recurse(r, c):
   if r < 0 or r >= rows or c < 0 or c >= cols:
      return 0
   end

   name = index(r, c)
   val = ::eval(name)

   if val == "+" or val == "-" or val == "|" or val == breadcrumb:
      return 0
   end

   if val == empty_cell and ( r == 0 or r == rows-1 or c == 0 or c == cols-1 ):
      ::eval(name) = "1"
      return 1
   end

   ::eval(name) = breadcrumb

   # Up
   if recurse(r - 1, c) == 1:
      ::eval(name) = "1"
      return 1
   end

   # Down
   if recurse(r + 1, c) == 1:
      ::eval(name) = "1"
      return 1
   end

   # Left
   if recurse(r, c - 1) == 1:
      ::eval(name) = "1"
      return 1
   end

   # Right
   if recurse(r, c + 1) == 1:
      ::eval(name) = "1"
      return 1
   end

   return 0
end
