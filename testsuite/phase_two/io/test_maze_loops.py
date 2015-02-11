pathToData = "datasets/"
file = open(pathToData + "testmaze")
array = "maze_"

cols = int(read(file))
rows = int(read(file))
pos_x = int(read(file))
pos_y = int(read(file))

readMaze()

#__debug__

println "Initial Maze"
printMaze()

::eval(index(pos_x, pos_y)) = "$"
recurse(pos_x, pos_y)

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
			print ::eval(name) + " "
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

	if val == "#" or val == "2":
		return 0
	end

	if val == "_" and ( r == 0 or r == rows-1 or c == 0 or c == cols-1 ):
		::eval(name) = "1"
		return 1
	end

	::eval(name) = "2"

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
