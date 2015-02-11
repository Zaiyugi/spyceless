def loop(ndx, cnt):
	if ndx > cnt:
		print "Finished!"
		return 0
	end

	x = read(file)
	print x

	ndx = ndx + 1
	loop(ndx, cnt)
end

pathToData = "datasets/"
file = open(pathToData + "dataset1")
cnt = read(file)
__debug__

ndx = 0
loop(ndx, int(cnt))

close(file)
