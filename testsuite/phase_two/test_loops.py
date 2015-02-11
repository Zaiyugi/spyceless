# Test Loops
def foo():
   i = 0
   while i < 10:
      println i
      i = i + 1
   end
end

def bar():
   i = 0
   while i < 5:
      j = 0
      line = ""
      while j < 5:
         print "(" + str(i) + ", " + str(j) + ") "
         j = j + 1
      end
      println ""
      i = i + 1
   end
end

def returnFromLoop():
   i = 0
   while i < 5:
      if i == 3:
         return i
      end
      i = i + 1
   end
end

foo()
bar()

println returnFromLoop()
